
cmake_minimum_required(VERSION 3.27)
project(AlcoInput CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories("inc")
set(INC_FILES
    "inc/AlcoInput.hpp"
    "inc/key.hpp"
    "inc/Keyboard.hpp"
    "inc/Mouse.hpp"
)
set(SRC_FILES
    "src/AlcoInput.cpp"
    "src/Keyboard.cpp"
    "src/Mouse.cpp"
)

add_library(${PROJECT_NAME} STATIC ${INC_FILES} ${SRC_FILES})
