################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
brtos-master/hal/GCC_CORTEX-M0/%.o: ../brtos-master/hal/GCC_CORTEX-M0/%.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DPART_TM4C1294NCPDT -DTARGET_IS_TM4C129_RA1 -Dgcc -I"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/arm-none-eabi/include" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/brtos-master/ConfigExample" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/brtos-master/hal/GCC_CORTEX-M4" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/brtos-master/hal/GCC_CORTEX-M4" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/brtos-master/hal/MemoryAllocation" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/brtos-master/brtos/includes" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/rtu" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/driverlib" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva" -I"D:/Engenharia/6 periodo/Microcontrolador/MBUS_Master_Tiva/port" -I"C:/ti/TivaWare_C_Series-2.1.1.71" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MD -std=c99 -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


