#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"

TEST(BancoTest, MaiorNumeroConta) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();

    const Banco& constBanco = banco;  // Create a const reference
    EXPECT_EQ(constBanco.maiorNumeroConta(), 2);
}

TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();

    const Banco& constBanco = banco;  // Create a const reference
    EXPECT_EQ(constBanco.getContas().size(), 1);
}

TEST(BancoTest, Depositar) {
    Banco banco;
    banco.abrirConta();
    
    const Banco& constBanco = banco;  // Create a const reference
    const Conta& conta = constBanco.getContas().front();

    double valorDeposito = 100.0;
    conta.depositar(valorDeposito, true);
    EXPECT_EQ(conta.consultarSaldo(), valorDeposito);
}

TEST(BancoTest, Sacar) {
    Banco banco;
    banco.abrirConta();
    
    const Banco& constBanco = banco;  // Create a const reference
    const Conta& conta = constBanco.getContas().front();
    
    double valorInicial = 200.0;
    conta.depositar(valorInicial, true);

    double valorSaque = 100.0;
    EXPECT_TRUE(conta.sacar(valorSaque, true));
    EXPECT_EQ(conta.consultarSaldo(), valorInicial - valorSaque);

    double valorSaqueMaiorQueSaldo = 500.0;
    EXPECT_FALSE(conta.sacar(valorSaqueMaiorQueSaldo, true));
    EXPECT_EQ(conta.consultarSaldo(), valorInicial - valorSaque);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
