#ifndef abinaria_h
#define abinaria_h

#include "item.h"

#define SEM_FILHO -1

typedef struct No{

    /* 
     * Estrutura do Nó da Arvore.
     * Contém um item
     * Contém inteiros para representar quantos bytes devem ser deslocados para chegar aos filhos
     */
    
    TItem item;   //Conteúdo do Nó
    
    long pEsq;    //Nó filho da esquerda
    long pDir;    //Nó filho da direita
    
}TNo;

/*  Cria o arquivo binário que contém os nós da árvore.
 *  Recebe o nome do arquivo binário de entrada e do arquivo binário de saída e ponteiros para estatisticas
 */
void criarArvoreBinaria(const char* nome_arq_entrada, const char* nome_arq_saida, long long int* comparacoes, long long int* transferencias, double* tempo);

/* Pesquisa pelo item no arquivo através de sua chave
 * Recebe a chave a ser pesquisada e o nome do arquivo binário que contém a árvore
 * Retorna um ponteiro para o registro encontrado, ou NULL caso a busca falhe
 */
TItem* pesquisarArvoreBinaria(int chave, const char* nome_arquivo, long long int* comparacoes, long long int* transferencias, double* tempo);

#endif
