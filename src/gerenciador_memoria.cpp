#include "gerenciador_memoria.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

GerenciadorMemoria::GerenciadorMemoria(){}

void GerenciadorMemoria::salvarDadosContas(const std::vector<Conta>& contas) {
    std::ofstream file("files/dadosContas.txt");
    
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar dados." << std::endl;
        return;
    }

    for (const Conta& conta : contas) {
        file << conta.getTitular() << '/' << conta.getNumeroConta() << '/' << conta.consultarSaldo() << '/' << conta.getSenha() << '\n';
    }

    file.close();
}

std::vector<Conta> GerenciadorMemoria::carregarDadosContas() {
    std::vector<Conta> contas;
    std::ifstream file("files/dadosContas.txt");
    std::string dado, titular, senha;
    int numeroConta;
    double saldo;

    if (!file.is_open()) {
        std::cerr << "Arquivo de dados não encontrado. Criando novo arquivo." << std::endl;
        return contas;
    }

    try {
        std::string linha;

        while (std::getline(file, linha)) {
            std::istringstream iss(linha);
            
            std::getline(iss, dado, '/');
            titular = dado;
            std::getline(iss, dado, '/');
            numeroConta = std::stoi(dado);
            std::getline(iss, dado, '/');
            saldo = std::stod(dado);
            std::getline(iss, dado, '/');
            senha = dado;
            Conta novaConta(numeroConta, titular, senha);
            novaConta.depositar(saldo, false);

            contas.push_back(novaConta);
        }

        file.close();
    } 
    
    catch (const std::exception& e) {
        std::cerr << "Erro ao ler dados do arquivo: " << e.what() << std::endl;
    }

    return contas;
}

void GerenciadorMemoria::carregarDadosTransacoes(std::vector<Conta>& contas) {
    std::ifstream file("files/dadosTransacoesContas.txt");
    if (file.is_open()) {
        int numeroConta;
        std::string transacao;

        while (file >> numeroConta) {
            std::getline(file >> std::ws, transacao);
            
            for (auto& conta : contas) {
                if (conta.getNumeroConta() == numeroConta) {
                    conta.historico.push_back(transacao);
                }
            }
        }

        file.close();
    }
}

void GerenciadorMemoria::salvarDadosTransacoes(int numeroConta, const std::string& transacao) {
    std::ofstream file("files/dadosTransacoesContas.txt", std::ios::app); 
    if (file.is_open()) {
        file << numeroConta << ' ' << transacao << '\n';
        file.close();
    }   
}
