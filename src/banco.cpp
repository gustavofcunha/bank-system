#include "banco.h"
#include "conta.h"
#include <iostream>
#include "gerenciador_memoria.h"

GerenciadorMemoria gerenciadorMemoriaBanco;

Banco::Banco(){}

Banco::Banco(const std::vector<Conta>& contas) : contas(contas) {}

int Banco::maiorNumeroConta(){
    int maior = 0;
    for (auto& conta : contas) {
        if (conta.getNumeroConta() > maior) {   
            maior = conta.getNumeroConta();
        }
    }
    return maior;
}

void Banco::abrirConta() {
    std::string titular, senha;
    std::cout << "Digite o nome completo do titular da conta: ";
    std::cin.ignore(); // Ignorar o caractere de nova linha deixado pelo cin anterior
    std::getline(std::cin, titular);
    std::cout << "Digite a senha da conta: ";
    std::cin >> senha;
    int maiorNumeroConta = this->maiorNumeroConta();
    Conta conta(maiorNumeroConta+ 1, titular, senha);
    contas.push_back(conta);
    std::cout << "Conta criada com sucesso. Número da conta: " << conta.getNumeroConta() << std::endl;
}

bool Banco::verificarSenha(Conta& conta) {
    std::string senha;
    std::cout << "Digite a senha da conta: ";
    std::cin >> senha;
    if (senha != conta.getSenha()) {
        return false;
    }
    return true;
}


void Banco::depositar() {
    int numeroConta;
    double valor;

    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;
    Conta *conta = this->procuraConta(numeroConta);
    if(!conta){
        std::cout << "Conta não encontrada." << std::endl;
        return;
    }
    
    /*if(!this->verificarSenha(*conta)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }*/
    
    std::cout << "Digite o valor a ser depositado: ";
    std::cin >> valor;
    
    conta->depositar(valor, true);
    std::cout << "Depósito realizado com sucesso." << std::endl;
}

void Banco::sacar() {
    int numeroConta;
    double valor;

    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;
    Conta *conta = this->procuraConta(numeroConta);
    if(!conta){
        std::cout << "Conta não encontrada." << std::endl;
        return;
    }
    
    if(!this->verificarSenha(*conta)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }

    std::cout << "Digite o valor a ser sacado: ";
    std::cin >> valor;
    if (conta->sacar(valor, true)) {
        std::cout << "Saque realizado com sucesso." << std::endl;
    } 
    else {
        std::cout << "Saldo insuficiente." << std::endl;
    }
}

void Banco::consultarSaldo() {
    int numeroConta;

    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;
    Conta *conta = this->procuraConta(numeroConta);
    if(!conta){
        std::cout << "Conta não encontrada." << std::endl;
        return;
    }
    
    if(!this->verificarSenha(*conta)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }

    std::cout << "Saldo: " << conta->consultarSaldo() << std::endl;
}

Conta* Banco::procuraConta(int numeroConta){
    for (auto& conta : contas) {
        if (conta.getNumeroConta() == numeroConta) {   
            return &conta;
        }
    }
    return nullptr;
}

void Banco::transferir() {
    int numeroContaOrigem, numeroContaDestino;
    std::string transacao;
    double valor;

    std::cout << "Digite o número da conta de origem: ";
    std::cin >> numeroContaOrigem;
    Conta *contaOrigem = this->procuraConta(numeroContaOrigem);
    if(!contaOrigem){
        std::cout << "Conta de origem não encontrada." << std::endl;
        return;
    }

   if(!this->verificarSenha(*contaOrigem)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }

    std::cout << "Digite o número da conta de destino: ";
    std::cin >> numeroContaDestino;
    Conta *contaDestino = this->procuraConta(numeroContaDestino);
    
    if(!contaDestino){

        //registra tentativa no extrato de transacoes
        transacao = "Tentativa de transferência para a conta " + 
        std::to_string(numeroContaDestino) + ", que não existe.";
        contaOrigem->historico.push_back(transacao);
        gerenciadorMemoriaBanco.salvarDadosTransacoes(numeroContaOrigem, transacao);

        std::cout << "Conta de destino não encontrada." << std::endl;
        return;
    }
    
    std::cout << "Digite o valor a ser transferido: ";
    std::cin >> valor;

    //se houver saldo suficiente
    if (contaOrigem->sacar(valor, false)) {
        contaDestino->depositar(valor, false);

        transacao = "Transferência de " + 
        std::to_string(valor) + " realizada para conta " + 
        std::to_string(numeroContaDestino);
        gerenciadorMemoriaBanco.salvarDadosTransacoes(numeroContaOrigem, transacao);
        contaOrigem->historico.push_back(transacao);

        transacao = "Transferência de " + 
        std::to_string(valor) + " recebida da conta número " + 
        std::to_string(numeroContaOrigem);
        gerenciadorMemoriaBanco.salvarDadosTransacoes(numeroContaDestino, transacao);
        contaDestino->historico.push_back(transacao);

        std::cout << "Transferência realizada com sucesso." << std::endl;
    } 
    
    //sem saldo suficiente
    else {
        transacao = "Tentativa de transferência de " + 
        std::to_string(valor) + "  para conta " + 
        std::to_string(numeroContaDestino) + 
        ", mas a conta de origem não possuía saldo suficiente no momento da tentativa.";
        contaOrigem->historico.push_back(transacao);
        gerenciadorMemoriaBanco.salvarDadosTransacoes(numeroContaOrigem, transacao);

        std::cout << "Saldo insuficiente." << std::endl;
        return;
    }

    return;
}

void Banco::encerrarConta() {
    int numeroConta;
    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;

    auto it = contas.begin(); // Inicializa um iterador para o início do vetor

    while (it != contas.end()) {
        if (it->getNumeroConta() == numeroConta) {
            
            if(!this->verificarSenha(*it)){
                std::cout << "Senha incorreta." << std::endl;
                return;
            }

            it = contas.erase(it); // Remove a conta e atualiza o iterador
            std::cout << "Conta encerrada com sucesso." << std::endl;

            return;
        }
        ++it; // Avança para o próximo elemento do vetor
    }

    std::cout << "Conta não encontrada." << std::endl;
}

void Banco::verExtratoConta(){
    int numeroConta;

    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;
    Conta *conta = this->procuraConta(numeroConta);
    if(!conta){
        std::cout << "Conta não encontrada." << std::endl;
        return;
    }
    
    if(!this->verificarSenha(*conta)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }

    conta->exibirHistorico();
}

void Banco::verInformacoesConta(){
    int numeroConta;

    std::cout << "Digite o número da conta: ";
    std::cin >> numeroConta;
    Conta *conta = this->procuraConta(numeroConta);
    if(!conta){
        std::cout << "Conta não encontrada." << std::endl;
        return;
    }
    
    if(!this->verificarSenha(*conta)){
        std::cout << "Senha incorreta." << std::endl;
        return;
    }

    std::cout << std::endl << "Sumário de Informações da Conta Número " 
    << conta->getNumeroConta() << ":" << std::endl;

    std::cout << "Titular: " << conta->getTitular() << std::endl;
    std::cout << "Saldo: " << conta->consultarSaldo() << std::endl;
}

const std::vector<Conta>& Banco::getContas() {
    return contas;
}
