#ifndef TP1_ARVOREBINARIA_HPP
#define TP1_ARVOREBINARIA_HPP


typedef struct No{

	TItem item;		//No item
	long pEsq;    //No filho da esquerda
	long pDir;    //No filho da direita

}TNo;

void criarArvoreBin(const char* arqEntrada, const char* arqSaida, long long int* comp, long long int* trans, double* tempo);

void addItem(TItem item, FILE* arq, long long int* comp, long long int* trans);

void insereRec(long int localraiz, TItem p, FILE* arq, long long int* comp, long long int* trans);

#endif //TP1_ARVOREBINARIA_HPP
