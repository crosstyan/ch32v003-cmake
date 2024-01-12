cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_LIST_DIR}/xpack-riscv-none-elf-gcc.cmake)
project(template-project C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FUN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fun)
file(GLOB FUN_SRC ${FUN_DIRECTORY}/ch32v003fun/*.c)
add_library(fun)
target_sources(fun PRIVATE ${FUN_SRC})
target_include_directories(fun PUBLIC ${FUN_DIRECTORY}/ch32v003fun)
target_include_directories(fun PUBLIC ${FUN_DIRECTORY}/extralibs)
target_include_directories(fun PUBLIC src/config)

add_executable(${CMAKE_PROJECT_NAME}.elf
        src/main.cpp
)

set_target_properties(${CMAKE_PROJECT_NAME}.elf PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ch32v003fun.ld
        LINK_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/ch32v003fun.ld -Wl,--wrap=malloc") # prevent malloc from being called

add_subdirectory(lib)

target_link_libraries(${CMAKE_PROJECT_NAME}.elf fun)

add_compile_definitions(
        SYSTICK_USE_HCLK=1
)

# Generate the binary file
add_custom_target(
        bin ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-objcopy -Obinary
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)

# Echo the size Information
add_custom_target(
        size ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-size "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)

# flash with minichlink
add_custom_target(
        flash COMMAND
        minichlink -w ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin flash -b
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin)

add_custom_command(
        USES_TERMINAL
        OUTPUT gdb-cmd
        COMMAND ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-gdb ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)
add_custom_target(gdb DEPENDS gdb-cmd)

add_custom_command(USES_TERMINAL OUTPUT gdb-server-cmd
        COMMAND minichlink -b -G)
add_custom_target(serve DEPENDS gdb-server-cmd)

add_custom_command(USES_TERMINAL OUTPUT monitor-cmd
        COMMAND minichlink -b -T)
add_custom_target(monitor DEPENDS monitor-cmd)
