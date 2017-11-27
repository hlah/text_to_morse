#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ABP/abp.h"


/*****************************************************
 * monta_abp_morse:
 * params: FILE* fd - fileDescriptor do arquivo que contem a tabela morse
 *         insereFuncPtr insert: Ponteiro de funçao para a funcao de insercao na arvore.
 * return:
 *          root: ponteiro para a raiz da arvore montada
 *****************************************************/
pNodoA* monta_abp_morse(FILE *fd, insereFuncPtr insert)
{
	char	morse[MORSELEN];
    tipoinfo info;
    pNodoA* root= NULL;
    while(fscanf(fd, "%c\t%s\n", &info.key, info.code) == 2) {
		info.key = toupper(info.key);
        root= insert(root, info);
    }
    return root;
}

/*****************************************************/
int main(int argc, char* argv[]) {
	FILE*  	tabelaMorseFD;
	FILE*  	texto_origem;
	FILE*  	texto_destino;
	char	espaco;
    pNodoA* rootMorse;
	char	letra;

	// abre tabela do codigo morse
	tabelaMorseFD = fopen(argv[1], "r");
	// testa abertura
	if( tabelaMorseFD == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[1]);
	} else {
        rootMorse= monta_abp_morse(tabelaMorseFD, InsereArvore);
		// fecha tabela morse
		fclose(tabelaMorseFD);
	}
    printf("TABELA MORSE:INICIO\n");
    Central(rootMorse);
    printf("TABELA MORSE:FIM\n");
    
	
	// abre arquivo destino
	texto_origem = fopen(argv[2], "r");
	// abre destino
	texto_destino = fopen(argv[3], "w");

	// testa abertura dos arquivos
	if( texto_origem == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[2]);
	} else if( texto_destino == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[3]);
		// fecha origem
		fclose(texto_origem);
	} else {
		// inicia variavel que determina se último carcter era espaço (ou '\n')
		espaco = 0;
		while(fscanf(texto_origem, "%c", &letra) == 1) {
			// verifica se é ' ' ou '\n'
			if( letra == ' ' || letra == '\n') {
				// se era espaco antes não faz nada
				if(!espaco) {
					// coloca " / " no arquivo destino
					fprintf(texto_destino, "/ ");
				}
				// seta variavel
				espaco = 1;
			} else {
				// converte letra para upercase
				letra = toupper(letra);
				// TEM QUE REMOVER OS ACENTOS TAMBÈM.....

				// AQUI CONSULTA ARVORE, CONVERTE PARA MORSE E SALVA NO ARQUIVO //
				
				fprintf(texto_destino, "%c ", letra); // escreve sem converter, para teste


				// reseta variavel
				espaco = 0;
			}
		}

		// fecha origem
		fclose(texto_origem);
		// fecha destino
		fclose(texto_destino);
	}
	
	return 0;
}
/*****************************************************/
