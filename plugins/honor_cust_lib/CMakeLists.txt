# 设置变量
SET(HONOR_CUST_LIB_SRC ./HonorCust4Dongle.h ./HonorCust4Dongle.cpp ../../src/core/Plugin.cpp ../../src/core/CallerContainer.cpp ../../src/core/DynamicModule.cpp)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../src/app)

# 第一个参数为你需要构建的dll的名字，第二个为类型
add_library(honor_cust_lib SHARED ${HONOR_CUST_LIB_SRC})
INSTALL(TARGETS honor_cust_lib)
# 为dll设置linker
# 指定dll的生成目录，这里是：./lib_out
SET_TARGET_PROPERTIES(honor_cust_lib PROPERTIES LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "honor_cust_lib"
        PREFIX "")