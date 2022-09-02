#include "../include/descompHuff.h"

int main(int argc, char ** argv)
{
  FILE *comp;
 //testa se o nome do arquivo foi passado por linha de comando
 if(argv[1]!=NULL)
 {   
   //abertura do arquivo passado por linha de comando
   comp=fopen(argv[1],"rb");
   if(comp==NULL)
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

 //descompacta o arquivo passado por linha de comando
 descompacta_arquivo(comp,argv[1]); 

 //fecha o arquivo compactado
 fclose(comp);

 return 0;
} 