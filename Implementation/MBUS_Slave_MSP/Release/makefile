################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./utils/util.obj" \
"./modbus/rtu/mbcrc.obj" \
"./modbus/rtu/mbrtu.obj" \
"./modbus/port/portevent.obj" \
"./modbus/port/portserial.obj" \
"./modbus/port/porttimer.obj" \
"./modbus/mb.obj" \
"./modbus/functions/mbfunccoils.obj" \
"./modbus/functions/mbfuncdiag.obj" \
"./modbus/functions/mbfuncdisc.obj" \
"./modbus/functions/mbfuncholding.obj" \
"./modbus/functions/mbfuncinput.obj" \
"./modbus/functions/mbfuncother.obj" \
"./modbus/functions/mbutils.obj" \
"./config/config_hw.obj" \
"../lnk_msp430g2553.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utils/subdir_vars.mk
-include modbus/rtu/subdir_vars.mk
-include modbus/port/subdir_vars.mk
-include modbus/subdir_vars.mk
-include modbus/functions/subdir_vars.mk
-include config/subdir_vars.mk
-include subdir_rules.mk
-include utils/subdir_rules.mk
-include modbus/rtu/subdir_rules.mk
-include modbus/port/subdir_rules.mk
-include modbus/subdir_rules.mk
-include modbus/functions/subdir_rules.mk
-include config/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MBUS_Slave_MSP.out \

EXE_OUTPUTS__QUOTED += \
"MBUS_Slave_MSP.out" \


# All Target
all: MBUS_Slave_MSP.out

# Tool invocations
MBUS_Slave_MSP.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmsp --abi=eabi -O2 --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"MBUS_Slave_MSP.map" --heap_size=80 --stack_size=80 -i"C:/ti/ccsv6/ccs_base/msp430/include" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="MBUS_Slave_MSP_linkInfo.xml" --rom_model -o "MBUS_Slave_MSP.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "utils\util.pp" "modbus\rtu\mbcrc.pp" "modbus\rtu\mbrtu.pp" "modbus\port\portevent.pp" "modbus\port\portserial.pp" "modbus\port\porttimer.pp" "modbus\mb.pp" "modbus\functions\mbfunccoils.pp" "modbus\functions\mbfuncdiag.pp" "modbus\functions\mbfuncdisc.pp" "modbus\functions\mbfuncholding.pp" "modbus\functions\mbfuncinput.pp" "modbus\functions\mbfuncother.pp" "modbus\functions\mbutils.pp" "config\config_hw.pp" 
	-$(RM) "main.obj" "utils\util.obj" "modbus\rtu\mbcrc.obj" "modbus\rtu\mbrtu.obj" "modbus\port\portevent.obj" "modbus\port\portserial.obj" "modbus\port\porttimer.obj" "modbus\mb.obj" "modbus\functions\mbfunccoils.obj" "modbus\functions\mbfuncdiag.obj" "modbus\functions\mbfuncdisc.obj" "modbus\functions\mbfuncholding.obj" "modbus\functions\mbfuncinput.obj" "modbus\functions\mbfuncother.obj" "modbus\functions\mbutils.obj" "config\config_hw.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

