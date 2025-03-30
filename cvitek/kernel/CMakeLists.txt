cmake_minimum_required(VERSION 3.16.5)

project(kernel C ASM)

set(SAFETY_FLAGS "-Wall -Wextra -fno-strict-aliasing -static --specs=nosys.specs -D__BUILD_RTOS_KERNEL__")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SAFETY_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SAFETY_FLAGS}")

file(GLOB _SOURCES
    "${KERNEL_SOURCE}/*.c"
    "${KERNEL_SOURCE}/portable/GCC/RISC-V/*.c"
    "${KERNEL_SOURCE}/portable/GCC/RISC-V/*.S"
    "${KERNEL_SOURCE}/portable/MemMang/heap_4.c"
    "${TRACE_SOURCE}/src/*.c"
)

include_directories(include/${RUN_ARCH})
include_directories(${CMAKE_INSTALL_INC_PREFIX}/arch)
include_directories(${CMAKE_INSTALL_INC_PREFIX}/common)

include_directories(${KERNEL_SOURCE}/portable/GCC/RISC-V)
include_directories(${KERNEL_SOURCE}/portable/GCC/RISC-V/chip_specific_extensions/thead_c906_rv64imafdc/)
include_directories(${KERNEL_SOURCE}/include)
include_directories(${TRACE_SOURCE}/include)
include_directories(${TRACE_SOURCE}/config)

file(GLOB _HEADERS "include/${RUN_ARCH}/*.h"
                   "${KERNEL_SOURCE}/include/*.h"
                   "${KERNEL_SOURCE}/portable/GCC/RISC-V/*.h"
                   "${KERNEL_SOURCE}/portable/GCC/RISC-V/chip_specific_extensions/thead_c906_rv64imafdc/*.h"
                   "${TRACE_SOURCE}/include/*.h"
                   "${TRACE_SOURCE}/config/*.h"
)

add_library(kernel STATIC ${_SOURCES})

install(TARGETS kernel DESTINATION lib)
install(FILES ${_HEADERS} DESTINATION include/kernel)
