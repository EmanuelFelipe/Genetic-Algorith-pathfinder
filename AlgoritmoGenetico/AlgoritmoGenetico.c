#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2

    int tamGenes = 2;
    int tamPop = 50;
    int numGeracoes = 100;
    float probMut = 0.1;
    float probCruz = 0.7;

    int coluna_atual = 1,
    linha_atual = 1,
    coluna_atual2 = 1,
    linha_atual2 = 1;

    int key,
    passos;

typedef struct individuo{
    int x;
    int y;
    int fitness;
}individuo;

int mapa[20][20];

void gera_mapa() {
    int m, n;
    srand(time(NULL));

    for (m = 0; m < 20;m++)
    {
        for (n = 0;n<20;n++)
        {
            if (mapa[m][n] == 0)
            {
                mapa[m][n] = rand() % 3;

                if (mapa[m][n] == 2)
                {
                    mapa[m][n] = 0;
                }
            }
        }
    }
    n = rand() % 20;
    m = rand() % 20;
    mapa[m][n] = 4;
}

int desenhar_mapa(int mapa[20][20]) {
    int linha,coluna;
	int coluna_atual = 1, linha_atual = 1, coluna_atual2 = 1, linha_atual2 = 1;

    for (linha=0;linha<20;linha++) {
        for (coluna=0;coluna<20;coluna++) {

            if ((linha == linha_atual) && (coluna == coluna_atual)) {
                printf("*");
                continue;
            }
            if (mapa[linha][coluna] == CHAO)
                printf(" ");
            if (mapa[linha][coluna] == PAREDE)
                printf("-");
            if (mapa[linha][coluna] == SAIDA)
                printf("#");

        }
        printf("\n");
    }
    return 1;
}
void iniciaPopulacao(){
    
}

int paraBaixo(){
    linha_atual = 1 + linha_atual;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        linha_atual = linha_atual - 1;
    }
}

int paraCima(){
    linha_atual = linha_atual - 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        linha_atual = linha_atual + 1;
    }
}

int paraDireita(){
    coluna_atual = coluna_atual + 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        coluna_atual = coluna_atual - 1;
    }
}

int paraEsquerda(){
    coluna_atual = coluna_atual - 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        coluna_atual = coluna_atual + 1;
    }
}

int main(){

	gera_mapa();
    desenhar_mapa(mapa);

    return 0;
}