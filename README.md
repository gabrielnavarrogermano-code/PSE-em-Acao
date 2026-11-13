# PSE em Ação

**Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola**

AEP do 2º semestre de Engenharia de Software – UniCesumar (2026) · Turma ESOFT2SNB

| Integrante | RA |
|---|---|
| Gabriel Navarro Germano | 26005537-2 |
| Heitor Kaminagakura Corradi | 26010122-2 |
| Luidy Rolphe Bianchini | 26005360-2 |

## Sobre o projeto

Aplicação em **linguagem C**, executada em terminal, que ajuda a equipe do
**Programa Saúde na Escola (PSE)** a planejar, registrar e acompanhar ações coletivas nas
escolas de um município.

- **Temática de demonstração:** verificação da situação vacinal. O sistema aceita, porém,
  qualquer temática do PSE (alimentação saudável, saúde bucal, cultura de paz...).
- **Privacidade:** o programa guarda apenas informações coletivas sobre as ações e deve ser
  usado com dados fictícios. Não registra nomes nem dados de saúde de estudantes.

### Funcionalidades

| Opção | Funcionalidade |
|---|---|
| 1 | Cadastrar ação (código, escola, tema, data prevista, público-alvo, responsável, participantes previstos e situação inicial) |
| 2 | Listar ações |
| 3 | Pesquisar por código, escola ou tema |
| 4 | Atualizar situação (planejada, realizada ou cancelada) e registrar participantes efetivos |
| 5 | Gerar resumo: ações por situação, percentual de participação, ações por temática e participação por escola |
| 0 | Encerrar |

O programa valida as entradas: código repetido, campo vazio, quantidade negativa ou zero,
data inválida, opção inexistente, registro inexistente e limite de 100 ações.

## Como compilar e executar

### Pelo Dev-C++

1. Menu **Arquivo → Novo → Projeto**, escolha **Console Application**, marque **Projeto C**,
   dê um nome ao projeto e salve.
2. Remova do projeto o `main.c` de exemplo criado pelo Dev-C++ (botão direito no arquivo →
   **Remover arquivo**).
3. Clique com o botão direito no projeto → **Adicionar ao projeto** e selecione os cinco
   arquivos da pasta `src`: `main.c`, `acoes.c`, `acoes.h`, `relatorio.c` e `relatorio.h`.
4. Pressione **F11** (Compilar e Executar).

> Não abra apenas o `main.c` para compilar: as funções ficam em `acoes.c` e `relatorio.c`,
> e o Dev-C++ mostraria erros como `undefined reference to 'cadastrarAcao'`.

### Pelo terminal (GCC)

Na pasta raiz do repositório:

```
gcc -o pse-em-acao src/main.c src/acoes.c src/relatorio.c
```

Depois execute `pse-em-acao.exe` (Windows) ou `./pse-em-acao` (Linux).

O código foi testado no Dev-C++ 5.11 (TDM-GCC 4.9.2) e no GCC 16, compilando sem avisos nos
padrões C89 e C99.

## Estrutura do repositório

```
PSE-em-Acao/
|-- README.md              -> descricao, integrantes, compilacao e execucao
|-- documentacao/
|   |-- entrega-1/         -> documento da 1a entrega
|   |-- entrega-2/         -> documento final (PDF)
|-- src/
|   |-- main.c             -> menu principal e chamadas das funcoes
|   |-- acoes.h            -> struct Acao, constantes e prototipos das funcoes
|   |-- acoes.c            -> cadastro, listagem, pesquisa, atualizacao
|   |-- relatorio.h        -> prototipo da funcao de resumo
|   |-- relatorio.c        -> resumo geral, por tematica e por escola
```

## Documentação

- **1ª entrega:** [documento escrito](documentacao/entrega-1/entrega-1.pdf)
- **2ª entrega:** [documento final](documentacao/entrega-2/entrega-2.pdf), com requisitos
  atualizados, casos de uso, fluxogramas, testes, manual do usuário (com capturas de tela) e
  considerações finais
- **Vídeo de apresentação:** *link a ser adicionado após a publicação*
