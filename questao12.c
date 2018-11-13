/*
Como indicado na questão, é desejado que desconsidere o
caracter '/n' na contagem de colunas da matriz.

No entanto, como deve ser feito no momento
de replicar o conteudo do arquivo original
na matriz gerada dinamicamente? Pois, caso
isso também não seja levado em conta, essa
tentativa de réplica falhará, já que
vão faltar caracteres a serem lidos devido
a diferença no número de colunas causada
por essa desconsideração.

Como achei confuso, decidi considerar o caracter '\n'
na contagem de colunas da matriz.

Mas é possível mudar isso facilmente. Para deixar
de acordo com o enunciado, basta retirar o 
operador de pré-incremento da linha 56 sobre
o operando "c".

Espero que na quarta (14/11) possamos conversar
sobre isso. :-)
*/

#include <stdio.h>
#include <stdlib.h>

char **geratriz(int l, int c);

int main(void) {
	
	char **mapa, caracter;
	int l, c, i, j;
	FILE *input = fopen("labirinto.txt", "r");
	
	if (input == NULL) {
		
		printf("Erro ao ler arquivo!\n");
		return (1);
	}
	
	for (c = 0; fgetc(input) != '\n'; c++);
	
	for (l = 1; caracter != EOF;) {
	
		caracter = fgetc(input);
		
		if (caracter == '\n') {
			l++;
		}
	}
	
	rewind(input);
	
	mapa = geratriz(l, ++c);
	
	for (i = 0; i < l; i++) {
		
		for (j = 0; j < c; j++) {
			
			mapa[i][j] = fgetc(input);
			
			printf("%c", mapa[i][j]);
		}
	}
	
	return (0);
}

char **geratriz(int l, int c) {
	
	char **matriz;
	int i;
	
	matriz = (char **)malloc(l * sizeof(char *));
	
	for (i = 0; i < l; i++) {
		matriz[i] = (char *)malloc(c * sizeof(char));
	}
	
	return (matriz);
}






