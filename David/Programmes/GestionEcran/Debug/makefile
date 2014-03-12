################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: GestionEcran.axf

# Tool invocations
GestionEcran.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/David/Google Drive/Micro/TpTrain/David/Programmes/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="GestionEcran.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "GestionEcran_Debug.ld" -o "GestionEcran.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) GestionEcran.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "GestionEcran.axf"; # arm-none-eabi-objcopy -O binary "GestionEcran.axf" "GestionEcran.bin" ; checksum -p LPC1769 -d "GestionEcran.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
