cmake_minimum_required(VERSION 2.8)

project(TP)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -pedantic")

add_library(sdldemo
 //EJEMPLO Arma/SocketParameterError.h
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (main
 //MAIN!!!!!!!! src/main.cpp  
)


target_link_libraries(main)

