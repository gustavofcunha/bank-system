cmake_minimum_required(VERSION 3.10)
project(SeuProjeto)

# Configuração dos diretórios
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(OBJ_DIR ${CMAKE_SOURCE_DIR}/obj)

# Adiciona os arquivos fonte ao executável
add_executable(seu_programa ${SRC_DIR}/main.cpp ${SRC_DIR}/banco.cpp ${SRC_DIR}/conta.cpp ${SRC_DIR}/gerenciador_memoria.cpp)

# Configuração para encontrar a biblioteca assert
target_compile_definitions(seu_programa PRIVATE NDEBUG)

# Configuração dos diretórios de output
set_target_properties(seu_programa PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OBJ_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR}
)

# Adiciona os diretórios de include
target_include_directories(seu_programa PRIVATE ${INCLUDE_DIR})

# Adiciona o arquivo de testes
add_executable(testes ${TEST_DIR}/testes.cpp)

# Configuração para encontrar a biblioteca assert nos testes
target_compile_definitions(testes PRIVATE NDEBUG)

# Configuração dos diretórios de output para os testes
set_target_properties(testes PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OBJ_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR}
)

# Adiciona os diretórios de include nos testes
target_include_directories(testes PRIVATE ${INCLUDE_DIR})
