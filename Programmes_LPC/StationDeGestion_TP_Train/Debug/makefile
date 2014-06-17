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
all: StationDeGestion_TP_Train.axf

# Tool invocations
StationDeGestion_TP_Train.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/mignam/HEPIA/TP_TRAIN/Programmes_LPC/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="StationDeGestion_TP_Train.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "StationDeGestion_TP_Train_Debug.ld" -o "StationDeGestion_TP_Train.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) StationDeGestion_TP_Train.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "StationDeGestion_TP_Train.axf"; # arm-none-eabi-objcopy -O binary "StationDeGestion_TP_Train.axf" "StationDeGestion_TP_Train.bin" ; checksum -p LPC1769 -d "StationDeGestion_TP_Train.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
