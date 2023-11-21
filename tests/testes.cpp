#include <iostream>
#include <assert.h>
#include "banco.h"
#include "conta.h"

void testAbrirConta() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    assert(!contas.empty());
}

void testDepositar() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    double saldoAntes = contas[0].consultarSaldo();
    banco.depositar();
    double saldoDepois = contas[0].consultarSaldo();
    assert(saldoDepois > saldoAntes);
}

void testSaque() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    double saldoAntes = contas[0].consultarSaldo();
    banco.sacar();
    double saldoDepois = contas[0].consultarSaldo();
    assert(saldoDepois < saldoAntes);
}

void testTransferencia() {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int contaOrigem = contas[0].getNumeroConta();
    int contaDestino = contas[1].getNumeroConta();
    double saldoOrigemAntes = contas[0].consultarSaldo();
    double saldoDestinoAntes = contas[1].consultarSaldo();
    banco.transferir();
    double saldoOrigemDepois = contas[0].consultarSaldo();
    double saldoDestinoDepois = contas[1].consultarSaldo();
    assert(saldoOrigemDepois < saldoOrigemAntes);
    assert(saldoDestinoDepois > saldoDestinoAntes);
}

void testEncerrarConta() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    banco.encerrarConta();
    const std::vector<Conta>& contasDepois = banco.getContas();
    assert(contasDepois.empty());
}

void testExtratoConta() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    banco.verExtratoConta();
    // Não há muito o que testar aqui além de garantir que a função não quebre
}

void testInformacoesConta() {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    banco.verInformacoesConta();
    // Não há muito o que testar aqui além de garantir que a função não quebre
}