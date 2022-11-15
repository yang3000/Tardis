cmake_minimum_required(VERSION 3.10)
project( tardis_core )
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(FMT_HEADER_ONLY)
include_directories(vendor/fmt/include)
include_directories(vendor/spdlog/include)

include_directories(src/core)
#include_directories(src/lib)

#add_subdirectory(src/core)
#add_subdirectory(demo)
#add_subdirectory(plugins/write_imei)
add_subdirectory(src/app)
#add_subdirectory(plugins/write_imei)