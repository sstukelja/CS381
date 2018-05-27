################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Aspect.cpp \
../src/Command.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp \
../src/GfxMgr.cpp \
../src/UnitAI.cpp \
../src/as3.cpp \
../src/engine.cpp \
../src/gameMgr.cpp \
../src/inputMgr.cpp \
../src/mgr.cpp 

OBJS += \
./src/Aspect.o \
./src/Command.o \
./src/Entity381.o \
./src/EntityMgr.o \
./src/GfxMgr.o \
./src/UnitAI.o \
./src/as3.o \
./src/engine.o \
./src/gameMgr.o \
./src/inputMgr.o \
./src/mgr.o 

CPP_DEPS += \
./src/Aspect.d \
./src/Command.d \
./src/Entity381.d \
./src/EntityMgr.d \
./src/GfxMgr.d \
./src/UnitAI.d \
./src/as3.d \
./src/engine.d \
./src/gameMgr.d \
./src/inputMgr.d \
./src/mgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/OGRE/Overlay -I/usr/local/include/OGRE -I/usr/include/OIS -I"/home/sstukelja/workspace/Assignment4_Test/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


