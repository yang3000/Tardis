# 设置变量
SET(SERIALPORT_LIB_SRC 
./SerialPort.h 
./SerialPort.cpp
../../src/core/CallerContainer.cpp)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../src/app)

add_library(serial_port_lib SHARED ${SERIALPORT_LIB_SRC})

INSTALL(TARGETS serial_port_lib)

SET_TARGET_PROPERTIES(serial_port_lib PROPERTIES LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "serial_port_lib"
        PREFIX "")