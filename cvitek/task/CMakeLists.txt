cmake_minimum_required(VERSION 3.16.5)

project(arch C ASM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_INSTALL_PREFIX ${TOP_DIR}/install)
set(CMAKE_INSTALL_INC_PREFIX ${TOP_DIR}/install/include)

set(SAFETY_FLAGS "-Wall -Wextra -fno-strict-aliasing -static --specs=nosys.specs")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SAFETY_FLAGS} -D${RUN_TYPE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SAFETY_FLAGS}")

add_subdirectory(comm)
add_subdirectory(rgn)
add_subdirectory(main)

set(BIN_DIR ${CMAKE_BINARY_DIR}/cvitek/task/main)

set(ELF_FILE ${BIN_DIR}/cvirtos.elf)
set(BIN_FILE ${BIN_DIR}/cvirtos.bin)

add_custom_target(cvirtos.bin
    DEPENDS cvirtos.elf
)
add_custom_command(TARGET cvirtos.bin
    COMMAND echo "Build cvirtos.bin and it depends on cvirtos.elf"
    POST_BUILD
    DEPENDS cvirtos.elf
    COMMAND ${CMAKE_OBJCOPY} ARGS ${ELF_FILE} -O binary ${BIN_FILE}
    COMMAND ${CMAKE_OBJDUMP} ARGS -dS ${ELF_FILE} > ${BIN_FILE}.dis
    VERBATIM
)

add_custom_target(arduino.elf
        DEPENDS cvirtos.elf
)

add_custom_command(TARGET arduino.elf
        COMMAND echo "Build arduino.elf"
        POST_BUILD
        DEPENDS cvirtos.elf
        COMMAND ${CMAKE_COMMAND} -E chdir ${BUILD_TOOLS}/burntools/burntool python3 burntool.py -p /dev/ttyACM0 -f ${ELF_FILE}
        VERBATIM
)

add_custom_target(fip.bin
        DEPENDS cvirtos.bin
)
add_custom_command(TARGET fip.bin
        COMMAND echo "Build fip.bin"
        POST_BUILD
        DEPENDS cvirtos.bin
        COMMAND  ${CMAKE_COMMAND} -E chdir ${BUILD_TOOLS}/fiptool make all rtos=${RTOS}
        VERBATIM
)
