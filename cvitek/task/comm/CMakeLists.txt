file(GLOB _SOURCES src/${RUN_ARCH}/*.c)

#if (CONFIG_FAST_IMAGE_TYPE STRGREATER "0")
#add_compile_definitions(FAST_IMAGE_ENABLE)
#endif()

include_directories(
        include
)

add_library(comm STATIC ${_SOURCES})
install(TARGETS comm DESTINATION lib)

