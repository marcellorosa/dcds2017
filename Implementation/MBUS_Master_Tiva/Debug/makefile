################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.o" \
"./tm4c1294ncpdt_startup_ccs_gcc.o" \
"./utils/queue.o" \
"./utils/util.o" \
"./rtu/mbRTU.o" \
"./rtu/mbcrc.o" \
"./port/portIO.o" \
"./port/portTimer.o" \
"./port/portUART.o" \
"./fsm_mestre/fsm_mestre.o" \
"./driverlib/cpu.o" \
"./driverlib/gpio.o" \
"./driverlib/interrupt.o" \
"./driverlib/timer.o" \
"./driverlib/uart.o" \
-Wl,-T"../tm4c1294ncpdt.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-l"gcc" \
-l"nosys" \
-l"c" \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utils/subdir_vars.mk
-include rtu/subdir_vars.mk
-include port/subdir_vars.mk
-include fsm_mestre/subdir_vars.mk
-include driverlib/subdir_vars.mk
-include subdir_rules.mk
-include utils/subdir_rules.mk
-include rtu/subdir_rules.mk
-include port/subdir_rules.mk
-include fsm_mestre/subdir_rules.mk
-include driverlib/subdir_rules.mk
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
MBUS_Master_Tiva.out \

EXE_OUTPUTS__QUOTED += \
"MBUS_Master_Tiva.out" \

BIN_OUTPUTS += \
MBUS_Master_Tiva.hex \

BIN_OUTPUTS__QUOTED += \
"MBUS_Master_Tiva.hex" \


# All Target
all: MBUS_Master_Tiva.out

# Tool invocations
MBUS_Master_Tiva.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc.exe" -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DPART_TM4C1294NCPDT -DTARGET_IS_TM4C129_RA1 -Dgcc -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -Wl,-Map,"MBUS_Master_Tiva.map" --entry _start -o"MBUS_Master_Tiva.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

MBUS_Master_Tiva.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-objcopy.exe"  $(EXE_OUTPUTS__QUOTED) "MBUS_Master_Tiva.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.d" "tm4c1294ncpdt_startup_ccs_gcc.d" "utils\queue.d" "utils\util.d" "rtu\mbRTU.d" "rtu\mbcrc.d" "port\portIO.d" "port\portTimer.d" "port\portUART.d" "fsm_mestre\fsm_mestre.d" "driverlib\cpu.d" "driverlib\gpio.d" "driverlib\interrupt.d" "driverlib\timer.d" "driverlib\uart.d" 
	-$(RM) "main.o" "tm4c1294ncpdt_startup_ccs_gcc.o" "utils\queue.o" "utils\util.o" "rtu\mbRTU.o" "rtu\mbcrc.o" "port\portIO.o" "port\portTimer.o" "port\portUART.o" "fsm_mestre\fsm_mestre.o" "driverlib\cpu.o" "driverlib\gpio.o" "driverlib\interrupt.o" "driverlib\timer.o" "driverlib\uart.o" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

