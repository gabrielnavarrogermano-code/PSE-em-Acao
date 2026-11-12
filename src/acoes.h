/*
 * acoes.h - Estrutura de dados das acoes do PSE e funcoes de cadastro,
 * listagem, pesquisa e atualizacao de situacao.
 */
#ifndef ACOES_H
#define ACOES_H

#define MAX_ACOES 100
#define MAX_TEMAS 8

#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

/* Cada acao guarda apenas informacoes coletivas: nenhum dado de estudante. */
typedef struct {
    int  codigo;            /* identificador unico da acao */
    char escola[60];        /* nome ficticio da escola */
    char tema[40];          /* tematica do PSE - ex.: Vacinacao */
    char dataPrevista[11];  /* formato dd/mm/aaaa */
    char publicoAlvo[40];   /* ex.: 6o ao 9o ano - fundamental */
    char responsavel[50];   /* funcao/equipe responsavel */
    int  previstos;         /* participantes previstos */
    int  efetivos;          /* participantes efetivos */
    int  situacao;          /* 1-planejada 2-realizada 3-cancelada */
} Acao;

/* Opcoes do menu */
void cadastrarAcao(Acao acoes[], int *totalAcoes);
void listarAcoes(Acao acoes[], int totalAcoes);
void pesquisarAcoes(Acao acoes[], int totalAcoes);
void atualizarSituacao(Acao acoes[], int totalAcoes);

/* Funcoes de apoio usadas tambem por main.c e relatorio.c */
int  lerInteiro(const char *mensagem);
void lerTexto(const char *mensagem, char destino[], int tamanho);
int  buscarPorCodigo(Acao acoes[], int totalAcoes, int codigo);
int  contemTexto(const char texto[], const char trecho[]);
const char *nomeSituacao(int situacao);

#endif
