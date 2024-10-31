/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "oled.h"
#include "ti/driverlib/dl_uart.h"
#include "ti_msp_dl_config.h"
#include "oled.h"
#include "string.h"

// General purpose debug timing pin = PA3 using DL_GPIO_setPins(GEN_PORT, GEN_OUT_PIN);

// Data received from UART
#define UART_RX_SIZE        2048        // Typical is around 1800 characters
#define NO_RX_DATA_TIMEOUT  4000        // 400000=110ms measured, u16 max. CPU ticks of no UART data within the receive code, before assuming that the GPS module has finished transmitting to us. Max gaps in TX measured for LC29T = 
#define NO_SIGNAL_TIMEOUT   1500000     // 1500000=3.4s measured, u32 max. CPU ticks of no UART data at all before assuming that there is no GPS module connected. Should receive every second so the timeout should be 2s or so. 

uint8_t rxPacket[UART_RX_SIZE];

enum SystemState {
    NO_SIGNAL_INITIAL = 0,
    NO_SIGNAL = 10,
    RX_RECEIVED = 20,
    RX_PSTMG = 30,
    WAITING = 40,
    LOCKED = 50
};
enum SystemState sys_state = NO_SIGNAL_INITIAL;

int main(void)
{
    SYSCFG_DL_init();

    // At startup the LEDs are initialised LOW
    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN);

    // Display the startup logo for at least a short time, which also includes a NO SIGNAL message
    OLED_Init();
    OLED_write();
    delay_cycles(16000000);

    while (DL_UART_Main_isBusy(UART_0_INST));   // Wait for UART to be ready

    while (1) {
        uint8_t hour_tens;
        uint8_t hour_ones;
        uint8_t min_tens;
        uint8_t min_ones;
        uint8_t sec_tens;
        uint8_t sec_ones;

        // Wait to receive the UART data
        uint32_t nosignal_timeout = 0;
        while(DL_UART_isRXFIFOEmpty(UART_0_INST) && nosignal_timeout < NO_SIGNAL_TIMEOUT){
            nosignal_timeout++;
        }
        
        if(nosignal_timeout >= NO_SIGNAL_TIMEOUT){
            // Looks like nothing on the UART for a few seconds, revert to NO SIGNAL state
            // DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN);   // This will give an invisible low flicker (~3us) but lets our scope check the timing
            if(sys_state > NO_SIGNAL){      // Only do this if we were previously showing the time, otherwise we lose the boot logo & message
                sys_state = NO_SIGNAL;      // Can't have the boot logo + NO SIGNAL screen anymore since that is the RAM init values, but we can have a blank time
            } else {
                sys_state = NO_SIGNAL_INITIAL;  // Same as NO_SIGNAL but doesn't clear OLED in order to preserve startup screen
            }
        } else {
            sys_state = RX_RECEIVED;
        }
        nosignal_timeout = 0;


        if(sys_state == RX_RECEIVED) {    // Process the received data
            memset(rxPacket, 0, UART_RX_SIZE);  // Clear out any oc:\Users\Michael\Desktop\Projects\GPS-Time-Source\MSPM0 Firmware\README.htmlld data

            // Receive the UART bytes until either the buffer is full (unlikely) or the transmission stops for a few ms
            // LC29T has two bursts every second separated by about 45ms: $PSTMTG and then $GNRMC (which is everything else). Since we only care about PSTMUTC which is at the end, 
            // the timeout is short enough that both get handled separately
            uint32_t timeout = 0;
            for (uint16_t i = 0; i < UART_RX_SIZE; i++) {
               DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN | GPIO_LEDS_GREEN_PIN);  // Dip out the LED to show that data was received

                DL_GPIO_setPins(GEN_PORT, GEN_OUT_PIN);
                while(DL_UART_isRXFIFOEmpty(UART_0_INST) && timeout < NO_RX_DATA_TIMEOUT) {
                    timeout++;
                }
                DL_GPIO_clearPins(GEN_PORT, GEN_OUT_PIN);

                if(timeout >= NO_RX_DATA_TIMEOUT){
                    // If there has been no new data for a few ms then assume that the transmission has finished
                    break;
                } else {
                    rxPacket[i] = DL_UART_receiveData(UART_0_INST); 
                }
                timeout = 0;
            }

            char *ptr_utc = strstr(rxPacket, "$PSTMUTC\0");     // Typical (locked) string: $PSTMUTC,101517.000,28102024,1414145717,18,2*5C
            
            if ( ptr_utc != NULL ) {
                ptr_utc += 9;   // advance to first character of interest which is the hours tens

                hour_tens = ptr_utc[0] - 48;    // Collect all the UTC time string characters and shift down 0-9 since our character set starts at 0='0'
                hour_ones = ptr_utc[1] - 48;
                min_tens = ptr_utc[2] - 48;
                min_ones = ptr_utc[3] - 48;
                sec_tens = ptr_utc[4] - 48;
                sec_ones = ptr_utc[5] - 48;

                for(uint8_t k=0; k<255; k++){   // Search for the asterisk which is the last character before the checksum
                    if(ptr_utc[k] == '*'){
                        if(ptr_utc[k-1] == '1'){    // The final character before the checksum is the GPS time lock status. 0=invalid, 1=from RAM, 2=locked
                            sys_state = WAITING;    // GPS is working and attached but not locked to satellites yet. Could take 15-20mins!
                            break;

                        } else if (ptr_utc[k-1] == '2'){    // GPS is locked and the time is valid so use it
                            sys_state = LOCKED;
                            break;

                        } else {                    // Value could be '0' which means invalid time
                            sys_state = NO_SIGNAL;    
                            break;
                        }
                    }
                }  
            } else if ( strstr(rxPacket, "$PSTMTG\0") != NULL ) {
                sys_state = RX_PSTMG;       // Received the first data burst from the module, the next one should contain PSTMUTC
            } else {
                sys_state = NO_SIGNAL;      // Received something on the UART but not the expected GPS data
            }
        }

        switch ( sys_state ) {
            default:
            case NO_SIGNAL_INITIAL:     // Same as normal NO_SIGNAL, except the OLED is showing the bootup logo+NO SIGNAL screen which is init RAM so don't want to erase
                DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_GREEN_PIN);
                DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN);
                break;

            case NO_SIGNAL:             
                DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_GREEN_PIN);
                DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN);

                OLED_clear();
                OLED_num(10, 32, 8);    // 10=colons so just show an empty time like "  :  :  "
                OLED_num(10, 80, 8);
                OLED_write(); 
                break;

            case RX_RECEIVED:
            case RX_PSTMG:
                // Mid-process for RX data handling so don't do anything
                break;

            case WAITING:
                DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_GREEN_PIN | GPIO_LEDS_RED_PIN);

                OLED_clear();
                OLED_num(10, 32, 8);    // 10=colons so just show an empty time like "  :  :  "
                OLED_num(10, 80, 8);
                OLED_write(); 
                break;

            case LOCKED:
                DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_RED_PIN);
                DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_GREEN_PIN);

                OLED_clear();
                OLED_num(hour_tens, 0, 8);
                OLED_num(hour_ones, 16, 8);
                OLED_num(10, 32, 8);
                OLED_num(min_tens, 48, 8);
                OLED_num(min_ones, 64, 8);
                OLED_num(10, 80, 8);
                OLED_num(sec_tens, 96, 8);
                OLED_num(sec_ones, 112, 8);
                OLED_write(); 
                break;
        } 
    }
}
