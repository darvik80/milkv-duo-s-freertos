cmake_minimum_required(VERSION 3.30)
project(arduino)

file(GLOB _SOURCES
        "src/*.c"
        "src/bsp/drivers/*.c"
        "src/bsp/hal/*.c"
        "src/bsp/hal/dw/*.c"
        "src/bsp/startup/*.S"
        "src/bsp/startup/*.c"
        "src/duos/*.c"
)

include_directories(
        #src
        src/csi
        src/bsp
        src/bsp/csi
        src/bsp/cvi
        src/bsp/drivers
        src/bsp/hal/dw
        src/bsp/hal
        src/duos
)


add_library(${PROJECT_NAME} STATIC ${_SOURCES})
