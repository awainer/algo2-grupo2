################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../a_lexico.c \
../a_sintactico.c \
../main.c \
../token.c 

OBJS += \
./a_lexico.o \
./a_sintactico.o \
./main.o \
./token.o 

C_DEPS += \
./a_lexico.d \
./a_sintactico.d \
./main.d \
./token.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


