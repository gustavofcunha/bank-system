#include <gtest/gtest.h>
#include "include/banco.h"
#include "include/conta.h"

TEST(BancoTest, AbrirConta) {
    Banco banco;
    banco.abrirConta();
    const std::vector<Conta>& contas = banco.getContas();
    ASSERT_FALSE(contas.empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
