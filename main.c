#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>

#define HEROI 79 //Representa 'O'
#define DESTINO 88 //Representa 'X'
#define INIMIGO 65 //Representa 'A'
#define COLISAO 33 //Representa '!'

struct Ponto {

    int x;
    int y;
};

struct Hero {

    struct Ponto p;
    char *nome;
    int score;
} heroi;

int mover_inimigos(char **m, struct Ponto *n, int qtd_inimigos, int l, int c);
int mover_heroi(char **field, char mov, int l, int c);
struct Ponto *gerar_inimigos(char **matriz, int limite_x, int limite_y, int qtd_inimigos);
void draw_scr(char **matriz, int linhas, int colunas);
char **geratriz(int linhas, int colunas);

int main(void) {
    
    int linhas, colunas, num_inimigos;
    char **matriz, input;
    struct Ponto *n;

    srand(time(0));

    heroi.p.x = heroi.p.y = 0;

    linhas = 10 + rand() % 11;
    colunas = 10 + rand() % 21;
    
    matriz = geratriz(linhas, colunas);
    num_inimigos = linhas * colunas / 12;
    
    n = gerar_inimigos(matriz, linhas, colunas, num_inimigos);
    
    printf("PRESSIONE QUALQUER TECLA PARA INICIAR O JOGO ... ");
    getchar();
    
    do {

        system("clear");
   	    draw_scr(matriz, linhas, colunas);

   	    input = getchar();

   	    if (mover_heroi(matriz, input, linhas, colunas) ||
   	    	mover_inimigos(matriz, n, num_inimigos, linhas, colunas)) {

            matriz[heroi.p.x][heroi.p.y] = (char)COLISAO;
            
            system("clear");
            draw_scr(matriz, linhas, colunas);

            printf("\n(%c) Colisao no ponto (%d;%d)\n", (char)COLISAO, heroi.p.x + 1, heroi.p.y + 1);
            printf("Nao foi dessa vez!\n");

            break;
        }

    } while (heroi.p.x != linhas - 1 || heroi.p.y != colunas - 1);

    if (heroi.p.x == linhas - 1 && heroi.p.y == colunas - 1) {
        
        system("clear");
        draw_scr(matriz, linhas, colunas);
        printf("\nVoce atingiu o ponto de chegada. Parabens!!\n");
    }
    
    getchar();

    return (0);
}

int mover_inimigos(char **m, struct Ponto *n, int qtd_inimigos, int l, int c) {

    int i, direcao, sentido;

    for (i = 0; i < qtd_inimigos; i++) {
    
    	direcao = rand() % 2;
    	sentido = rand() % 2;

        if (direcao == 0) {
            
            if (sentido == 0) {

                if (n[i].x < l - 1 && m[n[i].x + 1][n[i].y] != (char)INIMIGO &&
                    !(n[i].x >= l - 3 && n[i].y == c - 1)) {
                    
                    if (n[i].x + 1 == heroi.p.x && n[i].y == heroi.p.y) {

                        m[n[i].x][n[i].y] = '.';
                        return (1);
                    }

                    m[n[i].x][n[i].y] = '.';
                    m[++n[i].x][n[i].y] = (char)INIMIGO;
                }

            } else {

                if (n[i].x > 0 && m[n[i].x - 1][n[i].y] != (char)INIMIGO) {

                    if (n[i].x - 1 == heroi.p.x && n[i].y == heroi.p.y) {

                        m[n[i].x][n[i].y] = '.';
                        return (1);
                    }

                    m[n[i].x][n[i].y] = '.';
                    m[--n[i].x][n[i].y] = (char)INIMIGO;
                }
            }
            
        } else {
            
            if (sentido == 0) {

                if (n[i].y < c - 1 && m[n[i].x][n[i].y + 1] != (char)INIMIGO &&
                    !(n[i].x == l - 1 && n[i].y >= c - 3)) {

                    if (n[i].x == heroi.p.x && n[i].y + 1 == heroi.p.y) {

                        m[n[i].x][n[i].y] = '.';
                        return (1);
                    }

                    m[n[i].x][n[i].y] = '.';
                    m[n[i].x][++n[i].y] = (char)INIMIGO;
                }

            } else {

                if (n[i].y > 0 && m[n[i].x][n[i].y - 1] != (char)INIMIGO) {

                    if (n[i].x == heroi.p.x && n[i].y - 1 == heroi.p.y) {

                        m[n[i].x][n[i].y] = '.';
                        return (1);
                    }

                    m[n[i].x][n[i].y] = '.';
                    m[n[i].x][--n[i].y] = (char)INIMIGO;
                }
            }
        }
    }

    return (0);
}

