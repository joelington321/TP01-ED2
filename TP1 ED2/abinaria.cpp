#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "abinaria.h"

using namespace std;

/* Funções de busca */

//função recursiva auxiliar da função pesquisarArvoreBinaria(...)
void buscarRecursivo(long localraiz, int chave, TItem** resposta, FILE* arq, long long int* comparacoes, long long int* transferencias){

    TNo aux;
    fseek(arq, localraiz, SEEK_SET);
    
    (*transferencias)++;
    if(fread(&aux, sizeof(TNo), 1, arq) == 1){
        (*comparacoes)++;
        if(aux.item.chave == chave){
            *resposta = new TItem;
            **resposta = aux.item; //achou
        }else{
            (*comparacoes)++;
            if(aux.item.chave > chave){ //o item está à esquerda
                
                if(aux.pEsq == SEM_FILHO){ //não tem filho à esquerda
                  
                    *resposta = NULL;
                    
                }else{ //tem filho à esquerda
                    
                    //busca na subárvore da esquerda
                    buscarRecursivo(aux.pEsq, chave, resposta, arq, comparacoes, transferencias);
                }
            }else{ //o item está à direita
                
                if(aux.pDir == SEM_FILHO){ //não tem filho à direita
                
                    *resposta = NULL;
                    
                }else{ //tem filho à direita
                    
                    //insere na subárvore da direita
                    buscarRecursivo(aux.pDir, chave, resposta, arq, comparacoes, transferencias);
                }
            }
        }
    }
}

TItem* pesquisarArvoreBinaria(int chave, const char* nome_arquivo, long long int* comparacoes, long long int* transferencias, double* tempo){
    
    clock_t inicio = clock();
    
    *transferencias = 0;
    *comparacoes = 0;
    
    FILE* arq;
    TItem* resposta;
    TItem aux;
    
    if((arq = fopen(nome_arquivo, "rb")) == NULL)
        cout << "Erro ao abrir o arquivo" << endl;
    
    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);
    
    if(tamanho == 0){
        resposta = NULL;
    }else{
        buscarRecursivo(0, chave, &resposta, arq, comparacoes, transferencias);
    }
    
    fclose(arq);
    
     clock_t fim = clock();
     *tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;
    
    return resposta;
}

/* Funções de Criação da Árvore */

//função recursiva auxiliar da funcao inserirItem(...)
void inserirRecursivo(long int localraiz, TItem p, FILE* arq, long long int* comparacoes, long long int* transferencias){

    TNo aux;
    if(fseek(arq, localraiz, SEEK_SET) != 0)
        cout << "Erro no fseek" << endl;
    
    (*transferencias)++;
    if(fread(&aux, sizeof(TNo), 1, arq) == 1){
        (*comparacoes)++;
        if(aux.item.chave > p.chave){ //o item tem que ser inserido à esquerda
            
            if(aux.pEsq == SEM_FILHO){ //não tem filho à esquerda
            
                long int localpai = localraiz;
                
                //cria nó
                TNo novo;
                novo.item = p;
                novo.pEsq = SEM_FILHO;
                novo.pDir = SEM_FILHO;
                
                //escreve nó no fim do arquivo
                fseek(arq, 0, SEEK_END);
                fwrite(&novo, sizeof(TNo), 1, arq);
                
                long int localfilho = ftell(arq) - sizeof(TNo);
                
                //dizendo ao pai que tem um filho
                fseek(arq, localpai, SEEK_SET);
                aux.pEsq = localfilho;
                fwrite(&aux, sizeof(TNo), 1, arq);
                
            }else{ //tem filho à esquerda
                
                //insere na subárvore da esquerda
                inserirRecursivo(aux.pEsq, p, arq, comparacoes, transferencias);
            }
        }else{ //o item tem que ser inserido à direita
            
            if(aux.pDir == SEM_FILHO){ //não tem filho à direita
            
                long int localpai = localraiz;
                
                //cria nó
                TNo novo;
                novo.item = p;
                novo.pEsq = SEM_FILHO;
                novo.pDir = SEM_FILHO;
                
                //escreve nó no fim do arquivo
                fseek(arq, 0, SEEK_END);
                fwrite(&novo, sizeof(TNo), 1, arq);
                
                long int localfilho = ftell(arq) - sizeof(TNo);
                
                //dizendo ao pai que tem um filho
                fseek(arq, localpai, SEEK_SET);
                aux.pDir = localfilho;
                fwrite(&aux, sizeof(TNo), 1, arq);
                
            }else{ //tem filho à direita
                
                //insere na subárvore da direita
                inserirRecursivo(aux.pDir, p, arq, comparacoes, transferencias);
            }
        }
    }
}

//função auxiliar da função criarArvoreBinaria(...)
void inserirItem(TItem p, FILE* arq, long long int* comparacoes, long long int* transferencias){

    fseek(arq, 0, SEEK_END);
    long int tamanho = ftell(arq);
    
    if(tamanho == 0){
        TNo no;
        no.item = p;
        no.pEsq = SEM_FILHO;
        no.pDir = SEM_FILHO;
        fwrite(&no, sizeof(TNo), 1, arq);
    }else{
        inserirRecursivo(0, p, arq, comparacoes, transferencias);
    }
}

void criarArvoreBinaria(const char* nome_arq_entrada, const char* nome_arq_saida, long long int* comparacoes, long long int* transferencias, double* tempo){
    
    clock_t inicio = clock();
    
    *transferencias = 0;
    *comparacoes = 0;
    
    FILE* arq_entrada;
    FILE* arq_saida;
    
    if((arq_entrada = fopen(nome_arq_entrada, "rb")) == NULL)
        cout << "Erro ao abrir arquivo" << endl;
    
    if((arq_saida = fopen(nome_arq_saida, "w+b")) == NULL)
        cout << "Erro ao criar arquivo" << endl;
    
    TItem p;
    
    while(fread(&p, sizeof(TItem), 1, arq_entrada) == 1){
        (*transferencias)++;
        inserirItem(p, arq_saida, comparacoes, transferencias);
    }
    
    fclose(arq_saida);
    fclose(arq_entrada);
    
    clock_t fim = clock();
    *tempo = ((double) fim - inicio) / CLOCKS_PER_SEC;
}