#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "arvoreBinaria.hpp"
#include "item.h"

using namespace std;


//Função que cria a arvore

void criarArvoreBin(const char* arqEntrada, const char* arqSaida, long long int* comp, long long int* trans, double* tempo) {

	//abre os arquivo
	FILE* entrada;
	FILE* saida;

	TItem item; // item auxiliar 

	   
	if ((entrada = fopen(arqEntrada, "rb")) == NULL)// abre pra leitura binaria
		cout << "Erro ao abrir arquivo\n";

	if ((saida = fopen(arqSaida, "w+b")) == NULL)//cria e edita o arquivo de sairda
		cout << "Erro ao criar arquivo\n";

	while(fread(&item, sizeof(TItem), 1, entrada) == 1) {
		/*(*transferencias)++*/
		addItem(item, saida, comp, trans);// função pra adicionar itens na arvore;
	}


	//Fecha os arquivo
	fclose(entrada);
	fclose(saida);

}


void addItem(TItem item, FILE* arq, long long int* comp, long long int* trans) {

	//navega ate o fim do arquivo e se tiver vazio cria o No raiz;
	fseek(arq, 0, SEEK_END);
	long int tam = ftell(arq);



	if (tam == 0) {// faz a criação e gravação do no raiz
		TNo no;
		no.item = item;
		no.pEsq = NULL;
		no.pDir = NULL;
		fwrite(&no, sizeof(TNo), 1, arq);
	}
	else {

		// função auxiliar pra inserir recursivamente;
		insereRec(0, item, arq, comp, trans);
	}
}




void insereRec(long int localraiz, TItem item, FILE* arq, long long int* comp, long long int* trans) {

	TNo aux;// No auxiliar


	if (fseek(arq, localraiz, SEEK_SET) != 0)
		cout << "Erro no fseek" << endl;

	//(*transferencias)++;

	if (fread(&aux, sizeof(TNo), 1, arq) == 1) {

		//(*comparacoes)++;


		//testa se o item tem que ser inserido à esquerda
		if (aux.item.chave > item.chave) {

			if (aux.pEsq == NULL) { //não tem filho à esquerda

				long int localpai = localraiz;

				//cria no auxiliar
				TNo auxNo;
				auxNo.item = item;
				auxNo.pEsq = NULL;
				auxNo.pDir = NULL;

				//escreve nó no fim do arquivo
				fseek(arq, 0, SEEK_END);
				fwrite(&auxNo, sizeof(TNo), 1, arq);



				long int localfilho = ftell(arq) - sizeof(TNo); // Define o lugar aonde ta o nó que foi inserido atualmente

				//move o ponteiro ate o local do no pai aonde foi inserido
				fseek(arq, localpai, SEEK_SET);

				//seta o lugar do filho e grava no arquivo;
				aux.pEsq = localfilho;
				fwrite(&aux, sizeof(TNo), 1, arq);

			} else { 

			   //possue um filho na esqueda, insere na subárvore da esquerda chamando a recursividade;
				insereRec(aux.pEsq, item, arq, comp, trans);
			}

		}else { //o item tem que ser inserido à direita

			if (aux.pDir == NULL) { //não tem filho à direita

				long int localpai = localraiz;

				//cria no auxiliar
				TNo auxNo;
				auxNo.item = item;
				auxNo.pEsq = NULL;
				auxNo.pDir = NULL;

				//escreve nó no fim do arquivo
				fseek(arq, 0, SEEK_END);
				fwrite(&auxNo, sizeof(TNo), 1, arq);



				long int localfilho = ftell(arq) - sizeof(TNo); // Define o lugar aonde ta o nó que foi inserido atualmente

				//move o ponteiro ate o local do no pai aonde foi inserido
				fseek(arq, localpai, SEEK_SET);

				//seta o lugar do filho e grava no arquivo;
				aux.pDir = localfilho;
				fwrite(&aux, sizeof(TNo), 1, arq);

			}else {

				//possue um filho na direita, insere na subárvore da direita chamando a recursividade;
				insereRec(aux.pDir, item, arq, comp, trans);
			}
		}
	}
}

