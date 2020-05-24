#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define numGeracoes 5000

int parede = 0;
int saida = 0;
int geracaoAtual = 0;
int s1, s2, melhor1, melhor2, melhor3, melhor4;

int i = 0, j = 0, k = 0, l = 0;
int vet[4];

int individ1[80][numGeracoes],
    individ2[80][numGeracoes],
    individ3[80][numGeracoes],
    individ4[80][numGeracoes];

int coluna_atual = 1,
    linha_atual = 1,
    linha, coluna;

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
int **alocaMapa(int l, int c);
int fitness(int l, int c);
int melhorIndivid();

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
            mapa[20][n] = 3;
            mapa[m][0] = 1;
            mapa[m][30] = 1;
        }
    }
    s1 = rand() % 30;
    s2 = rand() % 20;
    mapa[s2][s1] = 4;
}

int desenhar_mapa()
{
    int linha1, coluna1;
    for (linha1 = 0; linha1 < 20; linha1++)
    {
        for (coluna1 = 0; coluna1 < 30; coluna1++)
        {

            if ((linha1 == linha_atual) && (coluna1 == coluna_atual))
            {
                printf(".");
                continue;
            }
            if (mapa[linha1][coluna1] == CHAO)
                printf(" ");
            if (mapa[linha1][coluna1] == PAREDE)
                printf("|");
            if (mapa[linha1][coluna1] == SAIDA)
                printf("#");
            if (mapa[linha1][coluna1] == TETO)
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
        individ1[i][geracaoAtual] = rand() % 3 + 1;
        printf("\nindividuo 1\n");
        printf("crom: %d\n", individ1[i][geracaoAtual]);
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
    melhor1 = fitness(linha_atual, coluna_atual);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;
    do
    {
        individ2[j][geracaoAtual] = rand() % 3 + 1;
        printf("\nindividuo 2\n");
        printf("crom: %d\n", individ2[j][geracaoAtual]);
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

    melhor2 = fitness(linha_atual, coluna_atual);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;
    do
    {
        individ3[k][geracaoAtual] = rand() % 3;
        printf("\nindividuo 3\n");
        printf("crom: %d\n", individ3[k][geracaoAtual]);
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

    melhor3 = fitness(linha_atual, coluna_atual);
    coluna_atual = 1;
    linha_atual = 1;
    parede = 0;
    saida = 0;

    do
    {
        individ4[l][geracaoAtual] = rand() % 3;
        printf("\nindividuo 4\n");
        printf("crom: %d\n", individ4[l][geracaoAtual]);
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
    melhor4 = fitness(linha_atual, coluna_atual);
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
    int x, escolha, aux, mutar, jaEscolheu = 0;
    int melhorAux1, melhorAux2, melhorAux3, melhorAux4;
    geracaoAtual++;
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    int a = 0, b = 0, c = 0, d = 0;
    mutar = mutacao();
    for (a = 0; a < 100; a++)
    {
        if (mutar == 1)
        {
            x = rand() % 3;
            individ1[a][geracaoAtual] = x;
        }
        else if (a < roleta() / 2)
        {
            escolha = roleta();
            aux = escolha;
            if (escolha == i)
            {
                individ1[a][geracaoAtual] = individ1[a][geracaoAtual - 1];
            }
            else if (escolha == j)
            {
                individ1[a][geracaoAtual] = individ2[a][geracaoAtual - 1];
            }
            else if (escolha == k)
            {
                individ1[a][geracaoAtual] = individ3[a][geracaoAtual - 1];
            }
            else if (escolha == l)
            {
                individ1[a][geracaoAtual] = individ4[a][geracaoAtual - 1];
            }
        }
        if (escolha == aux && jaEscolheu == 0)
        {
            escolha = roleta();
            jaEscolheu = 1;
        }
        else if (a > roleta() / 2)
        {
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
    }

    melhorAux1 = fitness(linha_atual, coluna_atual);
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    jaEscolheu = 0;
    mutar = mutacao();

    for (b = 0; b < 100; b++)
    {
        escolha = roleta();
        if (mutar == 1)
        {
            x = rand() % 3;
            individ2[b][geracaoAtual] = x;
        }
        else if (b < escolha / 2)
        {
            aux = escolha;
            if (escolha == i)
            {
                individ2[b][geracaoAtual] = individ1[b][geracaoAtual - 1];
            }
            else if (escolha == j)
            {
                individ2[b][geracaoAtual] = individ2[b][geracaoAtual - 1];
            }
            else if (escolha == k)
            {
                individ2[b][geracaoAtual] = individ3[b][geracaoAtual - 1];
            }
            else if (escolha == l)
            {
                individ2[b][geracaoAtual] = individ4[b][geracaoAtual - 1];
            }
        }
        if (escolha == aux && jaEscolheu == 0)
        {
            escolha = roleta();
            jaEscolheu = 1;
        }
        else if (a > escolha / 2)
        {
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
        printf("\nindividuo 2 ger %d\n", geracaoAtual + 1);
        printf("escolha %d\n", escolha);
        printf("x %d\n", x);
        printf("b %d\n", b);
        percurso(individ2[b][geracaoAtual]);
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    }

    melhorAux2 = fitness(linha_atual, coluna_atual);

    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    jaEscolheu = 0;
    mutar = mutacao();

    for (c = 0; c < 100; c++)
    {
        escolha = roleta();
        if (mutar == 1)
        {
            x = rand() % 3;
            individ3[c][geracaoAtual] = x;
        }
        else if (c < escolha / 2)
        {
            aux = escolha;
            if (escolha == i)
            {
                individ3[c][geracaoAtual] = individ1[c][geracaoAtual - 1];
            }
            else if (escolha == j)
            {
                individ3[c][geracaoAtual] = individ2[c][geracaoAtual - 1];
            }
            else if (escolha == k)
            {
                individ3[c][geracaoAtual] = individ3[c][geracaoAtual - 1];
            }
            else if (escolha == l)
            {
                individ3[c][geracaoAtual] = individ4[c][geracaoAtual - 1];
            }
        }
        if (escolha == aux && jaEscolheu == 0)
        {
            escolha = roleta();
            jaEscolheu = 1;
        }
        else if (c > escolha / 2)
        {
            if (escolha == 0)
            {
                individ3[c][geracaoAtual] = individ1[c][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                individ3[c][geracaoAtual] = individ2[c][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                individ3[c][geracaoAtual] = individ3[c][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                individ3[c][geracaoAtual] = individ4[c][geracaoAtual - 1];
            }
        }
        printf("\nindividuo 3 ger %d\n", geracaoAtual + 1);
        printf("escolha %d\n", escolha);
        printf("x %d\n", x);
        printf("b %d\n", c);
        percurso(individ3[c][geracaoAtual]);
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    }

    melhorAux3 = fitness(linha_atual, coluna_atual);

    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    jaEscolheu = 0;
    mutar = mutacao();

    for (d = 0; d < 100; d++)
    {
        escolha = roleta();
        if (mutar == 1)
        {
            x = rand() % 3;
            individ4[d][geracaoAtual] = x;
        }
        else if (d < escolha / 2)
        {
            aux = escolha;
            if (escolha == i)
            {
                individ4[d][geracaoAtual] = individ1[d][geracaoAtual - 1];
            }
            else if (escolha == j)
            {
                individ4[d][geracaoAtual] = individ2[d][geracaoAtual - 1];
            }
            else if (escolha == k)
            {
                individ4[d][geracaoAtual] = individ3[d][geracaoAtual - 1];
            }
            else if (escolha == l)
            {
                individ4[d][geracaoAtual] = individ4[d][geracaoAtual - 1];
            }
        }
        if (escolha == aux && jaEscolheu == 0)
        {
            escolha = roleta();
            jaEscolheu = 1;
        }
        else if (d > escolha / 2)
        {
            if (escolha == 0)
            {
                individ4[d][geracaoAtual] = individ1[d][geracaoAtual - 1];
            }
            else if (escolha == 1)
            {
                individ4[d][geracaoAtual] = individ2[d][geracaoAtual - 1];
            }
            else if (escolha == 2)
            {
                individ4[d][geracaoAtual] = individ3[d][geracaoAtual - 1];
            }
            else if (escolha == 3)
            {
                individ4[d][geracaoAtual] = individ4[d][geracaoAtual - 1];
            }
        }
        printf("\nindividuo 4 ger %d\n", geracaoAtual + 1);
        printf("escolha %d\n", escolha);
        printf("x %d\n", x);
        printf("b %d\n", b);
        percurso(individ4[d][geracaoAtual]);
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    }
    melhorAux4 = fitness(linha_atual, coluna_atual);

    melhor1 = melhorAux1;
    melhor2 = melhorAux2;
    melhor3 = melhorAux3;
    melhor4 = melhorAux4;
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
    int aleatorio, primeiro, segundo, terceiro, quarto;
    srand(time(NULL));

    aleatorio = rand() % 100;
    primeiro = melhorIndivid();
    segundo = melhorIndivid();
    terceiro = melhorIndivid();

    if (segundo == melhor1)
    {
        if (melhor2 < melhor3 && melhor2 < melhor4)
        {
            segundo = melhor2;
        }
        else if (melhor3 < melhor2 && melhor3 < melhor4)
        {
            segundo = melhor3;
        }
        else if (melhor4 < melhor2 && melhor4 < melhor3)
        {
            segundo = melhor4;
        }
    }
    else if (segundo == melhor2)
    {
        if (melhor1 < melhor3 && melhor1 < melhor4)
        {
            segundo = melhor2;
        }
        else if (melhor3 < melhor1 && melhor3 < melhor4)
        {
            segundo = melhor3;
        }
        else if (melhor4 < melhor1 && melhor4 < melhor3)
        {
            segundo = melhor4;
        }
    }

    if (aleatorio >= 60 && aleatorio <= 100)
    {
        return primeiro;
    }
    else if (aleatorio >= 30 && aleatorio <= 59)
    {
        return segundo;
    }
    else if (aleatorio >= 15 && aleatorio <= 29)
    {
        return terceiro;
    }
}

int fitness(int l, int c)
{
    int fit = 0;

    fit = (s2 - l) + (s1 - c);

    return fit;
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

int melhorIndivid()
{
    if (melhor1 < melhor2 && melhor1 < melhor3 && melhor1 < melhor4)
    {
        return i;
    }
    else if (melhor2 < melhor1 && melhor2 < melhor3 && melhor2 < melhor4)
    {
        return j;
    }
    else if (melhor3 < melhor1 && melhor3 < melhor2 && melhor3 < melhor4)
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
        printf("ta bom, tchau\n");
    }

    printf("começar proxima geracao?1 - sim, 2 - nao\n");
    scanf("%d", &pergunta);

    if (pergunta == 1)
    {
        do
        {
            crossOver();

            if (geracaoAtual == numGeracoes)
            {
                break;
            }
            else if (saida == 1)
            {
                break;
            }
        } while (saida == 0);
    }
    else
    {
        printf("ta bom, tchau\n");
    }
    printf("geracao: %d\n", geracaoAtual);

    return 0;
}
