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
    set(MCU_LD_OPTIONS -mcpu=cortex-m0plus -mthumb)
    set(XMCU_ISR_CONTEXT 0)
    set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/gcc/linker/STM32U083xx_FLASH.ld)
    set(CMSIS_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Include)
    set(CMSIS_DEVICE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Include)
    set(CMSIS_STARTUP ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/gcc/startup_stm32u083xx.s)
    set(VENDOR_SYSTEM_INIT ${CMAKE_CURRENT_LIST_DIR}/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/system_stm32u0xx.c)
else()
    message("Error!")
endif()

add_compile_definitions(XMCU_SOC_VENDOR=${XMCU_SOC_VENDOR} XMCU_SOC_ARCH_CORE_FAMILY=${XMCU_SOC_ARCH_CORE_FAMILY} XMCU_SOC_VENDOR_FAMILY=${XMCU_SOC_VENDOR_FAMILY} XMCU_SOC_ARCH=${XMCU_SOC_ARCH} XMCU_SOC_ARM_CORE_FAMILY_NAME=${XMCU_SOC_ARM_CORE_FAMILY_NAME})
add_compile_definitions(XMCU_SOC_STM32_FAMILY=${XMCU_SOC_VENDOR_FAMILY} XMCU_SOC_VENDOR_FAMILY_RM=${XMCU_SOC_VENDOR_FAMILY_RM} XMCU_SOC_VENDOR_MODEL=${XMCU_SOC_VENDOR_MODEL})
add_compile_definitions(XMCU_ISR_CONTEXT=${XMCU_ISR_CONTEXT} ${CMSIS_SOC_MODEL} CMSIS_SOC_FILE=stm32u0xx.h)

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
                              ${CMAKE_CURRENT_LIST_DIR}"/syscalls.c"
                              ${CMAKE_CURRENT_LIST_DIR}"/sysmem.c"
                              ${CMAKE_CURRENT_LIST_DIR}"/soc/st/arm/CMSIS/Device/ST/STM32U0xx/Source/Templates/system_stm32u0xx.c"
                              ${CMSIS_STARTUP} 
                              ${VENDOR_SYSTEM_INIT} "soc/st/arm/systick.cpp" "soc/st/arm/stdglue.cpp" "soc/st/arm/m0/u0/rm0503/peripherals/USART/usart.cpp")

set(CFLAGS -Wall -Wextra -Wno-strict-aliasing -Werror -Wno-unused-parameter -I. -c -fno-common
           -mcpu=cortex-m0plus -mthumb -nostartfiles -nostdlib -mfloat-abi=softfp -mfpu=fpv4-sp-d16
           -ffast-math -ffunction-sections -fdata-sections -fsingle-precision-constant
           -DARM_MATH_CM0PLUS -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING)

