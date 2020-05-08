#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define numGeracoes 1000

float probMut = 0.1;
float probCruz = 0.7;
int parede = 0;
int saida = 0;
int geracaoAtual = 0;

int i = 0, j = 0, k = 0, l = 0;
int vet[4];

int individ1[80][numGeracoes],
    individ2[80][numGeracoes],
    individ3[80][numGeracoes],
    individ4[80][numGeracoes];

int coluna_atual = 1,
    linha_atual = 1,
    coluna_anterior = 1,
    linha_anterior = 1;

int key,
    passos;

int mapa[20][30];

void percurso(int x);
void gera_mapa();
int desenhar_mapa();
void iniciaPopulacao();
void crossOver();
void paraBaixo();
void paraCima();
void paraDireita();
void paraEsquerda();
int maiorGene();
int roleta();
int mutacao();

void gera_mapa()
{
    int m, n;
    srand(time(NULL));

    for (m = 0; m < 20; m++)
    {
        for (n = 0; n < 30; n++)
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
    n = rand() % 30;
    m = rand() % 20;
    mapa[m][n] = 4;
}

int desenhar_mapa()
{
    int linha, coluna;
    for (linha = 0; linha < 20; linha++)
    {
        for (coluna = 0; coluna < 30; coluna++)
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
        individ2[j][geracaoAtual] = rand() % 4;
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
        individ3[k][geracaoAtual] = rand() % 4;
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
        individ4[l][geracaoAtual] = rand() % 4;
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

void crossOver()
{
    srand(time(NULL));
    int x, escolha, aux, mutar;
    geracaoAtual++;
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    int a = 0, b = 0;
    mutar = mutacao();

    if (mutar == 1)
    {
        do
        {
            individ1[a][geracaoAtual] = rand() % 4;
            printf("\nindividuo 1 ger %d\n", geracaoAtual + 1);
            printf("crom: %d", individ1[i][geracaoAtual]);
            percurso(individ1[i][geracaoAtual]);
            a++;
            if (saida == 1)
            {
                break;
            }
            else if (parede == 1)
            {
                break;
            }
        } while (a < 80);
    }
    else
    {
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
            printf("\nindividuo 1 ger %d\n", geracaoAtual + 1);
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
    }

    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    mutar = mutacao();

    if (mutar == 1)
    {
        do
        {
            individ2[b][geracaoAtual] = rand() % 4;
            printf("\nindividuo 2\n");
            printf("crom: %d", individ2[b][geracaoAtual]);
            percurso(individ2[b][geracaoAtual]);
            b++;

            if (saida == 1)
            {
                break;
            }
            else if (parede == 1)
            {
                break;
            }
        } while (b < 80);
    }

    else
    {
        for (b = 0; b < i; b++)
        {
            if (b == 0)
            {
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
                if (maiorGene() == i)
                {
                    individ2[b][geracaoAtual] = individ1[b][geracaoAtual - 1];
                }
                else if (maiorGene() == j)
                {
                    individ2[b][geracaoAtual] = individ2[b][geracaoAtual - 1];
                }
                else if (maiorGene() == k)
                {
                    individ2[b][geracaoAtual] = individ3[b][geracaoAtual - 1];
                }
                else if (maiorGene() == l)
                {
                    individ2[b][geracaoAtual] = individ4[b][geracaoAtual - 1];
                }
            }
            printf("\nindividuo 2 ger %d\n", geracaoAtual + 1);
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
    }
    printf("teste: %d", individ1[0][geracaoAtual]);
    int mostra = 0;
}

int mutacao()
{
    srand(time(NULL));
    int aleatorio, mutar;
    aleatorio = rand() % 10;

    if (aleatorio >= 3 && aleatorio <= 10)
    {
        return mutar = 0;
    }
    else
    {
        return mutar = 1;
    }
}

int roleta()
{
    int aleatorio, gene;
    srand(time(NULL));

    aleatorio = rand() % 100;
    gene = maiorGene();

    if (aleatorio >= 60 && aleatorio <= 100)
    {
        return gene;
    } //else if(aleatorio >= 30 && aleatorio <= 59){
    //     return
    // }
}

int maiorGene()
{
    if (i > j && i > k && i > l)
    {
        return i;
    }
    else if (j > i && j > k && j > l)
    {
        return j;
    }
    else if (k > i && k > j && k > l)
    {
        return k;
    }
    else
    {
        return l;
    }
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
        do
        {
            crossOver();
            
            if(geracaoAtual == numGeracoes){
                break;
            }else if(saida == 1){
                break;
            }
        } while (saida == 0);
    }
    else
    {
        printf("ta bom, tchau");
    }

    return 0;
}
