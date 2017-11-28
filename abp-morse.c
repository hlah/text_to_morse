#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>
#include "ABP/abp.h"
#include "ABP/avl.h"

#define AVL_OPTION "avl"

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
/*****************************************************
 * processa_letra:
 * params: wchar_t letra: Letra a ser processada
 * return:
 			letra: letra recebida por argumento removida de acentos e em uppercase
 *****************************************************/
wchar_t processa_letra(wchar_t letra) {
	// mapa de caracteres acentuados
	const wchar_t* acentuadas_mapa = 	L"ÁÀÃÂÄÉÈÊËÍÌÎĨÏÓÒÔÕÖÚÙÛŨÜÇÑ";
	const wchar_t* normais_mapa = 		L"AAAAAEEEEIIIIIOOOOOUUUUUCN";
	int indice = 0;

	// transforma em uppercase
	letra = towupper(letra);

	// procura letra no mapa
	while( acentuadas_mapa[indice] != 0 && letra != acentuadas_mapa[indice] )
		indice++;
	// se letra está no mapa, substitui por correspondente
	if( acentuadas_mapa[indice] != 0 )
		letra = normais_mapa[indice];

	return letra;
}


/*****************************************************/
pNodoA* InsereAVLWrapper(pNodoA *a, tipoinfo info)
{
    int ok;
    return InsereAVL(a,info,&ok);
}

/*****************************************************/


int main(int argc, char* argv[]) {
	FILE*  	tabelaMorseFD;
	FILE*  	texto_origem;
	FILE*  	texto_destino;
	char	espaco;
    pNodoA* rootMorse;
	char	letra;
	wchar_t	letra_wide;

	// função necessária para ler cacteres multi-byte apropriadamente
	setlocale(LC_ALL, "");

	// abre tabela do codigo morse
	tabelaMorseFD = fopen(argv[1], "r");
	// testa abertura
	if( tabelaMorseFD == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[1]);
	} else {
        if(argc==5 && strcmp(argv[4],AVL_OPTION)==0){
            printf("Usando AVL.\n");
            rootMorse= monta_abp_morse(tabelaMorseFD, InsereAVLWrapper);
        }else{
            printf("Usando ABP sem balanceamento.\n");
            rootMorse= monta_abp_morse(tabelaMorseFD, InsereArvore);
        }

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
		while(fscanf(texto_origem, "%lc", &letra_wide) == 1) {
			// verifica se é ' ' ou '\n'
			if( letra_wide == ' ' || letra_wide == '\n') {
				// se era espaco antes não faz nada
				if(!espaco) {
					// coloca " / " no arquivo destino
					fprintf(texto_destino, "/ ");
				}
				// seta variavel
				espaco = 1;
			} else {
				// converte letra para upercase
				letra_wide = processa_letra(letra_wide);
				// TEM QUE REMOVER OS ACENTOS TAMBÈM.....

				// AQUI CONSULTA ARVORE, CONVERTE PARA MORSE E SALVA NO ARQUIVO //
				
				fprintf(texto_destino, "%lc ", letra_wide); // escreve sem converter, para teste


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
