################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Beeper.cpp \
../Source/main.cpp \
../Source/tessst.cpp 

OBJS += \
./Source/Beeper.o \
./Source/main.o \
./Source/tessst.o 

CPP_DEPS += \
./Source/Beeper.d \
./Source/main.d \
./Source/tessst.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/Libs/include/aquila -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


