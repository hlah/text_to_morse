#include <stdio.h>
#include <stdlib.h>
#include "abp.h"



pNodoA* InsereArvore(pNodoA *a, tipoinfo ch)
{
     if (a == NULL)
     {
         a =  (pNodoA*) malloc(sizeof(pNodoA));
         a->info = ch;
         a->esq = NULL;
         a->dir = NULL;
         a->FB = 0; // o nodo é sempre inserido como folha então seu fator de balanceamento é 0
         return a;
     }
     else
          if (ch.key < a->info.key)
              a->esq = InsereArvore(a->esq,ch);
          else if (ch.key > a->info.key)
              a->dir = InsereArvore(a->dir,ch);
     return a;
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%c | %s\n",a->info.key, a->info.code);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->esq);
          printf("%c | %s\n",a->info.key, a->info.code);
          Central(a->dir);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%c | %s\n",a->info.key, a->info.code);
      }
}

pNodoA* consultaABP(pNodoA *a, tipoinfo chave, unsigned long int*comp) {

    while (a!=NULL){
		  (*comp)++;
          if (a->info.key == chave.key )
             return a; //achou então retorna o ponteiro para o nodo
          else
            if (a->info.key > chave.key)
               a = a->esq;
            else
               a = a->dir;
            }
            return NULL; //se não achou
}

pNodoA* consultaABP2(pNodoA *a, tipoinfo chave) {
    if (a!=NULL) {


       if (a->info.key == chave.key)
         return a;
       else
           if (a->info.key > chave.key)
                return consultaABP2(a->esq,chave);
            if (a->info.key < chave.key)
                return consultaABP2(a->dir,chave);

            else return a;
       }
       else return NULL;
}

