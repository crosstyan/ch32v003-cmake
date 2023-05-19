cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_LIST_DIR}/xpack-riscv-none-elf-gcc.cmake)
project(simple)
enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(VENDOR_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

file(GLOB VENDOR_CORE_SRC       ${VENDOR_DIRECTORY}/Core/*.c)
file(GLOB VENDOR_DEBUG_SRC      ${VENDOR_DIRECTORY}/Debug/*.c)
file(GLOB VENDOR_PERIPHERAL_SRC ${VENDOR_DIRECTORY}/Peripheral/src/*.c)
set(VENDOR_STARTUP_SRC ${VENDOR_DIRECTORY}/Startup/startup_ch32v00x.S)
set(VENDOR_SRC  ${VENDOR_STARTUP_SRC} ${VENDOR_CORE_SRC} ${VENDOR_DEBUG_SRC} ${VENDOR_PERIPHERAL_SRC})

include_directories(${VENDOR_DIRECTORY}/Core)
include_directories(${VENDOR_DIRECTORY}/Debug)
include_directories(${VENDOR_DIRECTORY}/Peripheral/inc)

file(GLOB SYSTEM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c)
include_directories(src/system)

set(APP_SRC src/main.cpp)
add_executable(${CMAKE_PROJECT_NAME}.elf ${VENDOR_SRC} ${SYSTEM_SRC} ${APP_SRC})

# Generate the binary file
add_custom_target(
        bin COMMAND
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-objcopy -Obinary
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)

# Generate the hex file
add_custom_target(
        hex COMMAND
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-objcopy -Oihex
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)

# Echo the size Infomation
add_custom_target(
        size COMMAND
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-size "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)

# flash with minichlink
add_custom_target(
        flash COMMAND
        minichlink -w ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin flash -b
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin)
