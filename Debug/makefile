################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include BSP/subdir.mk
-include ALGO/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Signal_channel_fft.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Signal_channel_fft.list \

OBJCOPY_BIN += \
Signal_channel_fft.bin \


# 所有目标
all: Signal_channel_fft.elf secondary-outputs

# 工具调用
Signal_channel_fft.elf: $(OBJS) $(USER_OBJS) D:\stm32cube\project_workspace\Signal_channel_fft\STM32F407VETX_FLASH.ld
	arm-none-eabi-gcc -o "Signal_channel_fft.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\stm32cube\project_workspace\Signal_channel_fft\STM32F407VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Signal_channel_fft.map" -Wl,--gc-sections -static -L"D:\stm32cube\project_workspace\Signal_channel_fft\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo '已结束构建目标： $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo '已结束构建： $@'
	@echo ' '

Signal_channel_fft.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Signal_channel_fft.list"
	@echo '已结束构建： $@'
	@echo ' '

Signal_channel_fft.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Signal_channel_fft.bin"
	@echo '已结束构建： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
