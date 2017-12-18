#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "ABP/abp.h"
#include "ABP/avl.h"

#define AVL_OPTION "avl"

#define ARGV_TABELA_MORSE_OFFSET 	1
#define ARGV_TEXTO_INPUT_OFFSET		2
#define ARGV_TEXTO_OUTPUT_OFFSET	3
#define ARGV_AVL_OPTION_OFFSET		4

/*****************************************************
 * monta_abp_morse:
 * params: FILE* fd - fileDescriptor do arquivo que contem a tabela morse
 *         insereFuncPtr insert: Ponteiro de funçao para a funcao de insercao na arvore.
 * return:
 *          root: ponteiro para a raiz da arvore montada
 *****************************************************/
pNodoA* monta_abp_morse(FILE *fd, insereFuncPtr insert)
{
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
char processa_letra(wchar_t letra) {
	// mapa de caracteres acentuados
	const wchar_t* acentuadas_mapa = 	L"ÁÀÃÂÄÉÈÊËÍÌÎĨÏÓÒÔÕÖÚÙÛŨÜÇÑ";
	const char* normais_mapa = 			 "AAAAAEEEEIIIIIOOOOOUUUUUCN";
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
	wchar_t	letra_wide;
	pNodoA* consultaRetorno;
	tipoinfo chaveProcura;
	unsigned long int comp=0;
    clock_t startTimeConsulta, endTimeConsulta, elapsedTimeConsulta; //para contar o tempo
    clock_t startTimeInsert, endTimeInsert, elapsedTimeInsert; //para contar o tempo


	// função necessária para ler caracteres multi-byte apropriadamente
	setlocale(LC_ALL, "");

	// abre tabela do codigo morse
	tabelaMorseFD = fopen(argv[ARGV_TABELA_MORSE_OFFSET], "r");

    startTimeInsert= clock();

	// testa abertura
	if( tabelaMorseFD == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[ARGV_TABELA_MORSE_OFFSET]);
	} else {
        if(argc==ARGV_AVL_OPTION_OFFSET+1 && strcmp(argv[ARGV_AVL_OPTION_OFFSET],AVL_OPTION)==0){
            printf("*Usando AVL.\n");
            rootMorse= monta_abp_morse(tabelaMorseFD, InsereAVLWrapper);
        }else{
            printf("*Usando ABP sem balanceamento.\n");
            rootMorse= monta_abp_morse(tabelaMorseFD, InsereArvore);
        }

		// fecha tabela morse
		fclose(tabelaMorseFD);
	}
    endTimeInsert= clock();
    
	// abre arquivo destino
	texto_origem = fopen(argv[ARGV_TEXTO_INPUT_OFFSET], "r");
	// abre destino
	texto_destino = fopen(argv[ARGV_TEXTO_OUTPUT_OFFSET], "w");

	// testa abertura dos arquivos
	if( texto_origem == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[ARGV_TEXTO_INPUT_OFFSET]);
	} else if( texto_destino == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[ARGV_TEXTO_OUTPUT_OFFSET]);
		// fecha origem
		fclose(texto_origem);
	} else {
		// inicia variavel que determina se último carcter era espaço (ou '\n')
		espaco = 0;
        startTimeConsulta= clock();

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
				// processa caracter
				chaveProcura.key = processa_letra(letra_wide);

				/////// CONVERSÂO PARA MORSE AQUI //////////
				consultaRetorno = consultaABP(rootMorse, chaveProcura, &comp);

				// se caracter ausente na tabela, não converte
				if( consultaRetorno != NULL ) {
					// salva no arquivo
					fprintf(texto_destino, "%s ", consultaRetorno->info.code);
				}

				// reseta variavel -- ultima não foi espaço
				espaco = 0;
			}
		}
        endTimeConsulta= clock();

		// fecha origem
		fclose(texto_origem);
		// fecha destino
		fclose(texto_destino);
		if(CLOCKS_PER_SEC!= 1000000){
			elapsedTimeInsert= 1000000*(endTimeInsert - startTimeInsert)/CLOCKS_PER_SEC;
			elapsedTimeConsulta= 1000000*(endTimeConsulta - startTimeConsulta)/CLOCKS_PER_SEC;
		}else{
			elapsedTimeInsert= endTimeInsert - startTimeInsert;
			elapsedTimeConsulta= endTimeConsulta - startTimeConsulta;
		}
		printf("\tNUMERO DE COMPARACOES: %'ld comps\n", comp);
        printf("\tTempo de Insercao:     %'10ld us\n", elapsedTimeInsert);
        printf("\tTempo de Consulta:     %'10ld us\n", elapsedTimeConsulta);
        printf("\tTempo Total:           %'10ld us\n", elapsedTimeConsulta+elapsedTimeInsert);
	}
	
	return 0;
}
/*****************************************************/
