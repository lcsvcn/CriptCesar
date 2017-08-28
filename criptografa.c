#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LOG 1

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
    int num_palavras;

	
	if(argc < 3) {
    	printf("./crypt <nome_arquivo_entrada> <key>\n");
    	return 1;
    }

    arq_entrada = fopen(argv[1], "r");

    // se deu erro ao criar o arquivo
	if (arq_entrada == NULL) {
	    printf("Nao existe arquivo que foi pedido\n");
	    return 1;
	} 

	arq_saida = fopen("mensage.csr", "w+");

	// se deu erro ao criar o arquivo
	if (arq_saida == NULL) {
	    printf("Nao existe arquivo que foi pedido\n");
	    return 1;
	}
	

	chave = atoi(argv[2]);

	// percorre para saber quantas palavras vai ter
	for(i = 0; !feof(arq_entrada); i++) {
		if(fscanf(arq_entrada, "%[a-zA-Z'1-9]", str) == EOF) {
			break;
		}

    	if(fscanf(arq_entrada, "%[^a-zA-Z'1-9]", lixo) == EOF) {
    		break;
		}
  	}
  	num_palavras = i;
  	
  	if(LOG) printf("%d\n", num_palavras);

	struct palavras PAL[num_palavras];

	rewind(arq_entrada);

  	for(i = 0; i < num_palavras; i++) {
  	
		for(j=0; ;j++) {
			if(fscanf(arq_entrada, "%[a-zA-Z]", str) == EOF) {
				break;
			}
			strcpy(PAL[j].str, str);

    		if(fscanf(arq_entrada, "%[^a-zA-Z]", lixo) == EOF) {
    			break;
    		}

			strcpy(PAL[j].lixo, lixo);
    		
		}
	}

	if(LOG) {
		for(i = 0; i < num_palavras; i++) {
  			printf("(%s)\n", PAL[i].str);
  		}
  		printf("\n");
  		for(i = 0; i < num_palavras; i++) {
  			printf("(%s)\n", PAL[i].lixo);
  		}
  	}

  	for(i = 0; i < num_palavras; i++) {
  		fprintf(arq_saida, "#");
	  	for(j=0; j<strlen(PAL[i].str); j++) {
			int enc = (int) PAL[i].str[j] + chave;
			fprintf(arq_saida, "%c", (char) enc);
		}
		fprintf(arq_saida, "#");
		
		fprintf(arq_saida, "%s", PAL[i].lixo);
	
	}

	/*printf("\n\nFrase encriptada com sucesso!\n\n");
	printf("Encriptacao:  ");

	for(i=0;i<strlen(frase);i++) {
		int enc=(int)frase[i]+chave;
		printf("%c",(char)enc);
    }*/







	fclose(arq_entrada);
	fclose(arq_saida);
	return 0;

}
