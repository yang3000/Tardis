cmake_minimum_required(VERSION 3.10)
project( tardis_core )
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_compile_options("/std:c++17")

add_compile_definitions(FMT_HEADER_ONLY)
add_compile_definitions(RAPIDJSON_HAS_STDSTRING)
#add_compile_definitions(_HAS_STD_BYTE 0)
include_directories(vendor/fmt/include)
include_directories(vendor/spdlog/include)
include_directories(vendor/rapidjson/include)

include_directories(src/core)
include_directories(src/ui)
include_directories(src/communication)

#include_directories(src/lib)



#add_subdirectory(src/core)
#add_subdirectory(demo)
#add_subdirectory(plugins/write_imei)
add_subdirectory(src/app)
add_subdirectory(src/communication)
#add_subdirectory(plugins/write_imei)
add_subdirectory(plugins/honor_cust_lib)