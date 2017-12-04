#ifndef _ABP_H_
#define _ABP_H_
#define MORSELEN 15
typedef struct
{
    char key;
    char code[MORSELEN];
} tipoinfo;

struct TNodoA{
        tipoinfo info;
        int FB;
        struct TNodoA *esq;
        struct TNodoA *dir;
};

typedef struct TNodoA pNodoA;

typedef pNodoA* (*insereFuncPtr)(pNodoA *a, tipoinfo ch);

pNodoA* InsereArvore(pNodoA *a, tipoinfo ch);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, tipoinfo chave, unsigned long int*comp);
pNodoA* consultaABP2(pNodoA *a, tipoinfo chave);

#endif
