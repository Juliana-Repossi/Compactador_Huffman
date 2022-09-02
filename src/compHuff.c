#include "../include/compHuff.h"

int* Contador_de_frequencia(FILE *arq)
{
  //para armazenar as frequencias
  int *vetor=(int*)calloc(257,sizeof(int));
  //posição 258 para computar quantidade de caracteres
  //para carregar os blocos do arq
  unsigned char c[BLOCK];
  int indicador=0;
  
  do
  {    
  //carregar BLOCK(10.000) caracteres por vez no array
  //o indicador sinaliza quantos caracteres foram lidos
  indicador=fread(c,sizeof(unsigned char),BLOCK,arq);
  //printf("%d\n",indicador); -> teste: ok

    //armazenar os caracteres lidos
    for(int i=0;i<indicador;i++)
    {
     //printf("%d %c\n",c[i],c[i]); //-> teste: ok
  
     //conta a frequencia do caracteres 0-256
     vetor[c[i]]++;
     //contabiliza o numero de caracteres lidos
     vetor[256]++;  
    }
   //achou o fim do arquivo
  }while(indicador==BLOCK);
  return vetor;
}


Arv* cria_nova_codificacao(int *vetor)
{
  //cria a lista para ordenar as frequencias
  Lista* listaFreq=inicializa_lista();

  //varer o vetor de caracter simples
  for(int i=0;i<256;i++)
  {
    //se houver ocorrencia do caractere
    if(vetor[i]!=0)
    {
      //cria o nó folha com o caractere;
      Arv* folha=arv_cria_folha(i);
      //insere na lista de frequencia de forma ordenada
      insere_ordenado_lista(listaFreq,folha,vetor[i]);
    }    
  }
  //imprime_lista(listaFreq); //teste -> ok
 
  //monta a arvore a partir da lista 
  while(!lista_unitaria(listaFreq))
  {
    //retira as duas letras de frequencia mais baixa;
    Celula* primeira=retira_inicio_lista(listaFreq);
    Celula* segunda=retira_inicio_lista(listaFreq);

    //monta uma arvore com os dois nós folhas
    Arv* no = arv_cria_Nfolha (retorna_arvore(primeira), retorna_arvore(segunda));

    //insere nova celula com nova frequencia e novo nó
    insere_ordenado_lista(listaFreq,no,retorna_frequencia(primeira)+retorna_frequencia(segunda));

    //libera as duas celulas antigas
    libera_celula(primeira);
    libera_celula(segunda);
    
  };

  //pega a unica celula da lista
  Celula *cel=retira_inicio_lista(listaFreq);
  //retorna o ponteiro raiz da arvore
  Arv *raiz=retorna_arvore(cel);

  //libera a celula
  libera_celula(cel);
  
  //libera sentinela da lista
  libera_sentinela(listaFreq);  

  return raiz;
}

unsigned char** novo_ASCII(Arv *Cod)
{
  //altura da arvore para saber qual vai ser o tamanho maximo de bits por caractere
  int alt = altura(Cod);

  //printf("%d\n",alt); //teste -> ok

  //alocar uma "tabela"
  unsigned char **tab=(unsigned char**)calloc(256,sizeof(unsigned char*));

  //temporário
  unsigned char *temp=(unsigned char*)calloc((alt+1),sizeof(unsigned char));

  //achar a codificação de cada caracter
  monta_ascii(Cod,temp,tab,alt);

  //libera o temporário
  free(temp);  

  /*
  for(int i=0;i<256;i++)
  {
    printf("%c  %s\n",i,tab[i]);
    
  } 
  */
  //teste ok! 

  return tab;
}

static void coloca_int_char_arq(int num,FILE *arq)
{
  int aux=num;
  int cont=0;
  //contar a quantidade de casas decimais
  do
  {
    aux=aux/10;
    cont++;
  }while(aux!=0);

  //inserir cada numero
  while(cont!=0)
  {
    aux=num;
    aux=aux/(pow(10,cont-1));
    num=num-(aux*(pow(10,cont-1)));
    aux=aux+48;
    //printf(" %c ",aux);
   //inserir no arq o numero de caracteres
   //inserir no arq o numero de caracteres
   fwrite(&aux,sizeof(unsigned char),1,arq);
   cont--;
  }

}

void criptografa_texto(unsigned char** tab,int *freq, char* ext, FILE *arq, FILE *comp)
{
  int tam=100;
  int indicador=0;
  unsigned char c[tam];
  //inicializa um bitmap
  bitmap* bitm=bitmapInit(8);
  char space[2]={" "};

  //coloca a quantidade de caracteres no arq, no formato char
  coloca_int_char_arq(freq[256],comp);
  //inserir no arq o espaço
  fwrite(space,sizeof(unsigned char),1,comp);

  int t=strlen(ext);

  for(int j=0;j<t;j++)
  {
  //inserir no arq a ext
  fwrite(ext+j,sizeof(unsigned char),1,comp);
  }
  
  //inserir no arq o espaço
  fwrite(space,sizeof(unsigned char),1,comp);
  
  //inserir no arq o vetor de freq
  for(int i=0;i<256;i++)
  {
  //inserir cada freq no arq
  coloca_int_char_arq(freq[i],comp);
  //inserir no arq o espaço
  fwrite(space,sizeof(unsigned char),1,comp);
  }

  do
  {
    //carregar um caracter do arquivo original
    indicador=fread(c,sizeof(unsigned char),tam,arq);  

    //printf("%d\n",indicador);
    //printf("%s\n",c);   

    //traduzir cada caracter
    for(int j=0; j<indicador; j++)
    {
      int bits=strlen((char*)tab[c[j]]);
      //printf("%d %s\n",bits,tab[c[j]]);

      //colocar os bits no bitmap
      for(int i=0;i<bits;i++)
      {
        if(bitmapGetLength(bitm) == bitmapGetMaxSize(bitm))
        {
          fwrite(bitmapGetContents(bitm),sizeof(unsigned char),1,comp);
          bitmapLibera(bitm);
          bitm=bitmapInit(8);
        }
        bitmapAppendLeastSignificantBit(bitm,tab[c[j]][i]);
        //printf("%c",tab[c[j]][i]);
      }
    }       
  }while(indicador==tam);

  //se ainda há algo para escrever 
  if(bitmapGetLength(bitm)!=0)
  {
    fwrite(bitmapGetContents(bitm),sizeof(unsigned char),1,comp);
  }
  bitmapLibera(bitm);  
}

int* libera_contador_freq(int *vetor)
{
  if(vetor!=NULL)
  {
    free(vetor);
  }
  return NULL;
}

unsigned char** libera_tabela(unsigned char **tab)
{
  if(tab!=NULL)
  {
    for(int i=0;i<256;i++)
    {
      if(tab[i]!=NULL)
      free(tab[i]);
    }
  free(tab);
  }
  return NULL;
}
  