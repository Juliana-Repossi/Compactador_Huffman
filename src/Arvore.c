#include "../include/Arvore.h"

struct arv {
  Arv *esq;
  Arv *dir;
  int ident;
  unsigned char item;
};

Arv* arv_cria_folha (unsigned char ch)
{
  //aloca a estrutura
  Arv *folha=(Arv*)malloc(sizeof(Arv));
  folha->ident=FOLHA;
  folha->esq=NULL;
  folha->dir=NULL;
  folha->item=ch;

  return folha;  
}

Arv* arv_cria_folha_serializacao(unsigned char ch)
{
  //aloca a estrutura
  Arv *folha=(Arv*)malloc(sizeof(Arv));
  folha->ident=SERIALIZACAO;
  folha->esq=NULL;
  folha->dir=NULL;
  folha->item=ch;

  return folha;  
}

Arv* arv_cria_Nfolha (Arv *esq, Arv *dir)
{
  //aloca a estrutura
  Arv *Nfolha=(Arv*)malloc(sizeof(Arv));
  Nfolha->ident=NFOLHA;
  Nfolha->esq=esq;
  Nfolha->dir=dir;
  
  return Nfolha;  
}

int altura (Arv* a)
{
  int altesq=0;
  int altdir=0;
  int alt=0;

  if(a!=NULL)
  {
    alt++;
    altesq = altesq + altura(a->esq);
    altdir = altdir + altura(a->dir);
  
    if(altesq>=altdir)
    {
      return alt= alt + altesq;
    }
      return alt= alt +altdir;
  }
  return -1;
}

void monta_ascii(Arv *Cod,unsigned char *vet,unsigned char **tabela, int alt)
{
  unsigned char esq[alt+1];
  unsigned char dir[alt+1];


  if(Cod->ident==FOLHA)
  {    
    //alocar na tabela a string e copiar
    tabela[Cod->item]=(unsigned char*)calloc((alt+1),sizeof(unsigned char));
    //copiar string
    strcpy((char*)tabela[Cod->item],(char*)vet);
  }
  else
  {
   strcpy((char*)esq,(char*)vet);
   strcat(esq,"0");
   monta_ascii(Cod->esq,esq,tabela,alt);

   strcpy((char*)dir,(char*)vet);
   strcat(dir,"1");
   monta_ascii(Cod->dir,dir,tabela,alt); 
  }
  
}

void arv_imprime_arq (Arv* a,FILE *comp)
{
  char abre='<';
  char fecha='>';

  fwrite(&abre,sizeof(unsigned char),1,comp);

  if(a!=NULL)
  {
    if(a->ident==FOLHA)
    {
      fwrite(&a->item,sizeof(unsigned char),1,comp);
    }
    arv_imprime_arq(a->esq,comp);
    arv_imprime_arq(a->dir,comp);
  }
  fwrite(&fecha,sizeof(unsigned char),1,comp);
}

Arv* desserializa_arvore(Arv *a, FILE *comp)
{
  unsigned char aux;

  //ler um caracter
  fread(&aux,sizeof(unsigned char),1,comp);
  //printf("%c",aux);
 
  if(aux=='<')
  {
    a = arv_cria_Nfolha(NULL,NULL);
    a->esq = desserializa_arvore(a->esq,comp);
    //se criou uma folha na ultima execução
    if(a->esq->ident==SERIALIZACAO)
    {
      //reseta indicador
      a->esq->ident=FOLHA;
      Arv *t = a->esq;
      free(a);
      return t;
    }

    a->dir = desserializa_arvore(a->dir,comp);
    //ler o fechamento >
    fread(&aux,sizeof(unsigned char),1,comp);
    //printf("%c",aux);

    return a;
    
  }
  else
  {
    char lixo[5];
    fread(lixo,sizeof(unsigned char),5, comp);
    //printf("%s",lixo);
    //é um char
    //Usar 
    return arv_cria_folha_serializacao(aux);
  }
}

Arv* retorna_esq(Arv *a)
{
  return a->esq;
}

Arv* retorna_dir(Arv *a)
{
  return a->dir;
}

unsigned char retorna_item(Arv *a)
{
  return a->item;
}

int retorna_ident(Arv *a)
{
  return a->ident;
}

Arv* arv_libera (Arv* a)
{
  if(a!=NULL)
  {
    arv_libera(a->esq);
    arv_libera(a->dir);
    free(a);
  }
  return NULL;
}
