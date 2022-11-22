set( CORE_SOURCE_FILES
    ../core/SpdLog.cpp 
    ../core/DynamicModule.cpp 
    ../core/RapidJsonParser.cpp 
    ../core/JsonParser.cpp 
    ../core/RawDataContainer.cpp
    ../core/Runner.cpp
    ../core/Engine.cpp
)
add_executable(main main.cpp  ${CORE_SOURCE_FILES})