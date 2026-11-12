/*
 * relatorio.c - Resumo geral (RF06), por tematica (RF10) e por escola (RF11).
 */
#include <stdio.h>
#include <string.h>
#include "relatorio.h"

/* Conta quantas acoes existem em cada tematica cadastrada. */
static void resumirPorTema(Acao acoes[], int totalAcoes)
{
    char temas[MAX_ACOES][40];
    int quantidade[MAX_ACOES];
    int totalTemas = 0;
    int i, j, achou;

    for (i = 0; i < totalAcoes; i++) {
        achou = 0;
        for (j = 0; j < totalTemas && !achou; j++) {
            /* mesmo texto, sem diferenciar maiusculas e minusculas */
            if (strlen(temas[j]) == strlen(acoes[i].tema) && contemTexto(temas[j], acoes[i].tema)) {
                quantidade[j]++;
                achou = 1;
            }
        }
        if (!achou) {
            strcpy(temas[totalTemas], acoes[i].tema);
            quantidade[totalTemas] = 1;
            totalTemas++;
        }
    }

    printf("\n--- Acoes por tematica ---\n");
    for (i = 0; i < totalTemas; i++) {
        printf("%-30s %d\n", temas[i], quantidade[i]);
    }
}

/* Conta as acoes de cada escola e soma os participantes das acoes realizadas. */
static void resumirPorEscola(Acao acoes[], int totalAcoes)
{
    char escolas[MAX_ACOES][60];
    int quantidade[MAX_ACOES], previstos[MAX_ACOES], efetivos[MAX_ACOES];
    int totalEscolas = 0;
    int i, j;

    for (i = 0; i < totalAcoes; i++) {
        j = 0;
        while (j < totalEscolas && !(strlen(escolas[j]) == strlen(acoes[i].escola) &&
                                     contemTexto(escolas[j], acoes[i].escola))) {
            j++;
        }
        if (j == totalEscolas) {
            strcpy(escolas[j], acoes[i].escola);
            quantidade[j] = 0;
            previstos[j] = 0;
            efetivos[j] = 0;
            totalEscolas++;
        }
        quantidade[j]++;
        if (acoes[i].situacao == REALIZADA) {
            previstos[j] += acoes[i].previstos;
            efetivos[j] += acoes[i].efetivos;
        }
    }

    printf("\n--- Participacao por escola ---\n");
    printf("(previstos e efetivos somam apenas as acoes realizadas)\n");
    printf("%-30s %5s %9s %9s\n", "ESCOLA", "ACOES", "PREVISTOS", "EFETIVOS");
    for (i = 0; i < totalEscolas; i++) {
        printf("%-30.30s %5d %9d %9d\n", escolas[i], quantidade[i], previstos[i], efetivos[i]);
    }
}

/* Opcao 5 - Gerar resumo */
void gerarResumo(Acao acoes[], int totalAcoes)
{
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int previstos = 0, efetivos = 0;
    int i;

    printf("\n========== RESUMO GERAL ==========\n");
    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada. Cadastre acoes para gerar o resumo.\n");
        return;
    }

    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].situacao == PLANEJADA) {
            planejadas++;
        } else if (acoes[i].situacao == REALIZADA) {
            realizadas++;
            previstos += acoes[i].previstos;
            efetivos += acoes[i].efetivos;
        } else {
            canceladas++;
        }
    }

    printf("Acoes cadastradas ............: %d\n", totalAcoes);
    printf("  Planejadas .................: %d\n", planejadas);
    printf("  Realizadas .................: %d\n", realizadas);
    printf("  Canceladas .................: %d\n", canceladas);
    printf("\nParticipantes previstos (acoes realizadas): %d\n", previstos);
    printf("Participantes efetivos (acoes realizadas) : %d\n", efetivos);

    if (previstos == 0) {
        printf("Percentual de participacao: nao calculado (nenhuma acao realizada).\n");
    } else {
        printf("Percentual de participacao: %.1f%%\n", efetivos * 100.0 / previstos);
    }

    resumirPorTema(acoes, totalAcoes);
    resumirPorEscola(acoes, totalAcoes);
}
