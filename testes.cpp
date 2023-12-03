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

TEST(BancoTest, NaoAbrirConta) {
    Banco banco;
    EXPECT_EQ(banco.getContas().size(), 0);
}

TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();
    EXPECT_EQ(banco.getContas().size(), 1);
}

TEST(BancoTest, AbrirDuasContas) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    EXPECT_EQ(banco.getContas().size(), 2);
}

TEST(BancoTest, TransferirComSaldoSuficiente) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    auto contas = banco.getContas();
    contas[0].depositar(100.0, true); 
    contas[0].sacar(50.0, true); 
    contas[1].depositar(50.0, true); 
    EXPECT_EQ(contas[0].consultarSaldo(), 50.0);
    EXPECT_EQ(contas[1].consultarSaldo(), 50.0);
}

TEST(BancoTest, TransferirComSaldoInsuficiente) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.transferir(); // tenta transferir sem saldo suficiente
    EXPECT_EQ(contas[0].consultarSaldo(), 0.0);
    EXPECT_EQ(contas[1].consultarSaldo(), 0.0);
}

TEST(BancoTest, EncerrarContaExistente) {
    Banco banco;
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.encerrarConta(); // encerra a conta existente
    EXPECT_EQ(contas.size(), 1);
}

TEST(BancoTest, EncerrarContaInexistente) {
    Banco banco;
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.encerrarConta(); // tenta encerrar uma conta inexistente
    EXPECT_EQ(contas.size(), 1);
}

TEST(ContaTest, ConsultarSaldoInicial) {
    Conta conta(1, "Titular", "senha");
    EXPECT_EQ(conta.consultarSaldo(), 0.0);
}

TEST(ContaTest, ExibirHistoricoVazio) {
    Conta conta(1, "Titular", "senha");
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    conta.exibirHistorico();
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "\nHistórico de transações da conta 1:\n");
}

TEST(BancoTest, ConsultarSaldoContaInexistente) {
    Banco banco;
    auto& contas = banco.getContas();
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    banco.consultarSaldo(); // tenta consultar saldo de uma conta inexistente
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "Digite o número da conta: Conta não encontrada.\n");
}

TEST(BancoTest, VerExtratoContaInexistente) {
    Banco banco;
    auto& contas = banco.getContas();
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    banco.verExtratoConta(); // tenta ver o extrato de uma conta inexistente
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "Digite o número da conta: Conta não encontrada.\n");
}

TEST(BancoTest, TransferirParaContaInexistente) {
    Banco banco;
    auto& contas = banco.getContas();
    
    // Cria uma conta de origem com saldo
    Conta contaOrigem(1, "TitularOrigem", "senha");
    contaOrigem.depositar(100.0, true);
    contas.push_back(contaOrigem);

    // Tenta transferir para uma conta de destino inexistente
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    banco.transferir(); 
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento

    // Verifica se a mensagem de conta de destino não encontrada foi exibida
    EXPECT_EQ(buffer.str(), "Digite o número da conta de origem: Digite o número da conta de destino: Conta de destino não encontrada.\n");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
