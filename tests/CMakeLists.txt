cmake_minimum_required(VERSION 3.12)

project(MyArduinoTests)

file(GLOB SOURCES "*.cpp")

add_executable(MyArduinoTests ${SOURCES})

target_include_directories(MyArduinoTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(MyArduinoTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
