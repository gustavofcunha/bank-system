#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"

TEST(ContaTest, Depositar) {
    Conta conta(1, "Titular", "senha");
    conta.depositar(100.0, true);
    EXPECT_EQ(conta.consultarSaldo(), 100.0);
}

TEST(ContaTest, SacarComSaldoSuficiente) {
    Conta conta(1, "Titular", "senha");
    conta.depositar(100.0, true);
    EXPECT_TRUE(conta.sacar(50.0, true));
    EXPECT_EQ(conta.consultarSaldo(), 50.0);
}

TEST(ContaTest, SacarComSaldoInsuficiente) {
    Conta conta(1, "Titular", "senha");
    EXPECT_FALSE(conta.sacar(50.0, true));
    EXPECT_EQ(conta.consultarSaldo(), 0.0);
}

// Testes para a classe Banco
TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();
    EXPECT_EQ(banco.getContas().size(), 1);
}

TEST(BancoTest, TransferirComSaldoSuficiente) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    auto& contas = banco.getContas();
    contas[0].depositar(100.0, true);
    banco.transferir();
    EXPECT_EQ(contas[0].consultarSaldo(), 0.0);
    EXPECT_EQ(contas[1].consultarSaldo(), 100.0);
}

TEST(BancoTest, TransferirComSaldoInsuficiente) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    auto& contas = banco.getContas();
    banco.transferir(); // tenta transferir sem saldo suficiente
    EXPECT_EQ(contas[0].consultarSaldo(), 0.0);
    EXPECT_EQ(contas[1].consultarSaldo(), 0.0);
}

TEST(BancoTest, EncerrarContaExistente) {
    Banco banco;
    banco.abrirConta();
    auto& contas = banco.getContas();
    banco.encerrarConta(); // encerra a conta existente
    EXPECT_EQ(contas.size(), 0);
}

TEST(BancoTest, EncerrarContaInexistente) {
    Banco banco;
    banco.abrirConta();
    auto& contas = banco.getContas();
    banco.encerrarConta(); // tenta encerrar uma conta inexistente
    EXPECT_EQ(contas.size(), 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
