/*
 * acoes.c - Leitura das entradas, cadastro, listagem, pesquisa e
 * atualizacao de situacao das acoes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "acoes.h"

/* Lista apenas de apoio: o campo tema tambem aceita texto livre. */
const char *temasPSE[MAX_TEMAS] = {
    "Vacinacao",
    "Alimentacao saudavel",
    "Atividade fisica",
    "Saude bucal",
    "Saude mental",
    "Cultura de paz",
    "Prevencao das violencias",
    "Saude ambiental"
};

/* ================= Leitura e validacao das entradas ================= */

/* Le uma linha do teclado e retira o ENTER do final. */
static void lerLinha(const char *mensagem, char linha[], int tamanho)
{
    int tamanhoLido;

    printf("%s", mensagem);
    if (fgets(linha, tamanho, stdin) == NULL) {
        printf("\nFim da entrada. Programa encerrado.\n");
        exit(0);
    }

    tamanhoLido = strlen(linha);
    if (tamanhoLido > 0 && linha[tamanhoLido - 1] == '\n') {
        linha[tamanhoLido - 1] = '\0';
        tamanhoLido--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* descarta o que passou do tamanho da linha */
        }
    }
    if (tamanhoLido > 0 && linha[tamanhoLido - 1] == '\r') {
        linha[tamanhoLido - 1] = '\0';
    }
}

/* Converte o texto em numero. Retorna -1 se nao for um inteiro positivo. */
static int converterNumero(const char texto[])
{
    int i;

    if (texto[0] == '\0' || strlen(texto) > 6) {
        return -1;
    }
    for (i = 0; texto[i] != '\0'; i++) {
        if (!isdigit((unsigned char) texto[i])) {
            return -1;
        }
    }
    return atoi(texto);
}

/* Le um numero inteiro. Retorna -1 se o valor digitado for invalido. */
int lerInteiro(const char *mensagem)
{
    char linha[100];

    lerLinha(mensagem, linha, sizeof(linha));
    return converterNumero(linha);
}

/* Le um campo de texto obrigatorio, repetindo ate que seja valido. */
void lerTexto(const char *mensagem, char destino[], int tamanho)
{
    char linha[200];
    int inicio;
    int valido = 0;

    while (!valido) {
        lerLinha(mensagem, linha, sizeof(linha));
        inicio = 0;
        while (linha[inicio] == ' ') {
            inicio++; /* ignora espacos no inicio */
        }
        if (linha[inicio] == '\0') {
            printf("Campo obrigatorio vazio. Preencha este campo.\n");
        } else if ((int) strlen(linha + inicio) >= tamanho) {
            printf("Texto muito longo. Use no maximo %d caracteres.\n", tamanho - 1);
        } else {
            strcpy(destino, linha + inicio);
            valido = 1;
        }
    }
}

/* Confere se a data esta no formato dd/mm/aaaa e se o dia existe no mes. */
static int dataValida(const char data[])
{
    int diasNoMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dia, mes, i;

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit((unsigned char) data[i])) {
            return 0;
        }
    }
    dia = atoi(data);
    mes = atoi(data + 3);
    return mes >= 1 && mes <= 12 && dia >= 1 && dia <= diasNoMes[mes - 1];
}

static void lerData(char data[])
{
    lerTexto("Data prevista (dd/mm/aaaa): ", data, 11);
    while (!dataValida(data)) {
        printf("Data invalida. Use o formato dd/mm/aaaa (ex.: 15/03/2026).\n");
        lerTexto("Data prevista (dd/mm/aaaa): ", data, 11);
    }
}

/* Aceita o numero de uma tematica da lista ou o nome digitado livremente. */
static void lerTema(char tema[])
{
    int numero;

    lerTexto("Tema: ", tema, 40);
    numero = converterNumero(tema);
    while (numero == 0 || numero > MAX_TEMAS) {
        printf("Numero fora da lista. Digite de 1 a %d ou escreva a tematica.\n", MAX_TEMAS);
        lerTexto("Tema: ", tema, 40);
        numero = converterNumero(tema);
    }
    if (numero != -1) {
        strcpy(tema, temasPSE[numero - 1]);
    }
}

