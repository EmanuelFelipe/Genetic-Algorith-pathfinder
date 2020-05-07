#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3

int numGeracoes = 100;
float probMut = 0.1;
float probCruz = 0.7;
int parede = 0;
int saida = 0;
int geracaoAtual = 0;

int i = 0, j = 0, k = 0, l = 0;
int vet[4];

int individ1[80][100],
    individ2[80][100],
    individ3[80][100],
    individ4[80][100];

int coluna_atual = 1,
    linha_atual = 1,
    coluna_anterior = 1,
    linha_anterior = 1;

int key,
    passos;

int mapa[20][50];

void percurso(int x);
void gera_mapa();
int desenhar_mapa();
void iniciaPopulacao();
void crossOver();
void paraBaixo();
void paraCima();
void paraDireita();
void paraEsquerda();

void gera_mapa()
{
    int m, n;
    srand(time(NULL));

    for (m = 0; m < 20; m++)
    {
        for (n = 0; n < 50; n++)
        {
            if (mapa[m][n] == 0)
            {
                mapa[m][n] = rand() % 3;

                mapa[1][1] = 0;
                if (mapa[m][n] == 2)
                {
                    mapa[m][n] = 0;
                }
            }
            mapa[0][n] = 3;
        }
    }
    n = rand() % 50;
    m = rand() % 20;
    mapa[m][n] = 4;
}

int desenhar_mapa()
{
    int linha, coluna;
    for (linha = 0; linha < 20; linha++)
    {
        for (coluna = 0; coluna < 50; coluna++)
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
            if (mapa[linha][coluna] == TETO)
                printf("-");
        }
        printf("\n");
    }
    return 1;
}
void iniciaPopulacao()
{
    srand(time(NULL));
    do
    {
        individ1[i][geracaoAtual] = rand() % 3;
        printf("\nindividuo 1\n");
        printf("crom: %d", individ1[i][geracaoAtual]);
        percurso(individ1[i][geracaoAtual]);
        i++;
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    } while (i < 80);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;
    do
    {
        individ2[j][geracaoAtual] = rand() % 3;
        printf("\nindividuo 2\n");
        printf("crom: %d", individ2[j][geracaoAtual]);
        percurso(individ2[j][geracaoAtual]);
        j++;

        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    } while (j < 80);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;
    do
    {
        individ3[k][geracaoAtual] = rand() % 3;
        printf("\nindividuo 3\n");
        printf("crom: %d", individ3[k][geracaoAtual]);
        percurso(individ3[k][geracaoAtual]);
        k++;

        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    } while (k < 80);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;
    do
    {
        individ4[l][geracaoAtual] = rand() % 3;
        printf("\nindividuo 4\n");
        printf("crom: %d", individ4[l][geracaoAtual]);
        percurso(individ4[l][geracaoAtual]);
        l++;

        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    } while (l < 80);
    //desenhar_mapa();
}

void percurso(int opcao)
{
    switch (opcao)
    {
    case 0:
        paraBaixo();
        printf("\n");
        desenhar_mapa();
        break;
    case 1:
        paraCima();
        printf("\n");
        desenhar_mapa();
        break;
    case 2:
        paraDireita();
        printf("\n");
        desenhar_mapa();
        break;
    case 3:
        paraEsquerda();
        printf("\n");
        desenhar_mapa();
        break;

    default:
        printf("\nopção invalida");
        break;
    }
}

