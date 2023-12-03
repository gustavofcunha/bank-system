#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"


TEST(BancoTest, MaiorNumeroConta) {
    // Crie um objeto Banco e adicione algumas contas
    Banco banco;
    banco.abrirConta(); // Adicione uma conta
    banco.abrirConta(); // Adicione outra conta

    // O maior número de conta deve ser 2, pois iniciamos de 1
    EXPECT_EQ(banco.maiorNumeroConta(), 2);
}


TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();

    // Verifica se a conta foi adicionada ao vetor de contas
    EXPECT_EQ(banco.getContas().size(), 1);
}

TEST(BancoTest, Depositar) {
    Banco banco;
    banco.abrirConta();
    
    // Obtém a conta recém-criada
    Conta& conta = banco.getContas().front();
    
    // Deposita um valor na conta
    double valorDeposito = 100.0;
    conta.depositar(valorDeposito, true);

    // Verifica se o saldo da conta é igual ao valor depositado
    EXPECT_EQ(conta.consultarSaldo(), valorDeposito);
}

TEST(BancoTest, Sacar) {
    Banco banco;
    banco.abrirConta();
    
    // Obtém a conta recém-criada
    Conta& conta = banco.getContas().front();
    
    // Deposita um valor inicial
    double valorInicial = 200.0;
    conta.depositar(valorInicial, true);

    // Tenta sacar um valor menor que o saldo
    double valorSaque = 100.0;
    EXPECT_TRUE(conta.sacar(valorSaque, true));

    // Verifica se o saldo foi reduzido corretamente
    EXPECT_EQ(conta.consultarSaldo(), valorInicial - valorSaque);

    // Tenta sacar um valor maior que o saldo
    double valorSaqueMaiorQueSaldo = 500.0;
    EXPECT_FALSE(conta.sacar(valorSaqueMaiorQueSaldo, true));

    // O saldo não deve ter sido alterado neste caso
    EXPECT_EQ(conta.consultarSaldo(), valorInicial - valorSaque);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
