#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

pNodoA* InsereWrapper(pNodoA *a, TipoInfo info)
{
    int ok;
    return InsereAVL(a,info,&ok);
}

int main()
{

    pNodoA *arv = NULL;
    pNodoA *arv2 = NULL;
    int i, ok;



    printf("insere 42\n");
    arv = InsereAVL(arv, 42,&ok);
    printf("insere 15\n");
    arv = InsereAVL(arv, 15,&ok);
    printf("insere 88\n");
    arv = InsereAVL(arv, 88,&ok);
    printf("insere 6\n");
    arv = InsereAVL(arv, 6,&ok);
    printf("insere 27\n");
    arv = InsereAVL(arv, 27,&ok);
    printf("insere 4\n");
    arv = InsereAVL(arv, 4,&ok);

    printf("insere 42\n");
    arv2 = InsereWrapper(arv2, 42);
    printf("insere 15\n");
    arv2 = InsereWrapper(arv2, 15);
    printf("insere 88\n");
    arv2 = InsereWrapper(arv2, 88);
    printf("insere 6\n");
    arv2 = InsereWrapper(arv2, 6);
    printf("insere 27\n");
    arv2 = InsereWrapper(arv2, 27);
    printf("insere 4\n");
    arv2 = InsereWrapper(arv2, 4);


    printf("avr:\n");
    Desenha(arv,1);
    printf("avr2:\n");
    Desenha(arv2,1);



    if (is_avl(arv)) puts("Eh AVL");
    else puts("Nao eh AVL");


}

