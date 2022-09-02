#ifndef LISTAD_H
#define LISTAD_H

#include "Arvore.h"

//Implementação do tipo lista duplamente encadeada com sentinela

typedef struct lista Lista;

typedef struct celula Celula;

/**
* @brief Aloca uma estrutura do tipo lista e retorna seu endereço
* @return Ponteiro valido para a estrutura do tipo lista alocada
**/
Lista* inicializa_lista();

/**
* @brief Insere de forma ordenada crescente de frequencia o nó na lista
* @param lista - ponteiro válido para lista
* @param no - ponteiro para uma arvore/nó 
* @param freq - frequencia do nó respectivo passado
* @return Imprime "Nó/Árvore Inválida" caso o ponteiro no aponte para NULL;
**/
void insere_ordenado_lista(Lista *lista, Arv *no,int freq);

/**
* @brief Retira a primeira célula da lista
* @param Ponteiro valido para a estrutura lista
* @return Imprime mensagem de lista vazia ou retorna o Ponteiro para a celula retirada
**/
Celula* retira_inicio_lista(Lista *lista);

/**
* @brief Retorna um ponteiro para a arvore interna a estrutura celula
* @param Ponteiro valido para a estrutura celula
* @return Retorna a Arvore da Celula
**/
Arv* retorna_arvore(Celula *cel);

/**
* @brief Retorna a frequencia interna da estrutura celula 
* @param Ponteiro valido para a estrutura celula
* @return Retorna a frequencia da Celula
**/
int retorna_frequencia(Celula *cel);

/**
* @brief Libera uma celula passada sem liberar a estrutura interna (o nó)  
* @param Ponteiro valido para a estrutura celula
* @return memória alocada para a célula liberada
**/
void libera_celula(Celula *cel);

/**
* @brief Testa se a lista tem apenas uma celula, retornando 1 para esse caso e 0 para o caso contrario 
* @param Ponteiro valido para lista
* @return 1 - caso a lista tenha apenas um elemento e 0 para o caso contrario
**/
int lista_unitaria(Lista *lista);

/**
* @brief Libera sentinela da lista passada  
* @param Ponteiro valido para a estrutura lista
* @return memória ocupada pela sentinela da lista liberada
**/
void libera_sentinela(Lista *lista);

#endif