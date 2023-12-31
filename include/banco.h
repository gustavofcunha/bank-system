#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include "conta.h"

class Banco {
private:
    std::vector<Conta> contas;

public:
    Banco();
    Banco(const std::vector<Conta>& contas);
    void abrirConta();
    void depositar();
    void sacar();
    void consultarSaldo();
    void transferir();
    void encerrarConta();
    void verExtratoConta();
    void verInformacoesConta();
    Conta* procuraConta(int numeroConta);
    const std::vector<Conta>& getContas();
    int maiorNumeroConta();
    bool verificarSenha(Conta& conta);
};

#endif
