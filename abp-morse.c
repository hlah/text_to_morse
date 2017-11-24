#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MORSELEN 15

int main(int argc, char* argv[]) {
	FILE*  	tabela_morse;
	FILE*  	texto_origem;
	FILE*  	texto_destino;
	char	letra;
	char	morse[MORSELEN];
	char	espaco;

	// abre tabela do codigo morse
	tabela_morse = fopen(argv[1], "r");
	// testa abertura
	if( tabela_morse == NULL ) {
		printf("Nao foi possivel abrir o arquivo '%s'\n", argv[1]);
	} else {
		// converte letra para uppercase
		letra = toupper(letra);
		while(fscanf(tabela_morse, "%c\t%s\n", &letra, morse) == 2) {
			// AQUI COLOCA CHAVE=letra E VALOR=morse NA ÁRVORE

		}
		// fecha tabela morse
		fclose(tabela_morse);
	}
	
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
