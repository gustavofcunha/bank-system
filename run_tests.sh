# Configuração dos diretórios
BIN_DIR="./bin"

# Compilar os testes
cmake -S . -B build
cmake --build build --target testes -- -j$(nproc)

# Executar os testes
${BIN_DIR}/testes

# Verificar o status de saída
if [ $? -eq 0 ]; then
    echo "Testes passaram com sucesso!"
else
    echo "Testes falharam."
fi
