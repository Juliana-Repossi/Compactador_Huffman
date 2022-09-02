#ifndef DESCOMPHUFF_H
#define DESCOMPHUFF_H

#define BLOCK 10000

#include "compHuff.h"

/**
* @brief Lê um numero do arquivo que foi escrito em formato de caracter e transforma-o para int novamente
* @param ponteiro para o arquivo
* @return Retorna um numero lido agora no formato de inteiro
**/
static int le_char_int_arq(FILE *arq);

/**
* @brief Lê o cabeçalho do arquivo compactado nos padrão :"numero de caracteres" "extensão do arquivo original" "serialização do vetor de frequencias" "texto codificado" e reproduz o arquivo original.
* @param ponteiro para o arquivo compactado
* @param nome do arquivo compactado
* @pos-processamento arquivo original criado idêntico ao anterior ao processo de compactação
**/
void descompacta_arquivo(FILE *comp,char* nome_arq);

/**
* @brief Lê a parte textual do arquivo compactado "comp" e traduz, colocando essa tradução no arquivo "arq" passado
* @param árvore de codificação de huffman
*@param ponteiro para arquivo compactado
* @param ponteiro para arquivo original aberto para escrita
* @param quantidade de caracteres do arquivo original, lido no cabeçalho do compactado
**/
void traduz_texto(Arv *code, FILE *comp, FILE *arq, int quant);

#endif