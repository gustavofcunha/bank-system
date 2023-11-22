# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(SeuProjeto CXX)

# Defina a variável RUN_TESTS ao compilar os testes
option(BUILD_TESTS "Build tests" OFF)

# Configuração do projeto principal
add_executable(main src/main.cpp src/banco.cpp src/conta.cpp src/gerenciador_memoria.cpp)

# ... outras configurações para o projeto principal

# Adicione a definição de compilador se estiver construindo os testes
if(BUILD_TESTS)
    add_executable(testes testes.cpp src/banco.cpp src/conta.cpp src/gerenciador_memoria.cpp)
    target_compile_definitions(testes PRIVATE RUN_TESTS)
endif()
