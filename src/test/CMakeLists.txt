set( CORE_SOURCE_FILES
    #Application.cpp
    Test.cpp
    ../core/SpdLog.cpp 
    ../core/DynamicModule.cpp 
    ../core/RapidJsonParser.cpp 
    ../core/JsonParser.cpp 
    ../core/RawDataContainer.cpp
    ../core/Runner.cpp
    ../core/Engine.cpp
)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)

#set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/lib)

add_executable(test Test.cpp  ${CORE_SOURCE_FILES})


target_link_libraries(test DbgHelp.lib d3d12.lib d3dcompiler.lib dxgi.lib)

