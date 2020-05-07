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
int parede = 0;
int saida = 0;

int coluna_atual = 1,
    linha_atual = 1,
    coluna_atual2 = 1,
    linha_atual2 = 1;

int key,
    passos;

typedef struct individuo
{
    int x;
    int y;
    int fitness;
} individuo;

int mapa[10][20] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};;

void percurso(int x);
void gera_mapa();
int desenhar_mapa();
void iniciaPopulacao();
void paraBaixo();
void paraCima();
void paraDireita();
void paraEsquerda();

void gera_mapa()
{
    int m, n;
    srand(time(NULL));

    for (m = 0; m < 10; m++)
    {
        for (n = 0; n < 20; n++)
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
    m = rand() % 10;
    mapa[m][n] = 4;
}

int desenhar_mapa()
{
    int linha, coluna;
    for (linha = 0; linha < 10; linha++)
    {
        for (coluna = 0; coluna < 20; coluna++)
        {

            if ((linha == linha_atual) && (coluna == coluna_atual))
            {
                printf(".");
                continue;
            }
            if (mapa[linha][coluna] == CHAO)
                printf(" ");
            if (mapa[linha][coluna] == PAREDE)
                printf("|");
            if (mapa[linha][coluna] == SAIDA)
                printf("#");
        }
        printf("\n");
    }
    return 1;
}
void iniciaPopulacao()
{
    srand(time(NULL));
    int individ[80];
        int i = 0;
        do{
        individ[i] = rand() % 3;
        percurso(individ[i]);
        i++;

        if (saida == 1){
            break;
        }//else if(parede == 1){
        //    break;
        //}
        
        }while(i<80);
        
    
}

void percurso(int x)
{
    int opcao = x;
    switch (opcao)
    {
    case 0:
        paraBaixo();
        system("clear");
        desenhar_mapa();
        break;
    case 1:
        paraCima();
        system("clear");
        desenhar_mapa();
        break;
    case 2:
        paraDireita();
        system("clear");
        desenhar_mapa();
        break;
    case 3:
        paraEsquerda();
        system("clear");
        desenhar_mapa();
        break;

    default:
        printf("\nopção invalida");
        break;
    }
}

void paraBaixo()
{
    linha_atual = 1 + linha_atual;
    passos = passos + 1;
    
    if ((mapa[linha_atual][coluna_atual] == PAREDE)){
        parede = 1;
        linha_atual -= 1;
    }else if(mapa[linha_atual][coluna_atual] == SAIDA){
        saida = 1;
    }
}

void paraCima()
{
    linha_atual = linha_atual - 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        parede = 1;
        linha_atual = linha_atual + 1;
    }else if(mapa[linha_atual][coluna_atual] == SAIDA){
        saida = 1;
    }
}

void paraDireita()
{
    coluna_atual = coluna_atual + 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        parede = 1;
        coluna_atual = coluna_atual - 1;
    }else if(mapa[linha_atual][coluna_atual] == SAIDA){
        saida = 1;
    }
}

void paraEsquerda()
{
    coluna_atual = coluna_atual - 1;
    passos = passos + 1;

    if(mapa[linha_atual][coluna_atual] == PAREDE){
        parede = 1;
        coluna_atual = coluna_atual + 1;
    }else if(mapa[linha_atual][coluna_atual] == SAIDA){
        saida = 1;
    }
}

int main()
{

    gera_mapa();
    desenhar_mapa();
    int pergunta, perg;


    printf("\ncomecar labirinto?");
    scanf("%d", &pergunta);
    if (pergunta == 1)
    {
        iniciaPopulacao();
    }
    else
    {
        printf("ta bom, tchau\n");
        system("exit");
    }

    return 0;
}