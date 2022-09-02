//Juliana Camilo Repossi - 2020100631
#include "../include/compHuff.h"

int main(int argc, char ** argv)
{
  FILE *arq;
 //testa se o nome do arquivofoi passado por linha de comando
 if(argv[1]!=NULL)
 {   
   //abertura do arquivo passado por linha de comando
   arq=fopen(argv[1],"rb");
   if(arq==NULL)
   {
     printf("Erro na abertura do arquivo %s\n",argv[1]);
     exit(1);
   }
 }
 else
 {
   printf("Erro: não foi passado o arquivo na linha de comando\n");
   exit(1);
 }  
 
 //Computar a frequencia dos caracteres
 int *freq=Contador_de_frequencia(arq);

 //criar nova codificação em arvore
 Arv *novaCod = cria_nova_codificacao(freq);

 //volta o cursor para o inicio do arquivo
 fseek(arq,  0,  SEEK_SET);

 //criar nome do arquivo para armazenar o compactado
 char comp[5]="comp";
 int tam=strlen(argv[1]);

 //guarda a extensão
 char ext[5]={}; 
 for(int i=0;i<tam;i++)
 {
   if(argv[1][i]=='.')
   {
     i++;
     strcpy(ext,argv[1]+i);
     //tirar a extensão do arquivo original
     argv[1][i]='\0';
      //adiciona a extensão comp
      strcat(argv[1],comp);
     break;
   }
 }
   
 //printf("%s\n",ext); //testes ok
 //printf("%s\n",argv[1]); //testes ok

 //criar um arquivo para guardar a compactação
 FILE *compac=fopen(argv[1],"wb");

 if(compac==NULL)
 {
   printf("Falha na abertura do arquivo %s\n",argv[1]);
 }

 //printf("%d\n",freq[256]); //teste ok

 //faz a nova sequencia de codificação
 unsigned char **tabela = novo_ASCII(novaCod);

 //"Traduzir"/compactar o texto
 criptografa_texto(tabela,freq,ext,arq,compac);

 //libera a memória alocada
 freq = libera_contador_freq(freq);
 novaCod = arv_libera (novaCod);
 tabela = libera_tabela(tabela);

 //fecha os arquivos
 fclose(arq);
 fclose(compac);

 return 0;
} 