/* Le a situacao (1, 2 ou 3), repetindo ate que a opcao exista. */
static int lerSituacao(const char *mensagem)
{
    int situacao;

    printf("1 - Planejada | 2 - Realizada | 3 - Cancelada\n");
    situacao = lerInteiro(mensagem);
    while (situacao < PLANEJADA || situacao > CANCELADA) {
        printf("Opcao invalida. Digite 1, 2 ou 3.\n");
        situacao = lerInteiro(mensagem);
    }
    return situacao;
}

/* Le a quantidade efetiva de participantes (zero ou mais). */
static int lerEfetivos(void)
{
    int efetivos = lerInteiro("Quantidade efetiva de participantes: ");

    while (efetivos < 0) {
        printf("Quantidade invalida. Informe um numero inteiro igual ou maior que zero.\n");
        efetivos = lerInteiro("Quantidade efetiva de participantes: ");
    }
    return efetivos;
}

/* ========================= Funcoes de apoio ========================= */

/* Busca sequencial pelo codigo. Retorna a posicao no vetor ou -1. */
int buscarPorCodigo(Acao acoes[], int totalAcoes, int codigo)
{
    int i;

    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Verifica se o texto contem o trecho, sem diferenciar maiusculas. */
int contemTexto(const char texto[], const char trecho[])
{
    char textoMinusculo[100], trechoMinusculo[100];
    int i;

    for (i = 0; texto[i] != '\0' && i < 99; i++) {
        textoMinusculo[i] = tolower((unsigned char) texto[i]);
    }
    textoMinusculo[i] = '\0';
    for (i = 0; trecho[i] != '\0' && i < 99; i++) {
        trechoMinusculo[i] = tolower((unsigned char) trecho[i]);
    }
    trechoMinusculo[i] = '\0';

    return strstr(textoMinusculo, trechoMinusculo) != NULL;
}

const char *nomeSituacao(int situacao)
{
    if (situacao == PLANEJADA) {
        return "Planejada";
    } else if (situacao == REALIZADA) {
        return "Realizada";
    }
    return "Cancelada";
}

static void imprimirCabecalho(void)
{
    printf("%-6s %-22s %-22s %-10s %-10s %5s %5s\n",
           "COD", "ESCOLA", "TEMA", "DATA", "SITUACAO", "PREV", "EFET");
    printf("------------------------------------------------------------------------------------\n");
}

/* Mostra uma acao em duas linhas: dados principais e detalhes. */
static void imprimirAcao(Acao acao)
{
    printf("%-6d %-22.22s %-22.22s %-10s %-10s %5d %5d\n",
           acao.codigo, acao.escola, acao.tema, acao.dataPrevista,
           nomeSituacao(acao.situacao), acao.previstos, acao.efetivos);
    printf("       Publico-alvo: %s | Responsavel: %s\n", acao.publicoAlvo, acao.responsavel);
}

/* ====================== Opcao 1 - Cadastrar acao ====================== */

void cadastrarAcao(Acao acoes[], int *totalAcoes)
{
    Acao nova;
    int i;

    printf("\n========== CADASTRAR ACAO ==========\n");
    if (*totalAcoes >= MAX_ACOES) {
        printf("Limite de armazenamento atingido (%d acoes). Cadastro nao realizado.\n", MAX_ACOES);
        return;
    }
    printf("Lembrete: registre apenas informacoes coletivas. Nao informe nomes\n");
    printf("ou dados de saude de estudantes.\n\n");

    nova.codigo = lerInteiro("Codigo da acao: ");
    while (nova.codigo <= 0 || buscarPorCodigo(acoes, *totalAcoes, nova.codigo) != -1) {
        if (nova.codigo <= 0) {
            printf("Codigo invalido. Digite um numero inteiro maior que zero.\n");
        } else {
            printf("Codigo ja existente. Informe outro codigo.\n");
        }
        nova.codigo = lerInteiro("Codigo da acao: ");
    }

    printf("\nTematicas sugeridas do PSE:\n");
    for (i = 0; i < MAX_TEMAS; i++) {
        printf("  %d - %s\n", i + 1, temasPSE[i]);
    }
    printf("No campo Tema, digite o numero da lista ou escreva outra tematica.\n\n");

    lerTexto("Escola: ", nova.escola, 60);
    lerTema(nova.tema);
    lerData(nova.dataPrevista);
    lerTexto("Publico-alvo: ", nova.publicoAlvo, 40);
    lerTexto("Responsavel (funcao ou equipe): ", nova.responsavel, 50);

    nova.previstos = lerInteiro("Quantidade prevista de participantes: ");
    while (nova.previstos <= 0) {
        printf("Quantidade invalida. Informe um numero inteiro maior que zero.\n");
        nova.previstos = lerInteiro("Quantidade prevista de participantes: ");
    }

    printf("\nSituacao inicial da acao:\n");
    nova.situacao = lerSituacao("Situacao inicial: ");
    nova.efetivos = 0;
    if (nova.situacao == REALIZADA) {
        nova.efetivos = lerEfetivos(); /* so a acao realizada guarda participantes */
    }

    acoes[*totalAcoes] = nova;
    (*totalAcoes)++;

    printf("\nAcao cadastrada com sucesso! Codigo %d com situacao inicial %s.\n",
           nova.codigo, nomeSituacao(nova.situacao));
}

/* ======================= Opcao 2 - Listar acoes ======================= */

void listarAcoes(Acao acoes[], int totalAcoes)
{
    int i;

    printf("\n========== LISTA DE ACOES ==========\n");
    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    imprimirCabecalho();
    for (i = 0; i < totalAcoes; i++) {
        imprimirAcao(acoes[i]);
    }
    printf("\nTotal: %d acao(oes) cadastrada(s).\n", totalAcoes);
}

/* ====================== Opcao 3 - Pesquisar acoes ===================== */

void pesquisarAcoes(Acao acoes[], int totalAcoes)
{
    int tipo, codigo, posicao, i;
    int encontradas = 0;
    char termo[60];

    printf("\n========== PESQUISAR ACOES ==========\n");
    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada para pesquisar.\n");
        return;
    }

    printf("1 - Pesquisar por codigo\n");
    printf("2 - Pesquisar por escola\n");
    printf("3 - Pesquisar por tema\n");
    tipo = lerInteiro("Tipo de pesquisa: ");

    if (tipo == 1) {
        codigo = lerInteiro("Codigo da acao: ");
        posicao = buscarPorCodigo(acoes, totalAcoes, codigo);
        if (posicao == -1) {
            printf("Acao nao encontrada.\n");
        } else {
            printf("\n");
            imprimirCabecalho();
            imprimirAcao(acoes[posicao]);
        }
    } else if (tipo == 2 || tipo == 3) {
        if (tipo == 2) {
            lerTexto("Nome da escola (ou parte dele): ", termo, 60);
        } else {
            lerTexto("Tema (ou parte dele): ", termo, 60);
        }
        for (i = 0; i < totalAcoes; i++) {
            if ((tipo == 2 && contemTexto(acoes[i].escola, termo)) ||
                (tipo == 3 && contemTexto(acoes[i].tema, termo))) {
                if (encontradas == 0) {
                    printf("\n");
                    imprimirCabecalho();
                }
                imprimirAcao(acoes[i]);
                encontradas++;
            }
        }
        if (encontradas == 0) {
            printf("Nenhuma acao encontrada para \"%s\".\n", termo);
        } else {
            printf("\n%d acao(oes) encontrada(s).\n", encontradas);
        }
    } else {
        printf("Opcao invalida. Digite 1, 2 ou 3.\n");
    }
}

/* =================== Opcao 4 - Atualizar situacao =================== */

void atualizarSituacao(Acao acoes[], int totalAcoes)
{
    int codigo, posicao, novaSituacao, efetivos;
    int situacaoAnterior;

    printf("\n========== ATUALIZAR SITUACAO ==========\n");
    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada para atualizar.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ");
    posicao = buscarPorCodigo(acoes, totalAcoes, codigo);
    if (posicao == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }

    printf("\n");
    imprimirCabecalho();
    imprimirAcao(acoes[posicao]);

    printf("\nNova situacao:\n");
    novaSituacao = lerSituacao("Opcao: ");

    efetivos = 0;
    if (novaSituacao == REALIZADA) {
        efetivos = lerEfetivos();
    }

    situacaoAnterior = acoes[posicao].situacao;
    acoes[posicao].situacao = novaSituacao;
    acoes[posicao].efetivos = efetivos; /* so a acao realizada guarda participantes */

    printf("\nSituacao atualizada com sucesso: %s -> %s.\n",
           nomeSituacao(situacaoAnterior), nomeSituacao(novaSituacao));
}
