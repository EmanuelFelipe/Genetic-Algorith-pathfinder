#include <stdlib.h>
#include <stdio.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2

typedef struct individuo{
    int x;
    int y;
    int fitness;
}individuo;

int mapa[10][20]={
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void gera_mapa() {
    int m, n;

    for (m = 0; m < 10;m++)
    {
        for (n = 0;n<20;n++)
        {
            if (mapa[m][n] == 0)
            {
                mapa[m][n] = rand() % 4;

                if (mapa[m][n] == 2)
                {
                    mapa[m][n] = 0;
                }
            }
        }
    }
    mapa[9][18] = 4;
}

int desenhar_mapa() {
    int linha,coluna;
	int coluna_atual = 1, linha_atual = 1, coluna_atual2 = 1, linha_atual2 = 1;

    for (linha=0;linha<10;linha++) {
        for (coluna=0;coluna<20;coluna++) {

            if ((linha == linha_atual) && (coluna == coluna_atual)) {
                printf("*");
                continue;
            }
            if (mapa[linha][coluna] == CHAO)
                printf(" ");
            if (mapa[linha][coluna] == PAREDE)
                printf("©");
            if (mapa[linha][coluna] == SAIDA)
                printf("#");

        }
        printf("\n");
    }
    return 1;
}

int gerações(individuo vet[], int tamVet){
	
}

int main(){

	void gera_mapa();
	int desenhar_mapa();

    return 0;
}