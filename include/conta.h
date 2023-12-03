#ifndef CONTA_H
#define CONTA_H

#include <string>
#include <vector>


class Conta {
private:
    int numeroConta;
    std::string titular;
    double saldo;
    std::string senha;
    

public:
    std::vector<std::string> historico;
    Conta(int numero, std::string titular, std::string senha);
    void depositar(double valor, bool registrar) const;
    bool sacar(double valor, bool registrar) const;
    double consultarSaldo() const; 
    int getNumeroConta() const; 
    const std::string& getTitular() const; 
    const std::string& getSenha() const; 
    void exibirHistorico() const;
};

#endif
