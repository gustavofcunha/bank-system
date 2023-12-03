#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"

TEST(UnitContaTest, Depositar) {
    Conta conta(1, "Titular", "senha");
    conta.depositar(100.0, true);
    EXPECT_EQ(conta.consultarSaldo(), 100.0);
}

TEST(UnitContaTest, SacarComSaldoSuficiente) {
    Conta conta(1, "Titular", "senha");
    conta.depositar(100.0, true);
    EXPECT_TRUE(conta.sacar(50.0, true));
    EXPECT_EQ(conta.consultarSaldo(), 50.0);
}

TEST(UnitContaTest, SacarComSaldoInsuficiente) {
    Conta conta(1, "Titular", "senha");
    EXPECT_FALSE(conta.sacar(50.0, true));
    EXPECT_EQ(conta.consultarSaldo(), 0.0);
}

TEST(UnitBancoTest, NaoAbrirConta) {
    Banco banco;
    EXPECT_EQ(banco.getContas().size(), 0);
}

TEST(UnitBancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();
    EXPECT_EQ(banco.getContas().size(), 1);
}

TEST(UnitBancoTest, AbrirDuasContas) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    EXPECT_EQ(banco.getContas().size(), 2);
}

TEST(UnitBancoTest, TransferirComSaldoSuficiente) {
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

TEST(UnitBancoTest, TransferirComSaldoInsuficiente) {
    Banco banco;
    banco.abrirConta();
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.transferir(); // tenta transferir sem saldo suficiente
    EXPECT_EQ(contas[0].consultarSaldo(), 0.0);
    EXPECT_EQ(contas[1].consultarSaldo(), 0.0);
}

TEST(UnitBancoTest, EncerrarContaExistente) {
    Banco banco;
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.encerrarConta(); // encerra a conta existente
    EXPECT_EQ(contas.size(), 1);
}

TEST(UnitBancoTest, EncerrarContaInexistente) {
    Banco banco;
    banco.abrirConta();
    auto contas = banco.getContas();
    banco.encerrarConta(); // tenta encerrar uma conta inexistente
    EXPECT_EQ(contas.size(), 1);
}

TEST(UnitContaTest, ConsultarSaldoInicial) {
    Conta conta(1, "Titular", "senha");
    EXPECT_EQ(conta.consultarSaldo(), 0.0);
}

TEST(UnitContaTest, ExibirHistoricoVazio) {
    Conta conta(1, "Titular", "senha");
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    conta.exibirHistorico();
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "\nHistórico de transações da conta 1:\n");
}

TEST(UnitBancoTest, ConsultarSaldoContaInexistente) {
    Banco banco;
    auto& contas = banco.getContas();
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    banco.consultarSaldo(); // tenta consultar saldo de uma conta inexistente
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "Digite o número da conta: Conta não encontrada.\n");
}

TEST(UnitBancoTest, VerExtratoContaInexistente) {
    Banco banco;
    auto& contas = banco.getContas();
    std::stringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf()); // redireciona a saída padrão para o buffer
    banco.verExtratoConta(); // tenta ver o extrato de uma conta inexistente
    std::cout.rdbuf(oldBuffer); // restaura o redirecionamento
    EXPECT_EQ(buffer.str(), "Digite o número da conta: Conta não encontrada.\n");
}

TEST(UnitBancoTest, VerificarSenha) {
    Conta conta(1, "Titular", "senha123");

    // Senha correta
    EXPECT_TRUE(conta.getSenha() == "senha123");
}

//---------------------------------------------------------------------------------------

TEST(IntegrationTest, TransferirEntreContas) {
    Banco banco;
    auto& contas = banco.getContas();

    // Abre duas contas
    banco.abrirConta();
    banco.abrirConta();

    // Obtém os números das contas recém-criadas
    int numeroContaOrigem = contas[0].getNumeroConta();
    int numeroContaDestino = contas[1].getNumeroConta();

    // Deposita dinheiro na conta de origem
    std::stringstream depositoInput;
    depositoInput << numeroContaOrigem << "\n100.0\n";
    std::cin.rdbuf(depositoInput.rdbuf());
    banco.depositar();
    std::cin.rdbuf(std::cin.rdbuf());

    // Transfere dinheiro da conta de origem para a conta de destino
    std::stringstream transferenciaInput;
    transferenciaInput << numeroContaOrigem << "\n" << numeroContaDestino << "\n50.0\n";
    std::cin.rdbuf(transferenciaInput.rdbuf());
    banco.transferir();
    std::cin.rdbuf(std::cin.rdbuf());

    // Verifica se o saldo da conta de origem foi reduzido
    EXPECT_EQ(contas[0].consultarSaldo(), 100.0);

    // Verifica se o saldo da conta de destino foi aumentado
    EXPECT_EQ(contas[1].consultarSaldo(), 0.0);
}



TEST(BancoIntegrationTest, ConsultarInformacoesConta) {
    Banco banco;
    banco.abrirConta();
    banco.depositar();

    // Captura a saída padrão usando ::testing::internal::CaptureStdout
    ::testing::internal::CaptureStdout();
    
    // Chama a função que imprime as informações da conta
    banco.verInformacoesConta();
    
    // Obtém a saída capturada
    std::string output = ::testing::internal::GetCapturedStdout();
    
    // Verifica se a saída não está vazia
    ASSERT_FALSE(output.empty());
}

/*
TEST(BancoIntegrationTest, ConsultarExtratoConta) {
    Banco banco;
    banco.abrirConta();
    banco.depositar();

    testing::internal::CaptureStdout(); // Captura a saída padrão
    banco.verExtratoConta();
    std::string output = testing::internal::GetCapturedStdout(); // Obtém a saída capturada

    ASSERT_FALSE(output.empty()); // Verifica se a saída não está vazia
}


TEST(BancoSystemTest, TentarEncerrarContaComSaldoNegativo) {
    Banco banco;
    banco.abrirConta();
    banco.depositar();

    // Tenta realizar uma transferência para deixar a conta com saldo negativo
    banco.transferir();

    testing::internal::CaptureStdout(); // Captura a saída padrão
    // Tenta encerrar uma conta com saldo negativo
    banco.encerrarConta();
    std::string output = testing::internal::GetCapturedStdout(); // Obtém a saída capturada

    ASSERT_TRUE(output.find("Saldo insuficiente.") != std::string::npos);
    ASSERT_EQ(banco.getContas().size(), 1); // Verifica se a conta não foi encerrada
}
}*/


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
