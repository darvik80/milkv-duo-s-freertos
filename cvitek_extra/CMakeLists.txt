cmake_minimum_required(VERSION 3.20)
project(cvitek_extra)

file(GLOB _SOURCES
        "src/bsp/*.c"
        "src/bsp/drivers/*.c"
        "src/bsp/hal/*.c"
        "src/bsp/hal/dw/*.c"
        "src/bsp/startup/*.S"
        "src/bsp/startup/*.c"
        "src/variants/duos/*.c"
)

include_directories(
        src/bsp/include
        src/bsp/include/csi
        src/bsp/include/cvi
        src/bsp/include/hal
        src/bsp/include/hal/dw
        src/variants/duos
)

add_library(${PROJECT_NAME} STATIC ${_SOURCES})
