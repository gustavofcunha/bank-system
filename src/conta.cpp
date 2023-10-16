#include <iostream>
#include "gerenciador_memoria.h"
#include "conta.h"

GerenciadorMemoria gerenciadorMemoria;

Conta::Conta(int numero, std::string titular, std::string senha) : numeroConta(numero), titular(titular), saldo(0.0), senha(senha) {}

void Conta::depositar(double valor, bool registrar) {
    saldo += valor;

    if(registrar){
        std::string transacao = "Depósito de " + std::to_string(valor) + " realizado.";
        historico.push_back(transacao);
        gerenciadorMemoria.salvarDadosTransacoes(numeroConta, transacao);
    }
}

bool Conta::sacar(double valor, bool registrar) {
    if (saldo >= valor) {
        saldo -= valor;
        if(registrar){
            
            std::string transacao = "Saque de " + std::to_string(valor) + " realizado.";
            historico.push_back(transacao);
            gerenciadorMemoria.salvarDadosTransacoes(numeroConta, transacao);
        }
        return true;
    } 
    
    else {
        if(registrar){
            std::string transacao = "Tentativa de saque de " + std::to_string(valor) + " realizado.";
            historico.push_back(transacao);
            gerenciadorMemoria.salvarDadosTransacoes(numeroConta, transacao);
        }
        return false;
    }
}

double Conta::consultarSaldo() const { 
    return saldo;
}

int Conta::getNumeroConta() const { 
    return numeroConta;
}

const std::string& Conta::getTitular() const { 
    return titular;
}

const std::string& Conta::getSenha() const { 
    return senha;
}

void Conta::exibirHistorico() const {
    std::cout << std::endl << "Histórico de transações da conta " 
    << numeroConta << ":" << std::endl;
    
    for (const std::string& transacao : historico) {
        std::cout << transacao << std::endl;
    }
}

