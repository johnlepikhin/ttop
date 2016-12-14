################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AppSettings.cpp \
../src/Logic.cpp \
../src/ParserDescription.cpp \
../src/ttop.cpp \
../src/utils.cpp 

OBJS += \
./src/AppSettings.o \
./src/Logic.o \
./src/ParserDescription.o \
./src/ttop.o \
./src/utils.o 

CPP_DEPS += \
./src/AppSettings.d \
./src/Logic.d \
./src/ParserDescription.d \
./src/ttop.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/AppSettings.o: ../src/AppSettings.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../cpp-quilt-strings/src -I../../TrafficProcessor/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/AppSettings.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I../../cpp-quilt-strings/src -I../../TrafficProcessor/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


