#include "oled.h"


void OLED_Init() {
    OLED_command(OLED_DISPLAYOFF);         // 0xAE
    OLED_command(OLED_SETDISPLAYCLOCKDIV); // 0xD5
    OLED_command(0x80);                    // the suggested ratio 0x80
    OLED_command(OLED_SETMULTIPLEX);       // 0xA8
    OLED_command(0x1F);
    OLED_command(OLED_SETDISPLAYOFFSET);   // 0xD3
    OLED_command(0x0);                        // no offset
    OLED_command(OLED_SETSTARTLINE | 0x0); // line #0
    OLED_command(OLED_CHARGEPUMP);         // 0x8D
    OLED_command(0x14);
    OLED_command(OLED_MEMORYMODE);         // 0x20
    OLED_command(0x00);                    // 0x0 = horizontal, 0x01 = vertical
    OLED_command(OLED_SEGREMAP | 0x1);
    OLED_command(OLED_COMSCANDEC);
    OLED_command(OLED_SETCOMPINS);         // 0xDA
    OLED_command(0x02);
    OLED_command(OLED_SETCONTRAST);        // 0x81
    OLED_command(0x8F);
    OLED_command(OLED_SETPRECHARGE);       // 0xd9
    OLED_command(0xF1);
    OLED_command(OLED_SETVCOMDETECT);      // 0xDB
    OLED_command(0x40);
    OLED_command(OLED_DISPLAYALLON_RESUME);// 0xA4
    OLED_command(OLED_NORMALDISPLAY);      // 0xA6
    OLED_command(OLED_DISPLAYON);          //--turn on oled panel
}

char OLED_command(char command) {

    const char I2C_TX_PACKET_SIZE = 2;
    const char gTxPacket[I2C_TX_PACKET_SIZE] = {0x00, command};  // 0x00 means command follows
    DL_I2C_fillControllerTXFIFO(I2C_INST, &gTxPacket[0], I2C_TX_PACKET_SIZE);

    /* Wait for I2C to be Idle */
    while (!(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    /* Send the packet to the device. This function will send Start + Stop automatically. */
    DL_I2C_startControllerTransfer(I2C_INST, OLED_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, I2C_TX_PACKET_SIZE);

    /* Poll until the Controller writes all bytes */
    while (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_ERROR) {
        return 1;
    }
    return 0;
}

char OLED_data( char data) {

    const char I2C_TX_PACKET_SIZE = 2;
    const char gTxPacket[I2C_TX_PACKET_SIZE] = {0x40, data};  // 0x40 means data follows
    DL_I2C_fillControllerTXFIFO(I2C_INST, &gTxPacket[0], I2C_TX_PACKET_SIZE);

    /* Wait for I2C to be Idle */
    while (!(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    /* Send the packet to the device. This function will send Start + Stop automatically. */
    DL_I2C_startControllerTransfer(I2C_INST, OLED_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, I2C_TX_PACKET_SIZE);

    /* Poll until the Controller writes all bytes */
    while (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_ERROR) {
        return 1;
    }
    return 0;
}

// Transfer the entire display buffer to the OLED display. measured time = 12.54ms
char OLED_write(){
    OLED_command(OLED_COLUMNADDR);
    OLED_command(0x00);
    OLED_command(127);
    OLED_command(OLED_PAGEADDR);
    OLED_command(0x00);
    OLED_command(3);

    const uint16_t I2C_TX_PACKET_SIZE = (128 * 32 / 8) + 1;
    const char controlByte = 0x40;
    uint16_t gTxCount=0;

    DL_I2C_fillControllerTXFIFO(I2C_INST, &controlByte, 1);
    
    /* Wait for I2C to be Idle */
    while (!(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    /* Send the packet to the device. This function will send Start + Stop automatically. */
    DL_I2C_startControllerTransfer(I2C_INST, OLED_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, I2C_TX_PACKET_SIZE);

    while (gTxCount < I2C_TX_PACKET_SIZE) {
        //Waiting for txfifo empty
        while(!DL_I2C_isControllerTXFIFOEmpty(I2C_INST));
        //while (!(DL_I2C_getRawInterruptStatus(I2C_INST, 0xFF) & DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_EMPTY));
        //clear interrupt
        //DL_I2C_clearInterruptStatus(I2C_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_EMPTY);
        //Write more data to I2C FIFO
        gTxCount += DL_I2C_fillControllerTXFIFO(I2C_INST, &OLED_buffer[gTxCount], I2C_TX_PACKET_SIZE - gTxCount);
    }

    /* Poll until the Controller writes all bytes */
    while (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    // DL_I2C_fillControllerTXFIFO(I2C_INST, &OLED_buffer[7], I2C_TX_PACKET_SIZE);

    DL_I2C_flushControllerTXFIFO(I2C_INST); // For some reason without this all future OLED_xxx() would be reversed byte order??

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_ERROR) {
        return 1;
    }
    OLED_command(3);
    return 0;
}

void OLED_clear(){
    memset(OLED_buffer, 0, 128 * 32 / 8); 
}

void OLED_invert(){
    OLED_command(OLED_INVERTDISPLAY);
}

void OLED_rscroll(char start, char stop) {
    OLED_command(0x26);
    OLED_command(0X00);
    OLED_command(start);
    OLED_command(0X00);
    OLED_command(stop);
    OLED_command(0X00);
    OLED_command(0XFF);
    OLED_command(0x2F); //Activate scroll
}

void OLED_lscroll(char start, char stop) {
    OLED_command(0x27);
    OLED_command(0X00);
    OLED_command(start);
    OLED_command(0X00);
    OLED_command(stop);
    OLED_command(0X00);
    OLED_command(0XFF);
    OLED_command(0x2F); //Activate scroll
}

void OLED_stopscroll() {
    OLED_command(0x2E);
}

void OLED_pixel(short x, short y, char color){ //hmm, dosent include error checking..
    char y_bit = y%8;
    short y_row = (y - y_bit)*16 + x;
    OLED_buffer[y_row] |= (color?1:0) << y_bit;
}

void OLED_char(char character, short x, short y) {
    short table_offset = (character-0x20)*5;
    short offset = y*16 + x;
    char i = 0;
    for(; i < 5; i++) OLED_buffer[i+offset] = OLED_characters[i+table_offset];
}

void OLED_num(char num, short x, short y) {
    short offset = y*16 + x;
    char i;
    // 16x16
    // for(i=0; i < 12; i++) OLED_buffer[i+offset] = OLED_numbers_16x16[num*24+i];           // First row
    // for(i=0; i < 12; i++) OLED_buffer[i+offset+128] = OLED_numbers_16x16[num*24+i+12];    // Second row

    // 16x24
    for(i=0; i < 14; i++) OLED_buffer[i+offset] = OLED_numbers_16x24[num*14*3+i];           // First row
    for(i=0; i < 14; i++) OLED_buffer[i+offset+128] = OLED_numbers_16x24[num*14*3+i+14];    // Second row
    for(i=0; i < 14; i++) OLED_buffer[i+offset+128*2] = OLED_numbers_16x24[num*14*3+i+14*2];    // Second row
}

void OLED_string(char* str, short x, short y) {

    short pos = 0;
    char character = str[pos++];
    short startx = x;
    short starty = y;
    while(character != '\0') {
        OLED_char(character, startx, starty);
        if(startx >= 123) starty++; //wrap around
        startx += 5;
        character = str[pos++];
    }
}