################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
i2c_controller_rw_multibyte_fifo_poll.o: ../i2c_controller_rw_multibyte_fifo_poll.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang" -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-646551009: ../i2c_controller_rw_multibyte_fifo_poll.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.21.0/sysconfig_cli.bat" --script "C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang/i2c_controller_rw_multibyte_fifo_poll.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_02_00_05/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-646551009 ../i2c_controller_rw_multibyte_fifo_poll.syscfg
device.opt: build-646551009
device.cmd.genlibs: build-646551009
ti_msp_dl_config.c: build-646551009
ti_msp_dl_config.h: build-646551009
Event.dot: build-646551009

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang" -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0l130x_ticlang.o: C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0l130x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang" -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

oled.o: ../oled.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang" -I"C:/Users/Michael/Desktop/Projects/GPS-Time-Source/Firmware/i2c_controller_rw_multibyte_fifo_poll_LP_MSPM0L1306_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(basename\ $(<F)).o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


