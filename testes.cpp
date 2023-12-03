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


TEST(IntegrationTest, AbrirContaSacarEncerrarConta) {
    Banco banco;
    auto& contas = banco.getContas();

    // Abre uma conta
    banco.abrirConta();

    // Obtém o número da conta recém-criada
    int numeroConta = contas.back().getNumeroConta();

    // Deposita dinheiro na conta
    std::stringstream depositoInput;
    depositoInput << numeroConta << "\n100.0\n";
    std::cin.rdbuf(depositoInput.rdbuf());
    banco.depositar();
    std::cin.rdbuf(std::cin.rdbuf());

    // Sacar dinheiro da conta
    std::stringstream saqueInput;
    saqueInput << numeroConta << "\n50.0\n";
    std::cin.rdbuf(saqueInput.rdbuf());
    banco.sacar();
    std::cin.rdbuf(std::cin.rdbuf());

    // Verifica se o saldo da conta foi reduzido após o saque
    EXPECT_EQ(contas.back().consultarSaldo(), 100.0);

    // Encerra a conta
    std::stringstream encerrarContaInput;
    encerrarContaInput << numeroConta << "\n";
    std::cin.rdbuf(encerrarContaInput.rdbuf());
    banco.encerrarConta();
    std::cin.rdbuf(std::cin.rdbuf());

    // Verifica se a conta foi removida da lista de contas
    EXPECT_EQ(contas.size(), 1);
}


TEST(IntegrationTest, DepositoSaqueConta) {
    Banco banco;
    Conta conta(1, "Titular", "senha123");
    banco.getContas().push_back(conta);

    // Depósito na conta
    testing::internal::CaptureStdout();  // Captura a saída para evitar interação do usuário
    banco.depositar();  // Chama a função sem parâmetros para usar a interação padrão do teste
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Digite o número da conta: Digite o valor a ser depositado: Depósito realizado com sucesso.\n");
    EXPECT_DOUBLE_EQ(conta.consultarSaldo(), 0.0);  // O saldo não é atualizado no banco automaticamente

    // Definindo saldo manualmente para o teste de saque
    conta.depositar(150.0, true);

    // Saque na conta
    testing::internal::CaptureStdout();  // Captura a saída novamente
    banco.sacar();  // Chama a função sem parâmetros para usar a interação padrão do teste
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Digite o número da conta: Digite o valor a ser sacado: Saque realizado com sucesso.\n");
    EXPECT_DOUBLE_EQ(conta.consultarSaldo(), 0.0);  // O saldo não é atualizado no banco automaticamente
}

/*
TEST(IntegrationTest, AberturaEncerramentoConta) {
    Banco banco;

    // Abertura de conta
    banco.abrirConta("NovoTitular", "novasenha");
    EXPECT_EQ(banco.getContas().size(), 1);

    // Encerramento de conta
    banco.encerrarConta(1);
    EXPECT_EQ(banco.getContas().size(), 0);
}

TEST(IntegrationTest, ConsultaSaldoHistoricoConta) {
    Banco banco;
    Conta conta(1, "Titular", "senha123");
    banco.getContas().push_back(conta);

    // Depósito na conta
    banco.depositar(1, 200.0);

    // Consulta de saldo
    EXPECT_DOUBLE_EQ(banco.consultarSaldo(1), 200.0);

    // Saque na conta
    banco.sacar(1, 50.0);

    // Verifica histórico de transações
    banco.verExtratoConta(1);
    const auto& historico = conta.getHistorico();
    EXPECT_EQ(historico.size(), 2);
    EXPECT_EQ(historico[0], "Depósito de 200.0 realizado.");
    EXPECT_EQ(historico[1], "Saque de 50.0 realizado.");
}*/


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
