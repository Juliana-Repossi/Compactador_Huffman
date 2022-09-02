#ifndef COMPHUFF_H
#define COMPHUFF_H

#define BLOCK 10000

//compactador de Huffman utilizando arvore binária e lista 
#include "ListaD.h"
#include "bitmap.h"
#include "math.h"

/**
* @brief Conta a frequencia de cada caractere do arquivo binário passado
* @param ponteiro para o arquivo binário a ser compactado
* @return Retorna um vetor alocado com 257  posições, com a frequencia de cada caractere ASCII do texto, e a ultima posição com a quantidade de caracteres do texto;
**/
int* Contador_de_frequencia(FILE *arq);

/**
* @brief Cria uma codficação de huffman (em árvore) a partir de um vetor contendo a frequencia de caracteres em modo de tabela Hash
* @param ponteiro para o vetor (em modo Hash) de frequencia dos caracteres
* @return Retorna um ponteiro para o nó raiz da arvore de codficação de huffman
**/
Arv* cria_nova_codificacao(int *vetor);

/**
* @brief Cria uma tabela de codificação de huffman
* @param ponteiro válido para a arvore de codificação de Huffman
* @return Retorna um ponteiro de ponteiro para a tabela contendo os caracteres e suas respectivas novas codificações no formato de tabela Hash
**/
unsigned char** novo_ASCII(Arv *Cod);

/**
* @brief Transforma um número(int) em uma string de caracteres e a insere no arquivo;
* @param numero a ser inserido
* @param ponteiro para arquivo
**/
static void coloca_int_char_arq(int num,FILE *arq);

/**
* @brief Faz toda a compactação do arquivo original dada as ferramentas nescessarias passadas por parâmetro
* @param ponteiro válido para a tabela de codificação;
* @param ponteiro válido para vetor de frequencias de cada caracter;
* @param string contendo a extensão do arquivo original
* @param ponteiro válido para o arquivo original
* @param ponteiro válido para o arquivo compactado
**/
void criptografa_texto(unsigned char** tab,int *freq, char* ext, FILE *arq, FILE *comp);

/**
* @brief Libera o vetor de frequencia alocado pela função "Contador_de_frequencia" do TAD
* @return NULL e Mémoria liberada 
**/
int* libera_contador_freq(int *vetor);

/**
* @brief Libera a tabela de codificação 
* @return NULL e Mémoria liberada
**/
unsigned char** libera_tabela(unsigned char **tab);

#endif