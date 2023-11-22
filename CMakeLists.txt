cmake_minimum_required(VERSION 3.12)

# Define o projeto
project(BankSystem)

option(BUILD_TESTS "Build tests" OFF)

# Configuração do projeto principal
add_executable(main 
    src/main.cpp 
    src/banco.cpp 
    src/conta.cpp 
    src/gerenciador_memoria.cpp
)

# Adiciona os arquivos fonte do projeto (banco.cpp e conta.cpp)
file(GLOB PROJECT_SOURCES "src/*.cpp")

# Configuração do executável do teste
add_executable(testes testes.cpp ${PROJECT_SOURCES})

# Adiciona o diretório de inclusão
target_include_directories(testes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Adiciona o diretório de inclusão globalmente
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_TESTS)
    # Configuração do executável de testes
    add_executable(testes testes.cpp ${PROJECT_SOURCES})
    target_compile_definitions(testes PRIVATE RUN_TESTS)
endif()
