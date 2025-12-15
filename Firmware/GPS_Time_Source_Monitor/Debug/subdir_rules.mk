################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1558069158: ../GPS_Time_Source_Monitor.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/michael/ti/sysconfig_1.25.0/sysconfig_cli.sh" -s "/home/michael/ti/mspm0_sdk_2_08_00_04/.metadata/product.json" -d "MSPM0L110X" -p "VSSOP-20(DGS20)" -r "Default" --script "/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor/GPS_Time_Source_Monitor.syscfg" --context "system" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1558069158 ../GPS_Time_Source_Monitor.syscfg
device.opt: build-1558069158
device.cmd.genlibs: build-1558069158
ti_msp_dl_config.c: build-1558069158
ti_msp_dl_config.h: build-1558069158
Event.dot: build-1558069158

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/michael/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor" -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor/Debug" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source/third_party/CMSIS/Core/Include" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0l110x_ticlang.o: /home/michael/ti/mspm0_sdk_2_08_00_04/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0l110x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/michael/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor" -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor/Debug" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source/third_party/CMSIS/Core/Include" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

main.o: ../main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/michael/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor" -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor/Debug" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source/third_party/CMSIS/Core/Include" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

oled.o: ../oled.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/michael/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor" -I"/home/michael/Documents/Projects/GPS-Time-Source/Firmware/GPS_Time_Source_Monitor/Debug" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source/third_party/CMSIS/Core/Include" -I"/home/michael/ti/mspm0_sdk_2_08_00_04/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


