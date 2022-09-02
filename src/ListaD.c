#include "../include/ListaD.h"

struct lista
{
  Celula *prim;
  Celula *ult;
};

struct celula
{
 Celula *prox;
 Celula *ant;
 Arv *no;
 int freq;
};

Lista* inicializa_lista()
{
  Lista *lista=(Lista*)malloc(sizeof(Lista));
  lista->prim=NULL;
  lista->ult=NULL;

  return lista;
}

void insere_ordenado_lista(Lista *lista, Arv *no,int freq)
{
  if(no==NULL)
  {
    printf("Nó/Árvore Inválida\n");
    exit(2);
  }

  Celula *nova=(Celula*)malloc(sizeof(Celula));
  nova->no=no;
  nova->freq=freq;

  //encadear na lista
  //testar se lista vazia
  if(lista->prim==NULL && lista->ult==NULL)
  {
    lista->prim=lista->ult=nova;
    nova->ant=nova->prox=NULL;
  }
  else
  {
    for(Celula *cel=lista->ult;cel!=NULL;cel=cel->ant)
    {
      if(nova->freq>=cel->freq)
      {
        //achou a posição
        nova->prox=cel->prox;
        cel->prox=nova;

        if(cel==lista->ult)
        {          
          nova->ant=cel;        
          lista->ult=nova;
          return;
        }
        else
        {
          nova->prox->ant=nova;
          cel->prox->ant=cel;
          return;
        }
      }
    }
    //caso seja a menor frequencia de todas
    nova->ant=NULL;
    nova->prox=lista->prim;
    nova->prox->ant=nova;
    lista->prim=nova;
    return;
  }  
}

Celula* retira_inicio_lista(Lista *lista)
{
  //testar se a lista é vazia, por segurança
  if(lista->prim==NULL)
  {
    printf("Lista Vazia\n");
    exit(2);
  }

  Celula *aux=lista->prim;

  //reencadear lista;
  //se é a unica celula da lista 
  if(lista->prim==lista->ult)
  {
    lista->prim=lista->ult=NULL;
  }
  else
  {
   lista->prim=aux->prox;
   if(lista->prim!=NULL)
    lista->prim->ant=NULL;
  }
  return aux;  
}

Arv* retorna_arvore(Celula *cel)
{
  return cel->no;
}

int retorna_frequencia(Celula *cel)
{
  return cel->freq;
}

void libera_celula(Celula *cel)
{
  if(cel!=NULL)
  free(cel);
}

int lista_unitaria(Lista *lista)
{
  if(lista->prim==lista->ult)
  return 1;
  return 0;
}

void libera_sentinela(Lista *lista)
{
  if(lista!=NULL)
    free(lista);
}