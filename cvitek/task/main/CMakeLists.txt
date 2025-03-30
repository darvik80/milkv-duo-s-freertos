file(GLOB _SOURCES "src/*.c" "*.S")

# try to find out the include folder recursively under CMAKE_INSTALL_PREFIX folder
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${CMAKE_INSTALL_PREFIX}/*.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_dir_list)
list(LENGTH header_dir_list header_dir_list_count)

include_directories(include)
include_directories(${header_dir_list})

#if (CONFIG_FAST_IMAGE_TYPE STRGREATER "0")
#    set(CVI_TASK_LIBS comm isp vi vcodec rgn audio camera)
#else()
    set(CVI_TASK_LIBS comm rgn_main audio arch common commonl kernel hal driver)
#endif()

set(LINKER_SCRIPT "${TOP_DIR}/scripts/${RUN_CHIP}_lscript.ld")
set(EXTRA_LIBS ${EXTRA_LIBS} "-L${BUILD_ENV_PATH}/output/$ENV{PROJECT_FULLNAME}")
set(EXTRA_LIBS ${EXTRA_LIBS} "-L${TOP_DIR}/task/audio/" audio)
set(EXTRA_LIBS ${EXTRA_LIBS} m c gcc sim)
set(CMAKE_EXE_LINKER_FLAGS -T${LINKER_SCRIPT} )
set(BUILD_SHARED_LIBS OFF)

add_executable(cvirtos.elf ${_SOURCES})

set(BIN_DIR ${CMAKE_BINARY_DIR}/cvitek/task/main)

target_link_options(cvirtos.elf PRIVATE -static)
target_link_libraries(cvirtos.elf PRIVATE -Wl,--start-group ${CVI_TASK_LIBS} ${CVI_LIBS} ${EXTRA_LIBS} -Wl,--end-group -Wl,-Map=${BIN_DIR}/cvirtos.map)

install(TARGETS cvirtos.elf DESTINATION bin)
install(FILES ${CMAKE_BINARY_DIR}/cvirtos.map DESTINATION bin)
