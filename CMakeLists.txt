cmake_minimum_required(VERSION 3.19.0)
project(simple_game_machine LANGUAGES ASM C CXX)

set(CMAKE_EXE_LINKER_FLAGS "")

message(STATUS "Building config: '${CMAKE_BUILD_TYPE}', Model: '${STM32_MODEL}'")
set(STM32_MODEL "" CACHE STRING "STM32 model to build firmware for")

set (CMAKE_CXX_STANDARD 23)

if(STM32_MODEL STREQUAL "STM32U083RCT6U")
    set(XMCU_SOC_VENDOR st)
    set(XMCU_SOC_ARCH arm)
    set(XMCU_SOC_ARCH_CORE_FAMILY m0)
    set(XMCU_SOC_VENDOR_FAMILY u0)
    set(XMCU_SOC_VENDOR_FAMILY_RM rm0503)
    set(XMCU_SOC_VENDOR_MODEL stm32l0u083rct6u)
    set(CMSIS_SOC_MODEL STM32U083xx)
    set(LDFLAGS -mcpu=cortex-m0plus -mthumb)
    set(CFLAGS -mcpu=cortex-m0plus -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16)
    set(XMCU_ISR_CONTEXT ${XMCU_ISR_CONTEXT})
    set(XMCU_NOSTDLIB ${XMCU_NOSTDLIB})
    set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/gcc/linker/STM32U083xx_FLASH.ld)
    set(CMSIS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Include)
    set(CMSIS_DEVICE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Include)
    set(CMSIS_STARTUP ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/gcc/startup_stm32u083xx.s)
    set(VENDOR_SYSTEM_INIT ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/system_stm32u0xx.c)
else()
    message("Error!")
endif()

add_compile_definitions(XMCU_SOC_VENDOR=${XMCU_SOC_VENDOR} XMCU_SOC_ARCH_CORE_FAMILY=${XMCU_SOC_ARCH_CORE_FAMILY} XMCU_SOC_VENDOR_FAMILY=${XMCU_SOC_VENDOR_FAMILY} XMCU_SOC_ARCH=${XMCU_SOC_ARCH})
add_compile_definitions(XMCU_SOC_STM32_FAMILY=${XMCU_SOC_VENDOR_FAMILY} XMCU_SOC_VENDOR_FAMILY_RM=${XMCU_SOC_VENDOR_FAMILY_RM} XMCU_SOC_VENDOR_MODEL=${XMCU_SOC_VENDOR_MODEL})
add_compile_definitions(XMCU_ISR_CONTEXT=${XMCU_ISR_CONTEXT} XMCU_NOSTDLIB=${XMCU_NOSTDLIB} ${CMSIS_SOC_MODEL} CMSIS_SOC_FILE=stm32u0xx.h)
add_compile_definitions(ARM_MATH_CM0PLUS ARM_MATH_ROUNDING)

include_directories(PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMSIS_DEVICE_INCLUDE_PATH} ${CMSIS_INCLUDE_PATH})

file(GLOB_RECURSE src ${CMAKE_CURRENT_LIST_DIR}/application/*.cpp ${CMAKE_CURRENT_LIST_DIR}/application/*.hpp ${CMAKE_CURRENT_LIST_DIR}/soc/*.cpp ${CMAKE_CURRENT_LIST_DIR}/soc/*.hpp)

set(ELF_NAME out.elf)
set(BIN_NAME out.bin)

add_executable(${ELF_NAME} ${src} ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Device/ST/STM32U0xx/Include/stm32u083xx.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Device/ST/STM32U0xx/Include/stm32u0xx.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Device/ST/STM32U0xx/Include/system_stm32u0xx.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cachel1_armv7.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_armcc.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_armclang.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_armclang_ltm.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_compiler.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_gcc.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_iccarm.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/cmsis_version.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_armv81mml.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_armv8mbl.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_armv8mml.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm0.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm0plus.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm1.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm23.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm3.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm33.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm35p.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm4.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm55.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm7.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_cm85.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_sc000.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_sc300.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/core_starmc1.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/mpu_armv7.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/mpu_armv8.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/pac_armv81.h" 
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/pmu_armv8.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/ST/arm/CMSIS/Include/tz_context.h"
                              ${CMAKE_CURRENT_LIST_DIR}"/application/syscalls.c"
                              ${CMAKE_CURRENT_LIST_DIR}"/application/sysmem.c"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/system_stm32u0xx.c"
                              ${CMSIS_STARTUP} 
                              ${VENDOR_SYSTEM_INIT} "soc/st/arm/systick.cpp" "xmcu/stdglue.cpp" "soc/st/arm/m0/u0/rm0503/peripherals/USART/usart.cpp" "soc/st/arm/m0/u0/rm0503/peripherals/I2C/i2c.cpp")

set(CFLAGS ${CFLAGS} -c -fno-common -ffast-math -fsingle-precision-constant)
set(CPPFLAGS ${CFLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit)
set(MCU_LD_OPTIONS )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CFLAGS ${CFLAGS} -Og -g3)
    set(CPPFLAGS ${CPPFLAGS} ${CFLAGS})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    set(CFLAGS ${CFLAGS} -Os -ffunction-sections -fdata-sections)
    set(CPPFLAGS ${CPPFLAGS} ${CFLAGS})
    set(LDFLAGS ${LDFLAGS} -Wl,--gc-sections)
endif()

if (XMCU_NOSTDLIB STREQUAL "1")
    set(LDFLAGS ${LDFLAGS} --specs=nosys.specs -nostdlib)
else()
    set(LDFLAGS ${LDFLAGS} --specs=nano.specs --specs=nosys.specs)
endif()

target_compile_options(${ELF_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:ASM,C>:${CFLAGS}>")
target_compile_options(${ELF_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CPPFLAGS}>")
        
set(OUTPUT_STEM out)
                         
target_link_options(${ELF_NAME} PRIVATE
        ${LDFLAGS}
        -Wl,-Map=${OUTPUT_STEM}.map,-cref,--print-memory-usage
        -T${LINKER_SCRIPT})
        
set_target_properties(${ELF_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Generating firmware .bin file"
)