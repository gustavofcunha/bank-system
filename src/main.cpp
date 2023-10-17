#include <iostream>
#include "banco.h"
#include "gerenciador_memoria.h"

void imprimeCabecalhoSistema(){
    std::cout << std::endl;
    std::cout << "=======================BANCO BEAGÁ DE MINAS GERAIS=======================" << std::endl;
    std::cout << "                         Olá, seja bem vindo(a)!                       " << std::endl;
}

void imprimeOpcoesSistema(){
        std::cout << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "Escolha um dos serviços disponíveis para você neste canal de atendimento:" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Abrir conta" << std::endl;
        std::cout << "2. Depositar" << std::endl;
        std::cout << "3. Sacar" << std::endl;
        std::cout << "4. Consultar saldo" << std::endl;
        std::cout << "5. Transferir" << std::endl;
        std::cout << "6. Encerrar conta" << std::endl;
        std::cout << "7. Consultar extrato" << std::endl;
        std::cout << "8. Consultar informações da conta" << std::endl;
        std::cout << "9. Sair" << std::endl << std::endl;
        std::cout << "Digite uma opção: ";
}

int main() {
    GerenciadorMemoria gerenciadorMemoria;
    std::vector<Conta> contas = gerenciadorMemoria.carregarDadosContas(); 
    gerenciadorMemoria.carregarDadosTransacoes(contas);

    Banco banco(contas);
    int escolha;

    imprimeCabecalhoSistema();
    
    do {
        imprimeOpcoesSistema();
        std::cin >> escolha;

        switch (escolha) {
            case 1:
                banco.abrirConta();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 2:
                banco.depositar();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 3:
                banco.sacar();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 4:
                banco.consultarSaldo();
                break;
            case 5:
                banco.transferir();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 6:
                banco.encerrarConta();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 7:
                banco.verExtratoConta();
                gerenciadorMemoria.salvarDadosContas(banco.getContas());
                break;
            case 8:
                banco.verInformacoesConta();
                break;
            case 9:
                std::cout << "Saindo do sistema..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
        

    } while (escolha != 9);

    return 0;
}
