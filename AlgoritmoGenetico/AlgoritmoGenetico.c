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
int melhorIndivid(int choice);
int ponto(int i);

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
        individ1[i][geracaoAtual] = rand() % 3;
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
        individ2[j][geracaoAtual] = rand() % 3;
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
    int x, escolha, aux, mutar, xMan, jaEscolheu = 0, DP;
    int melhorAux1, melhorAux2, melhorAux3, melhorAux4;
    int a = 0, b = 0, c = 0, d = 0;

    geracaoAtual++;
    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;

    mutar = mutacao();
    escolha = roleta();
    DP = ponto(escolha);

    for (a = 0; a < DP; a++)
    {

        if (escolha == i)
        {
            individ2[a][geracaoAtual] = individ1[a][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[a][geracaoAtual] = individ2[a][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[a][geracaoAtual] = individ3[a][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[a][geracaoAtual] = individ4[a][geracaoAtual - 1];
        }

        if (mutar == 1)
        {
            x = rand() % 3;
            xMan = rand() % maiorGene();
            individ1[xMan][geracaoAtual] = x;
        }
    }
    aux = escolha;

    if (escolha == aux)
    {
        escolha = roleta();
    }

    for (a = DP; a < aux; a++)
    {

        if (escolha == i)
        {
            individ2[a][geracaoAtual] = individ1[a][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[a][geracaoAtual] = individ2[a][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[a][geracaoAtual] = individ3[a][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[a][geracaoAtual] = individ4[a][geracaoAtual - 1];
        }
    }

    for (a = 0; a < aux; a++)
    {

        printf("\nindividuo 1 ger %d\n", geracaoAtual + 1);
        printf("distancia %d\n", escolha);
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
    escolha = roleta();
    DP = ponto(escolha);

    for (b = 0; b < DP; b++)
    {

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

        if (mutar == 1)
        {
            x = rand() % 3;
            xMan = rand() % maiorGene();
            individ1[xMan][geracaoAtual] = x;
        }
    }
    aux = escolha;

    if (escolha == aux)
    {
        escolha = roleta();
    }

    for (b = DP; b < aux; b++)
    {

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

    for (b = 0; b < aux; b++)
    {

        printf("\nindividuo 2 ger %d\n", geracaoAtual + 1);
        printf("distancia %d\n", escolha);
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

    melhorAux2 = fitness(linha_atual, coluna_atual);

    parede = 0;
    saida = 0;
    coluna_atual = 1;
    linha_atual = 1;
    jaEscolheu = 0;
    mutar = mutacao();
    escolha = roleta();
    DP = ponto(escolha);

    for (c = 0; c < DP; c++)
    {

        if (escolha == i)
        {
            individ2[c][geracaoAtual] = individ1[c][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[c][geracaoAtual] = individ2[c][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[c][geracaoAtual] = individ3[c][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[c][geracaoAtual] = individ4[c][geracaoAtual - 1];
        }

        if (mutar == 1)
        {
            x = rand() % 3;
            xMan = rand() % maiorGene();
            individ1[xMan][geracaoAtual] = x;
        }
    }
    aux = escolha;

    if (escolha == aux)
    {
        escolha = roleta();
    }

    for (c = DP; c < aux; c++)
    {

        if (escolha == i)
        {
            individ2[c][geracaoAtual] = individ1[c][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[c][geracaoAtual] = individ2[c][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[c][geracaoAtual] = individ3[c][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[c][geracaoAtual] = individ4[c][geracaoAtual - 1];
        }
    }

    for (c = 0; c < aux; c++)
    {

        printf("\nindividuo 3 ger %d\n", geracaoAtual + 1);
        printf("distancia %d\n", escolha);
        printf("c %d\n", c);
        percurso(individ1[c][geracaoAtual]);
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

    for (d = 0; d < DP; d++)
    {

        if (escolha == i)
        {
            individ2[d][geracaoAtual] = individ1[d][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[d][geracaoAtual] = individ2[d][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[d][geracaoAtual] = individ3[d][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[d][geracaoAtual] = individ4[d][geracaoAtual - 1];
        }

        if (mutar == 1)
        {
            x = rand() % 3;
            xMan = rand() % maiorGene();
            individ1[xMan][geracaoAtual] = x;
        }
    }
    aux = escolha;

    if (escolha == aux)
    {
        escolha = roleta();
    }

    for (d = DP; d < aux; d++)
    {

        if (escolha == i)
        {
            individ2[d][geracaoAtual] = individ1[d][geracaoAtual - 1];
        }
        else if (escolha == j)
        {
            individ2[d][geracaoAtual] = individ2[d][geracaoAtual - 1];
        }
        else if (escolha == k)
        {
            individ2[d][geracaoAtual] = individ3[d][geracaoAtual - 1];
        }
        else if (escolha == l)
        {
            individ2[d][geracaoAtual] = individ4[d][geracaoAtual - 1];
        }
    }

    for (d = 0; d < aux; d++)
    {

        printf("\nindividuo 4 ger %d\n", geracaoAtual + 1);
        printf("distancia %d\n", escolha);
        printf("d %d\n", d);
        percurso(individ1[d][geracaoAtual]);
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

int ponto(int i)
{
    //escolhe um ponto aleatorio de um indviduo para "transferir" seus genes para o filho
    srand(time(NULL));

    int aleatorio;

    aleatorio = rand() % i;
    return aleatorio;
}

int roleta()
{
    // escolhe aleatoriamente um indviduo, entre 1º, 2º, 3º e 4º;
    int aleatorio, primeiro, segundo, terceiro, quarto;
    srand(time(NULL));

    aleatorio = rand() % 10;
    primeiro = melhorIndivid(1);
    segundo = melhorIndivid(2);
    terceiro = melhorIndivid(3);
    quarto = melhorIndivid(4);

    aleatorio = aleatorio + 1;

    if (aleatorio >= 7 && aleatorio <= 11)
    {
        return primeiro;
    }
    else if (aleatorio >= 4 && aleatorio < 7)
    {
        return segundo;
    }
    else if (aleatorio >= 2 && aleatorio < 4)
    {
        return terceiro;
    }
    else if (aleatorio >= 1 && aleatorio < 2)
    {
        return quarto;
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

int melhorIndivid(int choice)
{
    int vet[4] = {melhor1, melhor2, melhor3, melhor4};
    int aux, def;
    for (int i = 1; i < 4; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            if (vet[i] > vet[i + 1])
            {
                aux = vet[i + 1];
                vet[i + 1] = vet[i];
                vet[i] = aux;
            }
        }
    }

    if (choice == 1)
    {
        return vet[0];
    }
    else if (choice == 2)
    {
        return vet[1];
    }
    else if (choice == 3)
    {
        return vet[2];
    }
    else if (choice == 4)
    {
        return vet[3];
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

            if (i == 1 && j == 1 && k == 1 && l == 1)
            {
                iniciaPopulacao();
            }

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
