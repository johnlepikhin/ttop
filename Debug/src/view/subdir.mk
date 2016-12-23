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
	g++ -std=c++0x -I../../cpp-quilt-strings/src -I../../TrafficProcessor/src -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


