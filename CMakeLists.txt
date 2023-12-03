cmake_minimum_required(VERSION 3.12)
project(bank)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Find GoogleTest
find_package(GTest REQUIRED)

# Add your main executable
add_executable(main
    src/main.cpp
    src/banco.cpp
    src/conta.cpp
    src/gerenciador_memoria.cpp
    # Add other source files as needed
)

# Add your test executable
add_executable(MyArduinoTests
    testes.cpp
    src/banco.cpp
    src/conta.cpp
    src/gerenciador_memoria.cpp
    # Add other source files as needed
)

# Link GoogleTest to your test executable
target_link_libraries(MyArduinoTests GTest::GTest GTest::Main)

# Include the source directory for header files
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(MyArduinoTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Optionally, you can enable testing using CTest
include(GoogleTest)
gtest_discover_tests(MyArduinoTests)
