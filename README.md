## Autor

Este sistema foi criado por Gustavo Freitas Cunha, para a disciplina de Enegenharia de Software II, do curso de graduação em Sistemas de Informação da  Universidade Federal de Minas Gerais. Gustavo pode ser contatado pelo endereço eletrônico `gustavocunha@dcc.ufmg.br`.

## Sistema Bancário Simples em C++

Este é um sistema bancário simples implementado em C++. Ele permite que os usuários realizem operações bancárias básicas, como abrir uma conta, depositar, sacar, verificar o saldo, transferir entre contas e encerrar uma conta.

## Funcionalidades do Sistema

O sistema possui as seguintes funcionalidades:

1. **Abrir Conta:** Os usuários podem abrir uma nova conta fornecendo o nome do titular e uma senha. O número da conta é gerado automaticamente.

2. **Depositar:** Os titulares de conta podem fazer depósitos em suas contas.

3. **Sacar:** Os titulares de conta podem sacar dinheiro de suas contas, desde que tenham saldo suficiente.

4. **Verificar Saldo:** Os titulares de conta podem verificar o saldo de suas contas.

5. **Transferir:** Os titulares de conta podem transferir dinheiro para outras contas, desde que a conta de origem tenha saldo e a conta de destino exista, de fato.

6. **Encerrar Conta:** Os titulares de conta podem encerrar suas contas.

7. **Senhas:** O sistema implementa senhas para garantir a segurança das transações.

8. **Persistência de Dados:** Os dados do sistema, inclusive transacionais, são armazenados em dois arquivos: "files/dadosContas.txt" e "files/dadosTransacoes.txt", permitindo que os dados persistam entre as execuções do sistema. Caso você deseje limpar a memória do sistema, basta esvaziar esses arquivos.

## Tecnologias Utilizadas

Este sistema bancário é implementado em C++, uma linguagem de programação de alto desempenho e amplamente utilizada. Além disso, ele faz uso de:

- **STL (Standard Template Library):** A STL do C++ é usada para trabalhar com estruturas de dados, como vetores e strings.

- **Arquivos:** O sistema armazena e lê dados a partir de arquivos para manter a persistência de dados.

## Compilação e Execução

Para compilar o sistema, você pode usar o arquivo `Makefile`. Basta executar o comando `make` no terminal.

Isso irá compilar o código-fonte e gerar um executável chamado `banco.exe`.

Para executar o sistema, use o seguinte comando:

`./bin/banco.exe`