################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../GPS_Time_Source_Monitor.syscfg 

C_SRCS += \
./ti_msp_dl_config.c \
C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0l130x_ticlang.c \
../main.c \
../oled.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./ti_msp_dl_config.d \
./startup_mspm0l130x_ticlang.d \
./main.d \
./oled.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./ti_msp_dl_config.o \
./startup_mspm0l130x_ticlang.o \
./main.o \
./oled.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h \
./Event.dot 

OBJS__QUOTED += \
"ti_msp_dl_config.o" \
"startup_mspm0l130x_ticlang.o" \
"main.o" \
"oled.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" \
"Event.dot" 

C_DEPS__QUOTED += \
"ti_msp_dl_config.d" \
"startup_mspm0l130x_ticlang.d" \
"main.d" \
"oled.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

SYSCFG_SRCS__QUOTED += \
"../GPS_Time_Source_Monitor.syscfg" 

C_SRCS__QUOTED += \
"./ti_msp_dl_config.c" \
"C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0l130x_ticlang.c" 


