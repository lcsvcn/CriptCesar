#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG 0

struct palavras {
	char str[50];
	char lixo[50];
	char criptografado[50];
	int pos;
};

int main(int argc,char* argv[]) {
	FILE *arq_entrada;
	FILE *arq_saida;
	int i, j;
	int chave;
	char arquivo[50];
	char str[50];
	char lixo[50];
	char linha1[1000];
	char linha2[1000];
    int num_palavras;
    int chave_correta;
	
	char arquivo_decifrado[50];
	char arquivo_pref[50];

	chave_correta = -1;

	if(argc < 2) {
    	printf("./crypt <nome_arquivo_entrada>\n");
    	return 1;
    }

    arq_entrada = fopen(argv[1], "r");

    // se deu erro ao criar o arquivo
	if (arq_entrada == NULL) {
	    printf("Nao existe arquivo que foi pedido\n");
	    return 1;
	} 

	strcpy(arquivo_decifrado, argv[1]);

	for(i=0; i < strlen(arquivo_decifrado); i++) {
		arquivo_pref[i] = arquivo_decifrado[i];
		if(arquivo_decifrado[i] == '.') {
			arquivo_pref[i] = '\0';
			break;
		}
	}

	strcpy(arquivo_decifrado, arquivo_pref);
	strcat(arquivo_decifrado, ".raw");

	arq_saida = fopen(arquivo_decifrado, "w+");

	// se deu erro ao criar o arquivo
	if (arq_saida == NULL) {
	    printf("Nao existe arquivo que foi pedido\n");
	    return 1;
	}

	// percorre para saber quantas palavras vai ter
	for(i = 0; !feof(arq_entrada); i++) {
		if(fscanf(arq_entrada, "%[#]", lixo) == EOF) {
			break;
		}

		if(fscanf(arq_entrada, "%[^#]", str) == EOF) {
			break;
		}
		printf("%s\n", str);
		if(fscanf(arq_entrada, "%[#]", lixo) == EOF) {
			break;
		}

    	if(fscanf(arq_entrada, "%[^#]", lixo) == EOF) {
    		break;
		}
  	}

  	num_palavras = i;

  	if(LOG) printf("%d\n", num_palavras);

	struct palavras PAL[num_palavras];

	char separador;

	rewind(arq_entrada);

	for(i = 0; i < num_palavras; i++) {
  	
		for(j=0; !feof(arq_entrada); j++) {
			if(fscanf(arq_entrada, "%[a-zA-Z#]", str) == EOF) {
				break;
			}
			
			strcpy(PAL[j].str, str);

			// nao pode ler letra nem separador
    		if(fscanf(arq_entrada, "%[^a-zA-Z#]", lixo) == EOF) {
    			break;
    		}

			strcpy(PAL[j].lixo, lixo);
    		
		}
	}

	if(LOG) {
		for(i = 0; i < num_palavras; i++) {
  			printf("(%s)", PAL[i].str);
  		}
  		printf("\n");
  		for(i = 0; i < num_palavras; i++) {
  			printf("(%s)", PAL[i].lixo);
  		}
  		printf("\n");
  	}



		fprintf(arq_saida, "---------------------------\n");

		fprintf(arq_saida, "    INICIO FORCA BRUTA\n");

  	// teste bruto de chave - como sao 26 letras no alfabeto da pra fazer
  	for(chave = 0; chave < 27; chave++) {
  		fprintf(arq_saida, "---------------------------\n");
  		fprintf(arq_saida, "chave: %d\n", chave);
  		fprintf(arq_saida, "---------------------------\n");
		for(i = 0; i < num_palavras; i++) {
	  		for(j=0; j<strlen(PAL[i].str); j++) {
				if(PAL[i].str[j] != '\0') {
					int enc = (int) PAL[i].str[j] - chave;
					fprintf(arq_saida, "%c", (char) enc);
				}

			}
			fprintf(arq_saida, "%s", PAL[i].lixo);
		}
		fprintf(arq_saida, "\n");
	}

		fprintf(arq_saida, "---------------------------\n");

		fprintf(arq_saida, "      FIM FORCA BRUTA\n");
		fprintf(arq_saida, "---------------------------\n");

	printf("O texto foi decifrado no arquivo: %s\n", arquivo_decifrado);




	fclose(arq_entrada);
	fclose(arq_saida);
	return 0;

}

