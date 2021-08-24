#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "geraArquivo.hpp"


using namespace std;

struct {

    int chave;
    long dado1;
    char dado2[501];
} Registro;

void criaArquivo(int situcao, long quantidade){

    FILE *arq; // variavel do arquivo
    long vetor[quantidade]; //vetor para aleatorio
    long aux; // variavel para auxiliar no aleatorio


    //Abre arquivo
    if ((arq = fopen("arquivo.bin", "w+b")) == NULL){

             cout << "Erro na abertura do arquivo" << endl;

        }

        switch (situcao){

            // Ordenado crescente
            case 1:
                for(int i = 0; i < quantidade; i++){
                    Registro.chave = i+1;
                    Registro.dado1 = rand();

                    for(int j = 0; j < 500; j++)
                        Registro.dado2[j] = rand() % 26 + 65;

                    fwrite(&Registro, sizeof(Registro), 1, arq);
                }
            break;

            // Ordenado Decrescente
            case 2:

                for(int i = (quantidade - 1); i >= 0; i--){
                    Registro.chave = i;
                    Registro.dado1 = rand();

                    for(int j = 0; j < 500; j++)
                        Registro.dado2[j] = rand() % 26 + 65;

                    fwrite(&Registro, sizeof(Registro), 1, arq);
                }
                break;

            // Aleatorio
            case 3:

                //zera as posicoes do vetor
                for (int i = 0; i <quantidade; i++){
                    vetor[i] = 0;
                }

                for (int i = 0; i < quantidade; i++){

                    aux = rand()%quantidade;

                    if (vetor[aux]== -1){
                        aux = rand()%quantidade;
                    }
                    else {
                        Registro.chave = aux+1;
                        vetor[aux] = -1;

                        Registro.dado1 = rand();

                        for(int j = 0; j < 500; j++)
                            Registro.dado2[j] = rand() % 26 + 65;


                        fwrite(&Registro, sizeof(Registro), 1, arq);

                    }

                }

        }

    fclose(arq);
}