#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"

TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    ASSERT_FALSE(contas.empty());
}

TEST(BancoTest, Depositar) {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    int numeroConta = contas[0].getNumeroConta();
    double saldoAntes = contas[0].consultarSaldo();
    banco.depositar();
    double saldoDepois = contas[0].consultarSaldo();
    ASSERT_GT(saldoDepois, saldoAntes);
}

// Adicione mais TESTs conforme necessário...

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
