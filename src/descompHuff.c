#include "../include/descompHuff.h"

static int le_char_int_arq(FILE *arq)
{
  char aux;
  int quant=0;
  //lê até encontrar o espaço
  while(1)
  {
   fread(&aux,sizeof(unsigned char),1,arq);
   if(aux==' ')
   {
     return quant;
   }
   //transformar char em int
   quant=quant*10+(aux-48);
  }
}

void descompacta_arquivo(FILE *comp,char* nome_arq)
{
  char aux;
  int quant=0;
  char ext[5]={};


  //lê a quantidade de caracteres
  quant=le_char_int_arq(comp);

  //printf("\n%d\n",quant); //perfeito
  
  //lê a extensão
  for(int j=0;;j++)
  {
    fread(&aux,sizeof(unsigned char),1,comp);
    if(aux==' ')
    {
      break;
    }
    ext[j]=aux;
  }
  

  //printf(".%s.\n",ext); //ok

  //nome do arquivo original
  nome_arq[strlen(nome_arq)-4]='\0';
  strcat(nome_arq,ext);

  //printf("%s\n",nome_arq); //ok;  

 
  int *freq=(int*)malloc(256*sizeof(int));

  //lê o vetor de frequencia do arq
  for(int i=0;i<256;i++)
  {
    freq[i]=le_char_int_arq(comp);
    //printf("%c %d\n",i,freq[i]);
  }

  //monta a arvore
  //Arv *Code = desserializa_arvore(Code,comp);
  Arv* Code=cria_nova_codificacao(freq);  

  //cria arquivo original
  FILE *arq=fopen(nome_arq, "w");
  if(arq==NULL)
  {
    printf("Erro na abertura do arquivo %s\n",nome_arq);
    exit(1);
  }

  //traduz o texto
  traduz_texto(Code,comp,arq,quant);
  
  //libera a memoria
  Code = arv_libera (Code);
  fclose(arq); 
  freq=libera_contador_freq(freq);
}

void traduz_texto(Arv *code, FILE *comp, FILE *arq, int quant)
{
  Arv *aux=code;
  int indicador;
  unsigned char c;

  do
  {
    //ler um caracter por vez
    indicador=fread(&c,sizeof(unsigned char),1,comp);

    //achar o char correspondente
    //percorre os 8 bits
    for(int i=7;i>-1;i--)
    {
      //ver se o bit é 0 ou 1
      if(c>=(pow(2,i)))
      {
        //bit igual a 1, logo arvore para a dir
        aux=retorna_dir(aux);
        //atualiza o valor do char
        c=c-(pow(2,i));
      }
      else
      {
        //bit igual a 0, logo arvore para a esq
        aux=retorna_esq(aux);
      }

      //ver se achou o caractere
      if(retorna_ident(aux)==FOLHA)
      {
        fprintf(arq,"%c",retorna_item(aux));
        quant--;
        if(quant==0)
        {
          //se ja inseriu todos os caracteres
          return;
        }
        //volta pro nó raiz da arvore
        aux=code;
      }
    }
  }while(indicador==1);  
}