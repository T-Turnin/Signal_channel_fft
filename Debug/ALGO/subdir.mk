################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ALGO/FFT.c 

OBJS += \
./ALGO/FFT.o 

C_DEPS += \
./ALGO/FFT.d 


# Each subdirectory must supply rules for building sources it contributes
ALGO/FFT.o: ../ALGO/FFT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32cube/project_workspace/Signal_channel_fft/BSP" -I"D:/stm32cube/project_workspace/Signal_channel_fft/Drivers/CMSIS/DSP/include" -I"D:/stm32cube/project_workspace/Signal_channel_fft/ALGO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ALGO/FFT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

