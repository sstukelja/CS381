################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../as3/src/Aspect.cpp \
../as3/src/Entity381.cpp \
../as3/src/EntityMgr.cpp \
../as3/src/GfxMgr.cpp \
../as3/src/as3.cpp \
../as3/src/engine.cpp \
../as3/src/gameMgr.cpp \
../as3/src/inputMgr.cpp \
../as3/src/mgr.cpp 

OBJS += \
./as3/src/Aspect.o \
./as3/src/Entity381.o \
./as3/src/EntityMgr.o \
./as3/src/GfxMgr.o \
./as3/src/as3.o \
./as3/src/engine.o \
./as3/src/gameMgr.o \
./as3/src/inputMgr.o \
./as3/src/mgr.o 

CPP_DEPS += \
./as3/src/Aspect.d \
./as3/src/Entity381.d \
./as3/src/EntityMgr.d \
./as3/src/GfxMgr.d \
./as3/src/as3.d \
./as3/src/engine.d \
./as3/src/gameMgr.d \
./as3/src/inputMgr.d \
./as3/src/mgr.d 


# Each subdirectory must supply rules for building sources it contributes
as3/src/%.o: ../as3/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/OGRE/Overlay -I/usr/local/include/OGRE -I/usr/include/OIS -I"/home/sstukelja/workspace/Assignment3/as3/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


