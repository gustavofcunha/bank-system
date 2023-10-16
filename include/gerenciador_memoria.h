#ifndef GERENCIADOR_MEMORIA_H
#define GERENCIADOR_MEMORIA_H

#include "conta.h"
#include <vector>
#include <string>
#include <map>
#include <set> 

class GerenciadorMemoria {
public:
    GerenciadorMemoria();

    std::vector<Conta> carregarDadosContas();
    void carregarDadosTransacoes(std::vector<Conta>& contas);
    void salvarDadosContas(const std::vector<Conta>& contas);
    void salvarDadosTransacoes(int numeroConta, const std::string& transacao);

private:
    std::vector<Conta> contas;
};

#endif
