################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Beeper.cpp \
../Source/CRC.cpp \
../Source/DataProcessor.cpp \
../Source/DataReceiver.cpp \
../Source/DataSender.cpp \
../Source/Recorder.cpp \
../Source/System.cpp \
../Source/main.cpp 

OBJS += \
./Source/Beeper.o \
./Source/CRC.o \
./Source/DataProcessor.o \
./Source/DataReceiver.o \
./Source/DataSender.o \
./Source/Recorder.o \
./Source/System.o \
./Source/main.o 

CPP_DEPS += \
./Source/Beeper.d \
./Source/CRC.d \
./Source/DataProcessor.d \
./Source/DataReceiver.d \
./Source/DataSender.d \
./Source/Recorder.d \
./Source/System.d \
./Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/path/to/aquila/files/folder -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


