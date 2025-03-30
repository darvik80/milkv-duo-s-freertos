cmake_minimum_required(VERSION 3.20)

include(toolchain-riscv64-elf.cmake)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(freertos C ASM)

set(RUN_ARCH riscv64)
set(RUN_TYPE CVIRTOS)
set(RUN_CHIP cv181x)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/cvitek/install)
set(CMAKE_INSTALL_INC_PREFIX ${CMAKE_SOURCE_DIR}/cvitek/install/include)

set(KERNEL_SOURCE ${CMAKE_SOURCE_DIR}/Source)
set(TRACE_SOURCE ${CMAKE_SOURCE_DIR}/Tracealyzer)
set(CVITEK ${CMAKE_SOURCE_DIR}/cvitek)
set(TOP_DIR ${CVITEK})
set(BUILD_TOOLS ${CMAKE_SOURCE_DIR}/tools)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SAFETY_FLAGS} -D${RUN_TYPE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SAFETY_FLAGS}")

include(${CMAKE_SOURCE_DIR}/cvitek/scripts/ParseConfiguration.cmake)
ParseConfiguration("${CMAKE_SOURCE_DIR}/.config")

include_directories(
        include
        ${KERNEL_SOURCE}/include
        ${KERNEL_SOURCE}/portable/GCC/RISC-V
        ${CVITEK}/kernel/include/${RUN_ARCH}
        ${CVITEK}/arch/${RUN_ARCH}/include
        ${CVITEK}/common/include/${RUN_ARCH}
        ${CVITEK}/common/include/interdrv/common
        ${CVITEK}/common/include/interdrv/chip/${RUN_ARCH}
        ${CVITEK}/driver/spinlock/include
        ${CVITEK}/driver/jenc/include
        ${CVITEK}/driver/rtos_cmdqu/include
        ${CVITEK}/driver/fast_image/include
        ${CVITEK}/driver/rgn/common/include
        ${CVITEK}/hal/${RUN_CHIP}/config
        ${CVITEK}/hal/${RUN_CHIP}/uart/include
        ${CVITEK}/hal/${RUN_CHIP}/pinmux/include
)

add_subdirectory(cvitek/arch)
add_subdirectory(cvitek/kernel)
add_subdirectory(cvitek/common)
add_subdirectory(cvitek/hal/cv181x)
add_subdirectory(cvitek/driver)
add_subdirectory(cvitek/task)

set(RTOS ${CMAKE_BINARY_DIR}/cvitek/task/main/cvirtos.bin)
set(RTOS_ELF ${CMAKE_BINARY_DIR}/cvitek/task/main/cvirtos.elf)