int mover_heroi(char **field, char mov, int l, int c) {

	switch(mov)
	{
	    case '8':

		if (heroi.p.x > 0) {

                	if (field[heroi.p.x - 1][heroi.p.y] == (char)INIMIGO) {
                    
                		field[heroi.p.x--][heroi.p.y] = '.';
                		return (1);
                	}

                	field[heroi.p.x][heroi.p.y] = '.';
                	field[--heroi.p.x][heroi.p.y] = (char)HEROI;
		}

		break;

		case '2':

		if (heroi.p.x < l - 1) {

			if (field[heroi.p.x + 1][heroi.p.y] == (char)INIMIGO) {

			    field[heroi.p.x++][heroi.p.y] = '.';
			    return (1);
			}

			field[heroi.p.x][heroi.p.y] = '.';
			field[++heroi.p.x][heroi.p.y] = (char)HEROI;
		}

		break;

		case '4':

		if (heroi.p.y > 0) {

			if (field[heroi.p.x][heroi.p.y - 1] == (char)INIMIGO) {

		    		field[heroi.p.x][heroi.p.y--] = '.';
		    		return (1);
			}

			field[heroi.p.x][heroi.p.y] = '.';
			field[heroi.p.x][--heroi.p.y] = (char)HEROI;
		}

		break;

		case '6':

		if (heroi.p.y < c - 1) {

			if (field[heroi.p.x][heroi.p.y + 1] == (char)INIMIGO) {

			    field[heroi.p.x][heroi.p.y++] = '.';
			    return (1);
			}

			field[heroi.p.x][heroi.p.y] = '.';
			field[heroi.p.x][++heroi.p.y] = (char)HEROI;
		}
	}

    return (0);
}

struct Ponto *gerar_inimigos(char **matriz, int limite_x, int limite_y, int qtd_inimigos) {
    
    int i, j;
    struct Ponto *enemy = (struct Ponto*) malloc(qtd_inimigos * sizeof(struct Ponto));

    do {

        (*enemy).x = rand() % limite_x;
        (*enemy).y = rand() % limite_y;

    } while ((enemy[0].x < 3 && enemy[0].y < 3) ||
        (enemy[0].x > limite_x - 3 && enemy[0].y > limite_y - 3));

    for (i = 1; i < qtd_inimigos; i++) {
        
        do {

		(*(enemy + i)).x = rand() % limite_x;
        	(*(enemy + i)).y = rand() % limite_y;

        } while ((enemy[i].x < 3 && enemy[i].y < 3) ||
            (enemy[i].x > limite_x - 3 && enemy[i].y > limite_y - 3));
        
        j = 0;
        do {
            
            if (enemy[i].x == enemy[j].x && enemy[i].y == enemy[j].y) {

                i--;
                break;
            }

        } while (++j < i);
        
        matriz[enemy[i].x][enemy[i].y] = (char)INIMIGO;
    }

    return (enemy);
}

void draw_scr(char **matriz, int linhas, int colunas) {

    int i, j;

    char msg[7][30] = {
        {"Va ate o ponto de chegada\0"},
        {"\0"},
        {"Controles:\0"},
        {"2. Mover para baixo\0"},
        {"4. Mover para esquerda\0"},
        {"6. Mover para direita\0"},
        {"8. Mover para cima\0"}
    };

    for (i = 0; i < 2 * colunas + 3; i++) {
        printf("%c", (char)220);
    }

    printf("\n");

    for (i = 0; i < 7; i++) {

        printf("%c ", (char)219);

        for (j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }

        printf("%c\t\t%s\n", (char)219, msg[i]);
    }

    for (; i < linhas; i++) {

        printf("%c ", (char)219);

        for (j = 0; j < colunas; j++) {

            printf("%c ", matriz[i][j]);
        }

        printf("%c\n", (char)219);
    }

    for (i = 0; i < 2 * colunas + 3; i++) {
        printf("%c", (char)223);
    }

    printf("\n");
}

char **geratriz(int linhas, int colunas) {

    long i, j;
    char **matriz = (char **) malloc(linhas * sizeof(char*));

    for (i = 0; i < linhas; i++) {
        *(matriz + i) = (char *) malloc(colunas * sizeof(char));
    }

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            *(*(matriz + i) + j) = '.';
        }
    }

    *(*(matriz)) = (char)HEROI;
    *(*(matriz + linhas - 1) + colunas - 1) = (char)DESTINO;

    return (matriz);
}