set(CPPFLAGS ${CFLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CFLAGS ${CFLAGS} -Og -g3)
    set(CPPFLAGS ${CPPFLAGS} -Og -g3)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    set(CFLAGS ${CFLAGS} -Os)
    set(CPPFLAGS ${CPPFLAGS} -Os)
endif()

target_compile_options(${ELF_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:ASM,C>:${CFLAGS}>")
target_compile_options(${ELF_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CPPFLAGS}>")
        
set(MAIN_LDFLAGS_COMMON -mcpu=cortex-m0 -mthumb -nostartfiles -fno-exceptions -nostdlib -fno-rtti -Wl,--gc-sections -lc_nano)

set(OUTPUT_STEM out)
                         
target_link_options(${ELF_NAME} PRIVATE
        ${MCU_LD_OPTIONS} ${MAIN_LDFLAGS_COMMON}
        -Wl,-Map=${OUTPUT_STEM}.map,-cref,--print-memory-usage
        -T${LINKER_SCRIPT})
        
set_target_properties(${ELF_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Generating firmware .bin file"
)
                             


#[[
# MCU-specific
if (HKM_MODEL STREQUAL "STM32WB35CE")
set(MCU_DEFINES M4 STM32WB STM32WB35xx STM32WB35CE ARM_MATH_CM4 ARM_MATH_MATRIX_CHECK ARM_MATH_ROUNDING)
    set(CORTEX_FAMILY M4)
    set(CMSIS_STARTUP_FILE_PATH externals/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/startup_stm32wb35xx_cm4.s)
    set(CMSIS_SYSTEM_FILE_PATH externals/CMSIS/Device/ST/STM32WBxx/Source/Templates/system_stm32wbxx.c)
    set(CMSIS_INCLUDE_PATHS externals/CMSIS/Include externals/CMSIS/Device/ST/STM32WBxx/Include)
    set(LD_FILE_STEM STM32WB35CE)
    set(LINK_BLE ON)
    set(ENABLE_LOG_CAROUSEL ON)
    set(OPENOCD_CONFIG_STEM stm32wbx)
    set(FLASH_BASE_ADDRESS 0x8009000)
elseif (HKM_MODEL STREQUAL "STM32L010F4P6")
    set(CORTEX_FAMILY M0_PLUS)
    set(MCU_DEFINES STM32L0 STM32L0x0 STM32L010xx STM32L010x4 STM32L010F4P6)
    set(CMSIS_STARTUP_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l010x4.s)
    set(CMSIS_SYSTEM_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c)
    set(CMSIS_INCLUDE_PATHS externals/CMSIS/Include externals/CMSIS/Device/ST/STM32L0xx/Include)
    set(LD_FILE_STEM STM32L010F4Px_FLASH)
    set(OPENOCD_CONFIG_STEM stm32l0)
    set(FLASH_BASE_ADDRESS 0x8000000)
    set(PRINT_BUFFER_SIZE 100)
elseif (HKM_MODEL STREQUAL "STM32L011F4P6")
    set(CORTEX_FAMILY M0_PLUS)
    set(MCU_DEFINES STM32L0 STM32L0x1 STM32L011xx STM32L011x4 STM32L011F4P6)
    set(CMSIS_STARTUP_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l011x4.s)
    set(CMSIS_SYSTEM_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c)
    set(CMSIS_INCLUDE_PATHS externals/CMSIS/Include externals/CMSIS/Device/ST/STM32L0xx/Include)
    set(LD_FILE_STEM STM32L011F4Px_FLASH)
    set(OPENOCD_CONFIG_STEM stm32l0)
    set(FLASH_BASE_ADDRESS 0x8000000)
    set(PRINT_BUFFER_SIZE 100)
elseif (HKM_MODEL STREQUAL "STM32L011K4T6")
    set(CORTEX_FAMILY M0_PLUS)
    set(MCU_DEFINES STM32L0 STM32L0x1 STM32L011xx STM32L011x4 STM32L011K4P6)
    set(CMSIS_STARTUP_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l011x4.s)
    set(CMSIS_SYSTEM_FILE_PATH externals/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c)
    set(CMSIS_INCLUDE_PATHS externals/CMSIS/Include externals/CMSIS/Device/ST/STM32L0xx/Include)
    set(LD_FILE_STEM STM32L011K4Tx_FLASH)
    set(OPENOCD_CONFIG_STEM stm32l0)
    set(FLASH_BASE_ADDRESS 0x8000000)
    set(PRINT_BUFFER_SIZE 100)
else()
    message(FATAL_ERROR "Unsupported or not specified HKM_MODEL: '${HKM_MODEL}', use one of following: ${MODEL_TYPES}")
endif()

# Cortex-specific
if(CORTEX_FAMILY STREQUAL "M4")
    set(MCU_C_OPTIONS -mcpu=cortex-m4 -mthumb)
    set(MCU_DEFINES ${MCU_DEFINES} M4)
    set(SOC_DIR m4)
elseif(CORTEX_FAMILY STREQUAL "M0_PLUS")
    set(MCU_C_OPTIONS -mcpu=cortex-m0plus -mthumb)
    set(MCU_DEFINES ${MCU_DEFINES} M0_PLUS)
    set(SOC_DIR m0)
else()
    message(FATAL_ERROR "Unsupported or undefined CORTEX_FAMILY: '${CORTEX_FAMILY}'")
endif()
set(MCU_LD_OPTIONS ${MCU_C_OPTIONS}) # It may be different later

# TODO: build soc/hal as standalone cmake library
# Requires cleaning up build options/defines - some should be set as PUBLIC in soc/hal, some should be priorly set
# by main CMakeLists.txt.
# This should effectively render vars from large if-elses above not needed in code below but automatically
# inherited/linked by main project instead, but doing it properly requires some work and testing.

#----------------------------------------------------------------------------------------------------------- HAL/SOC END

set(FIRMWARE_TYPES "sim" "beth" "rick" "davin" "morty")
set(HKM_FIRMWARE "" CACHE STRING "Firmware variant")
set_property(CACHE HKM_FIRMWARE PROPERTY STRINGS ${FIRMWARE_TYPES})

if (NOT(HKM_FIRMWARE IN_LIST FIRMWARE_TYPES))
    message(FATAL_ERROR "Unsupported or not specified HKM_FIRMWARE: '${HKM_FIRMWARE}', use one of following: ${FIRMWARE_TYPES}")
endif()

#TODO: RELEASE_DEFINES?
set(DEBUG_DEFINES HKM_ASSERT_ENABLED)
if(ENABLE_LOG_CAROUSEL)
    set(DEBUG_DEFINES ${DEBUG_DEFINES} HKM_LOGGER_CAROUSEL_ENABLED)
endif()
set(SIM_DEFINES SIMULATOR)
add_compile_definitions(
    MBEDTLS_PK_PARSE_C MBEDTLS_ASN1_PARSE_C MBEDTLS_PK_C MBEDTLS_PEM_PARSE_C MBEDTLS_BASE64_C MBEDTLS_PLATFORM_C
    MBEDTLS_PLATFORM_MEMORY MBEDTLS_PLATFORM_NO_STD_FUNCTIONS MBEDTLS_DHM_C
    GIT_COMMIT_ID="${GIT_COMMIT_ID}" ${MCU_DEFINES}
    "$<$<STREQUAL:${HKM_FIRMWARE},sim>:${SIM_DEFINES}>"
    "$<$<CONFIG:Debug,RelWithDebInfo>:${DEBUG_DEFINES}>"
)
if(PRINT_BUFFER_SIZE)
    add_compile_definitions(HKM_PRINT_BUFFER_SIZE=${PRINT_BUFFER_SIZE})
endif()

set(DEBUG_OPTIONS -Og -g3)
set(RELEASE_OPTIONS -Os)
set(C_OPTIONS
    -Wall -Wextra -Wno-strict-aliasing -Werror -Wno-unused-parameter
    ${MCU_C_OPTIONS} -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -ffast-math
    -fno-common -ffunction-sections -fdata-sections -fsingle-precision-constant
)
set(CPP_OPTIONS
    -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics
)
add_compile_options(
    "$<$<COMPILE_LANGUAGE:ASM,C,CXX>:${C_OPTIONS}>"
    "$<$<COMPILE_LANGUAGE:CXX>:${CPP_OPTIONS}>"
    "$<$<CONFIG:Debug,RelWithDebInfo>:${DEBUG_OPTIONS}>"
    "$<$<CONFIG:Release,MinSizeRel>:${RELEASE_OPTIONS}>"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# External
file(GLOB EXTERNAL_src
    ${CMSIS_SYSTEM_FILE_PATH}
    externals/printf/*.c
)
add_library(external OBJECT ${EXTERNAL_src})
target_include_directories(external PUBLIC
    ${CMSIS_INCLUDE_PATHS}
    externals/printf
)

# Modules
file(GLOB_RECURSE MODULES_src
    modules/common/*.cpp modules/common/*.hpp
    modules/debug/*.cpp modules/debug/*.hpp
    modules/stdio/*.cpp modules/stdio/*.hpp
    modules/hal/*.cpp modules/hal/*.hpp
    # TODO: move to separate SOC/HAL cmake
    modules/soc/${SOC_DIR}/*.cpp modules/soc/${SOC_DIR}/*.hpp
)
add_library(modules OBJECT ${MODULES_src})
target_include_directories(modules PUBLIC
    modules
    ${CMAKE_CURRENT_LIST_DIR}
    "$<TARGET_PROPERTY:external,INCLUDE_DIRECTORIES>"
)

# Firmware
set(OUTPUT_STEM "${HKM_FIRMWARE}_${HKM_MODEL}")
if((CMAKE_BUILD_TYPE STREQUAL "Debug") OR (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
    set(OUTPUT_STEM "${OUTPUT_STEM}_d")
endif()
set(ELF_NAME ${OUTPUT_STEM}.elf)
set(BIN_NAME ${OUTPUT_STEM}.bin)
set(LST_NAME ${OUTPUT_STEM}.lst)
set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/projects/solo/ldscripts/${LD_FILE_STEM}.ld)
message(STATUS "Firmware file: '${BIN_NAME}'")

file(GLOB_RECURSE FIRMWARE_src
    projects/solo/${HKM_FIRMWARE}/*.c projects/solo/${HKM_FIRMWARE}/*.cpp projects/solo/${HKM_FIRMWARE}/*.hpp
)
add_executable(${ELF_NAME} ${FIRMWARE_src} ${CMSIS_STARTUP_FILE_PATH})
include(projects/solo/${HKM_FIRMWARE}/firmware.cmake) # Expected to set firmware-specific sources and defines
target_include_directories(${ELF_NAME} PRIVATE projects)
target_link_libraries(${ELF_NAME} PRIVATE modules external)
if(LINK_BLE)
    target_link_libraries(${ELF_NAME} PRIVATE ble wpan)
endif()
target_link_options(${ELF_NAME} PRIVATE
    ${MCU_LD_OPTIONS} -nostartfiles -fno-exceptions -nostdlib -fno-rtti -Wl,--gc-sections
    -Wl,-Map=${OUTPUT_STEM}.map,-cref,--print-memory-usage
    -T${LINKER_SCRIPT})
set_target_properties(${ELF_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Generating firmware .bin file"
)
add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -S ${ELF_NAME} > ${LST_NAME}
    COMMENT "Generating disassembly .lst file"
)

# TODO: move to soc/hal cmake
if(LINK_BLE)
    # BLE - WPAN
    file(GLOB WPAN_src
        externals/STM32_WPAN/*.c
        externals/STM32_WPAN/ble/*.c
        externals/STM32_WPAN/ble/core/*.c
        externals/STM32_WPAN/ble/core/auto/*.c
        externals/STM32_WPAN/ble/core/template/*.c
        externals/STM32_WPAN/ble/svc/*.c
        externals/STM32_WPAN/interface/patterns/ble_thread/*.c
        externals/STM32_WPAN/interface/patterns/ble_thread/shci/*.c
        externals/STM32_WPAN/interface/patterns/ble_thread/tl/*.c
        externals/STM32_WPAN/utilities/*.c
    )

    add_library(wpan OBJECT ${WPAN_src})
    target_include_directories(wpan PUBLIC
        externals/STM32_WPAN
        externals/STM32_WPAN/ble
        externals/STM32_WPAN/ble/core
        externals/STM32_WPAN/ble/core/template
        externals/STM32_WPAN/ble/svc
        externals/STM32_WPAN/interface/patterns/ble_thread
        externals/STM32_WPAN/interface/patterns/ble_thread/shci
        externals/STM32_WPAN/interface/patterns/ble_thread/tl
        externals/STM32_WPAN/utilities
        projects/solo/ble # TODO: CIRCULAR DEPENDENCY - THIS SHOULDN'T BE NEEDED
        "$<TARGET_PROPERTY:external,INCLUDE_DIRECTORIES>"
    )

    # BLE - MODULES
    # TODO: this shouldn't be needed - internal_flash WB HAL depends on WPAN headers - do it in cleaner way somehow
    target_include_directories(modules PUBLIC
        "$<TARGET_PROPERTY:wpan,INCLUDE_DIRECTORIES>"
    )
endif()

# SOLO/BLE
if(LINK_BLE)
    file(GLOB_RECURSE BLE_src projects/solo/ble/*.cpp projects/solo/ble/*.hpp)
    add_library(ble OBJECT ${BLE_src})
    target_include_directories(ble PUBLIC
        "$<TARGET_PROPERTY:modules,INCLUDE_DIRECTORIES>"
        "$<TARGET_PROPERTY:wpan,INCLUDE_DIRECTORIES>"
        ${CMAKE_CURRENT_LIST_DIR}/projects
    )
endif()

add_custom_target(flash_openocd
	COMMAND ${OPENOCD} -f interface/stlink.cfg -f target/${OPENOCD_CONFIG_STEM}.cfg
        -c "init"
        -c "reset init"
        -c "program ${CMAKE_BINARY_DIR}/${BIN_NAME} ${FLASH_BASE_ADDRESS} verify"
        -c "reset run"
        -c "shutdown"
    COMMENT "Flashing '${BIN_NAME}' via OpenOCD"
)

]]
