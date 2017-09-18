cmake_minimum_required(VERSION 3.7)
project(SemanticAnalysis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Logic/Variable.cpp Logic/Variable.h Logic/Procedimiento.cpp Logic/Procedimiento.h)
add_executable(SemanticAnalysis ${SOURCE_FILES})


