################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/Dump.cpp \
../src/view/Top.cpp \
../src/view/View.cpp 

OBJS += \
./src/view/Dump.o \
./src/view/Top.o \
./src/view/View.o 

CPP_DEPS += \
./src/view/Dump.d \
./src/view/Top.d \
./src/view/View.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/%.o: ../src/view/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../TrafficAccounting/src -I../../cpp-sparse-ropes/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


