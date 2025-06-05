# Índice Invertido com Árvores - Estrutura de Dados (FGV)

Este repositório contém o desenvolvimento do **Trabalho A2** da disciplina de **Estrutura de Dados**, cujo objetivo é implementar e comparar a eficiência de três diferentes estruturas de dados na construção de um **índice invertido**: 

- **Árvore Binária de Busca (BST)**
- **Árvore AVL**
- **Árvore Rubro-Negra (RBT)**

## Objetivos do Projeto

- Construir um índice invertido associando palavras a documentos.
- Implementar do zero as três estruturas de dados mencionadas, utilizando **C++**.
- Avaliar o desempenho de cada estrutura nas operações de **inserção** e **busca**.
- Realizar uma **análise comparativa** com base em diferentes tamanhos de entrada.

## Estrutura do Repositório

```
A2_FGV_ED/
├── src/                # Código-fonte do projeto
│   ├── bst.cpp        # Implementação da BST
│   ├── avl.cpp        # Implementação da AVL
│   ├── rbt.cpp        # Implementação da RBT
│   ├── data.cpp       # Leitura de arquivos e pré-processamento
│   ├── tree_utils.cpp # Funções auxiliares e structs comuns
│   ├── main_bst.cpp   # Interface de linha de comando para BST
│   ├── main_avl.cpp   # Interface de linha de comando para AVL
│   ├── main_rbt.cpp   # Interface de linha de comando para RBT
│   ├── test_bst.cpp   # Arquivo de testes da BST
├── data/              # Base de dados de documentos (.txt)
├── docs/              # Relatório, gráficos e análises
├── Makefile           # Script para compilação automatizada
└── README.md          # Este arquivo
```

## Como Compilar

Certifique-se de ter o **g++** e **C++ 17** instalado.

```bash
make
```

Isso irá compilar os seguintes executáveis:

- `bst_main`
- `avl_main`
- `rbt_main`
- `test_bst`

## Como Executar

O programa deve ser executado via linha de comando com a seguinte estrutura:

```bash
./<arvore> <comando> <n_docs> <diretorio>
```

**Parâmetros:**

- `<arvore>`: `bst_main`, `avl_main` ou `rbt_main`
- `<comando>`: `search` ou `stats`
- `<n_docs>`: número de documentos a serem indexados
- `<diretorio>`: caminho para a pasta com arquivos `.txt`

**Exemplo:**

```bash
./bst_main search 100 ./data
./avl_main stats 500 ./data
```

## Análise Comparativa

A execução do programa gera estatísticas de desempenho como:

- Tempo de inserção e busca
- Número de comparações realizadas
- Altura das árvores
- Distribuição dos nós

## Integrantes

- Bryan Monteiro
- Sofia Monteiro
- Nicholas Costa
- Vinicio Deusdará
- Lucas Sodré

