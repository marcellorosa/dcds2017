################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
modbus/rtu/mbcrc.obj: ../modbus/rtu/mbcrc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi -O2 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/config" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/utils" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/rtu" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/include" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/port" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="modbus/rtu/mbcrc.pp" --obj_directory="modbus/rtu" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

modbus/rtu/mbrtu.obj: ../modbus/rtu/mbrtu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi -O2 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/config" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/utils" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/rtu" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/include" --include_path="C:/Users/Marcelo/Desktop/MBUS_Slave_MSP/modbus/port" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="modbus/rtu/mbrtu.pp" --obj_directory="modbus/rtu" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


