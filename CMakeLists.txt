# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

# Define o projeto
project(MyArduinoTests)

option(BUILD_TESTS "Build tests" OFF)

# Configuração do projeto principal
add_executable(main src/main.cpp src/banco.cpp src/conta.cpp src/gerenciador_memoria.cpp)

# Adiciona os arquivos fonte do teste (assumindo que testes.cpp está no diretório raiz)
file(GLOB SOURCES "*.cpp")

# Adiciona os arquivos fonte do projeto (banco.cpp e conta.cpp)
file(GLOB PROJECT_SOURCES "src/*.cpp")

# Configuração do executável do teste
add_executable(MyArduinoTests ${SOURCES} ${PROJECT_SOURCES})

# Adiciona o diretório de inclusão
target_include_directories(MyArduinoTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(MyArduinoTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Adiciona o diretório de inclusão globalmente (pode não ser necessário, dependendo da estrutura do projeto)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_TESTS)
    add_executable(testes testes.cpp src/banco.cpp src/conta.cpp src/gerenciador_memoria.cpp)
    target_compile_definitions(testes PRIVATE RUN_TESTS)
endif()

