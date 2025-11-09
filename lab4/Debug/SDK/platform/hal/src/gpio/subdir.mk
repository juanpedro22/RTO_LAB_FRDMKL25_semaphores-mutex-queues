################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/hal/src/gpio/fsl_gpio_hal.c 

OBJS += \
./SDK/platform/hal/src/gpio/fsl_gpio_hal.o 

C_DEPS += \
./SDK/platform/hal/src/gpio/fsl_gpio_hal.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/hal/src/gpio/%.o: ../SDK/platform/hal/src/gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -D"FSL_RTOS_FREE_RTOS" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/hal/inc" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/hal/src/sim/MKL25Z4" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/system/src/clock/MKL25Z4" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/system/inc" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/osa/inc" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/CMSIS/Include" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/devices" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/devices/MKL25Z4/include" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/devices/MKL25Z4/startup" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/Generated_Code/SDK/platform/devices/MKL25Z4/startup" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/Sources" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/Generated_Code" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/rtos/FreeRTOS/include" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/rtos/FreeRTOS/port/gcc" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/Generated_Code/SDK/rtos/FreeRTOS/config" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/drivers/inc" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/utilities/src" -I"C:/Users/juan_/OneDrive/Documentos/Mestrado/Software Real Time/lab 4 e 5/lab4/SDK/platform/utilities/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


