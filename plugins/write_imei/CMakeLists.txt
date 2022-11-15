# 设置变量
SET(LIBHELLO_SRC ./WriteImeiPlugin.h ./WriteImeiPlugin.cpp ../../src/core/CallerContainer.cpp ../../src/core/Plugin.cpp)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib_out)

# 第一个参数为你需要构建的dll的名字，第二个为类型
add_library(write_imei_dll SHARED ${LIBHELLO_SRC})
INSTALL(TARGETS write_imei_dll)
# 为dll设置linker
# 指定dll的生成目录，这里是：./lib_out
SET_TARGET_PROPERTIES(write_imei_dll PROPERTIES LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "write_imei_dll"
        PREFIX "")