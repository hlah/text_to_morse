#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"


int main()
{
    pNodoA *arv = NULL, *procurado=NULL;

    tipoinfo novo_nodo;

    novo_nodo.key='A';
    strcpy(novo_nodo.code,".-");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='B';
    strcpy(novo_nodo.code,"-...");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='C';
    strcpy(novo_nodo.code,"-.-.");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='D';
    strcpy(novo_nodo.code,"-..");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='E';
    strcpy(novo_nodo.code,".");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='F';
    strcpy(novo_nodo.code,"..-.");
    arv = InsereArvore(arv, novo_nodo);
    novo_nodo.key='G';
    strcpy(novo_nodo.code,"--.");
    arv = InsereArvore(arv, novo_nodo);


   Central(arv);
   printf("----\n\n");

  
   preFixado(arv);
}


