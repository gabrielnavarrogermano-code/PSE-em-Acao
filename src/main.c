/*
 * PSE em Acao - Sistema de Planejamento e Acompanhamento de Acoes de Saude
 * na Escola.
 *
 * main.c - Menu principal e chamada das funcoes de cada opcao.
 *
 * Compilacao: gcc -o pse-em-acao src/main.c src/acoes.c src/relatorio.c
 * Execucao:   ./pse-em-acao   (Linux)   ou   pse-em-acao.exe   (Windows)
 */
#include <stdio.h>
#include "acoes.h"
#include "relatorio.h"

void exibirMenu(void)
{
    printf("\n==============================================\n");
    printf("   PSE EM ACAO - Acoes de Saude na Escola\n");
    printf("==============================================\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acao\n");
    printf("4 - Atualizar situacao\n");
    printf("5 - Gerar resumo\n");
    printf("0 - Encerrar\n");
}

int main(void)
{
    Acao acoes[MAX_ACOES];
    int totalAcoes = 0;
    int opcao;

    printf("PSE em Acao - use somente dados ficticios e informacoes coletivas.\n");
    printf("O sistema nao registra nomes nem dados de saude de estudantes.\n");

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
        case 1:
            cadastrarAcao(acoes, &totalAcoes);
            break;
        case 2:
            listarAcoes(acoes, totalAcoes);
            break;
        case 3:
            pesquisarAcoes(acoes, totalAcoes);
            break;
        case 4:
            atualizarSituacao(acoes, totalAcoes);
            break;
        case 5:
            gerarResumo(acoes, totalAcoes);
            break;
        case 0:
            printf("\nPrograma encerrado. Obrigado por utilizar o PSE em Acao!\n");
            break;
        default:
            printf("Opcao invalida. Digite um numero de 0 a 5.\n");
        }
    } while (opcao != 0);

    return 0;
}
