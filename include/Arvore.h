#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FOLHA 1
#define NFOLHA 0
//auxiliador para desserialização
#define SERIALIZACAO 2

typedef struct arv Arv;

/**
* @brief Cria e preenche uma estrutura Arv do tipo nó folha com o caractere passado
* @param caractere;
* @return arvore válida e alocada com a informação passada
**/ 
Arv* arv_cria_folha (unsigned char ch);

/**
* @brief Cria e preenche uma estrutura Arv do tipo nó folha de serialização com o caractere passado
* @param caractere;
* @return arvore válida e alocada com a informação passada
**/ 
Arv* arv_cria_folha_serializacao(unsigned char ch);

/**
* @brief Cria e preenche uma estrutura Arv do tipo nó não folha com as subarvores passadas
* @param subarvore da esq e subarvore da direita válidas;
* @return arvore válida e alocada com as informações passadas
**/ 
Arv* arv_cria_Nfolha (Arv *esq, Arv *dir);

/**
* @brief Calcula a altura da arvore passada;
* @param Ponteiro para a Arvore;
* @return -1 caso arvore vazia, 0 caso haja apenas um nó raiz , ou um inteiro maior que 0, sendo esse a altura 
**/ 
int altura (Arv* a);

/**
* @brief Armazena na tabela (do tipo Hash) os novos códigos produzidos pela arvore, de cada caractere contido nela
* @param Cod - Ponteiro para a Arvore válida e preenchida;
* @param vet - vetor do caminho já percorrido a arvore;
* @param tabela - vetor de ponteiros alocado de tamanho 256 (conceito de tabela Hash);
* @param alt - altura da arvore ;
* @pós-processamento Na posição do caractere ocorrido, aloca-se uma string para armazenar a nova codificação do mesmo;
**/
void monta_ascii(Arv *Cod,unsigned char *vet,unsigned char **tabela, int alt);

/**
* @brief Imprime a serialização de uma arvore num arquivo binario passado em pre-ordem;
* @param Ponteiro válido para arvore;
* @param Ponteiro válido para arquivo;
**/ 
void arv_imprime_arq (Arv* a,FILE *comp);

/**
* @brief Monta uma arvore a partir de sua serialização;
* @param Ponteiro válido para arquivo na posição de inicio da serialização da arvore;
* @return Arvore de codificação montada e alocada;
**/ 
Arv* desserializa_arvore(Arv *a, FILE *comp);

/**
* @brief Retorna a subarvore da esquerda de uma arvore;
* @param Ponteiro válido para uma arvore;
* @return Subarvore da esquerda de uma dada arvore a;
**/ 
Arv* retorna_esq(Arv *a);

/**
* @brief Retorna a subarvore da direita de uma arvore;
* @param Ponteiro válido para uma arvore;
* @return Subarvore da direita de uma dada arvore a;
**/ 
Arv* retorna_dir(Arv *a);

/**
* @brief Retorna o item (caractere) de uma arvore;
* @param Ponteiro válido para uma arvore;
* @return item(caractere) de uma dada arvore a;
**/ 
unsigned char retorna_item(Arv *a);

/**
* @brief Retorna o campo ident de uma arvore;
* @param Ponteiro válido para uma arvore;
* @return 0 - caso nó não folha, 1 - caso nó folha e 2 - caso seja um nó recem alocado pela desserializa_arvore ;
**/ 
int retorna_ident(Arv *a);

/**
* @brief Libera uma arvore;
* @param Ponteiro para arvore;
* @return NULL e memória liberada;
**/ 
Arv* arv_libera (Arv* a);

#endif