void crossOver()
{
    srand(time(NULL));
    int x, escolha, aux;
    geracaoAtual++;
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    int a = 0;
    do
    {
        if (a == 0)
        {
            escolha = rand() % 3;
            aux = escolha;
            if (escolha == 0)
            {
                x = rand() % i;
                individ1[a][geracaoAtual] = individ1[x][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                x = rand() % j;
                individ1[a][geracaoAtual] = individ2[x][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                x = rand() % k;
                individ1[a][geracaoAtual] = individ3[x][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                x = rand() % l;
                individ1[a][geracaoAtual] = individ4[x][geracaoAtual - 1];
            }
        }
        else
        {
            if (escolha == aux)
            {
                escolha = rand() % 3;
            }
            if (escolha == 0)
            {
                individ1[a][geracaoAtual] = individ1[a][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                individ1[a][geracaoAtual] = individ2[a][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                individ1[a][geracaoAtual] = individ3[a][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                individ1[a][geracaoAtual] = individ4[a][geracaoAtual - 1];
            }
        }
        printf("\nindividuo 1 ger 2\n");
        printf("escolha %d\n", escolha);
        printf("x %d\n", x);
        printf("a %d\n", a);
        percurso(individ1[a][geracaoAtual]);
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
        a++;
    } while (a < 80);
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    for (int b = 0; b < i; b++)
    {
        if (b == 0)
        {
            x = rand() % i;
            escolha = rand() % 3;
            aux = escolha;
            if (escolha == 0)
            {
                x = rand() % i;
                individ2[b][geracaoAtual] = individ1[x][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                x = rand() % j;
                individ2[b][geracaoAtual] = individ2[x][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                x = rand() % k;
                individ2[b][geracaoAtual] = individ3[x][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                x = rand() % l;
                individ2[b][geracaoAtual] = individ4[x][geracaoAtual - 1];
            }
        }
        else
        {
            do
            {
                escolha = rand() % 3;
            } while (escolha == aux);
            if (escolha == 0)
            {
                individ2[b][geracaoAtual] = individ1[b][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                individ2[b][geracaoAtual] = individ2[b][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                individ2[b][geracaoAtual] = individ3[b][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                individ2[b][geracaoAtual] = individ4[b][geracaoAtual - 1];
            }
        }
        printf("\nindividuo 2 ger 2\n");
        printf("escolha %d\n", escolha);
        printf("x %d\n", x);
        printf("b %d\n", b);
        percurso(individ1[b][geracaoAtual]);
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    }
    printf("teste: %d", individ1[0][geracaoAtual]);
    int mostra = 0;
}

void paraBaixo()
{
    linha_atual = 1 + linha_atual;
    passos = passos + 1;

    if (mapa[linha_atual][coluna_atual] == PAREDE || mapa[linha_atual][coluna_atual] == TETO)
    {
        parede = 1;
        linha_atual -= 1;
    }
    else if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        saida = 1;
    }
}

void paraCima()
{
    linha_atual = linha_atual - 1;
    passos = passos + 1;

    if (mapa[linha_atual][coluna_atual] == PAREDE || mapa[linha_atual][coluna_atual] == TETO)
    {
        parede = 1;
        linha_atual = linha_atual + 1;
    }
    else if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        saida = 1;
    }
}

void paraDireita()
{
    coluna_atual = coluna_atual + 1;
    passos = passos + 1;

    if (mapa[linha_atual][coluna_atual] == PAREDE || mapa[linha_atual][coluna_atual] == TETO)
    {
        parede = 1;
        coluna_atual = coluna_atual - 1;
    }
    else if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        saida = 1;
    }
}

void paraEsquerda()
{
    coluna_atual = coluna_atual - 1;
    passos = passos + 1;

    if (mapa[linha_atual][coluna_atual] == PAREDE || mapa[linha_atual][coluna_atual] == TETO)
    {
        parede = 1;
        coluna_atual = coluna_atual + 1;
    }
    else if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        saida = 1;
    }
}

int main()
{
    int pergunta, perg;
    gera_mapa();
    desenhar_mapa();

    printf("começar labirinto?1 - sim, 2 - nao\n");
    scanf("%d", &pergunta);

    if (pergunta == 1)
    {
        iniciaPopulacao();
    }
    else
    {
        printf("ta bom, tchau");
    }

    printf("começar proxima geracao?1 - sim, 2 - nao\n");
    scanf("%d", &pergunta);

    if (pergunta == 1)
    {
        crossOver();
    }
    else
    {
        printf("ta bom, tchau");
    }

    return 0;
}
