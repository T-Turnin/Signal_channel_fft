################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_adc.c \
../BSP/bsp_tim.c \
../BSP/bsp_usart.c 

OBJS += \
./BSP/bsp_adc.o \
./BSP/bsp_tim.o \
./BSP/bsp_usart.o 

C_DEPS += \
./BSP/bsp_adc.d \
./BSP/bsp_tim.d \
./BSP/bsp_usart.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/bsp_adc.o: ../BSP/bsp_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32cube/project_workspace/Signal_channel_fft/BSP" -I"D:/stm32cube/project_workspace/Signal_channel_fft/Drivers/CMSIS/DSP/include" -I"D:/stm32cube/project_workspace/Signal_channel_fft/ALGO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BSP/bsp_adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
BSP/bsp_tim.o: ../BSP/bsp_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32cube/project_workspace/Signal_channel_fft/BSP" -I"D:/stm32cube/project_workspace/Signal_channel_fft/Drivers/CMSIS/DSP/include" -I"D:/stm32cube/project_workspace/Signal_channel_fft/ALGO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BSP/bsp_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
BSP/bsp_usart.o: ../BSP/bsp_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32cube/project_workspace/Signal_channel_fft/BSP" -I"D:/stm32cube/project_workspace/Signal_channel_fft/Drivers/CMSIS/DSP/include" -I"D:/stm32cube/project_workspace/Signal_channel_fft/ALGO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BSP/bsp_usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

