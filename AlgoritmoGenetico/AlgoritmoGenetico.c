#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define tampop 1000
#define numGeracoes 5000

typedef struct individuo
{
    long int genes[1000];
    int geracaoAtual;
    int fitness;
} individuo;

int s1, s2, melhor1, melhor2, melhor3, melhor4;

int i = 0, j = 0, k = 0, l = 0;

int coluna_atual = 1,
    linha_atual = 1,
    linha, coluna;

int key,
    passos;

int mapa[20][30];

void percurso(int opcao, int *parede, int *saida);
void gera_mapa();
int desenhar_mapa();
void iniciaPopulacao(individuo **ind, int *parede, int *saida);
void crossOver();
void paraBaixo(int *parede, int *saida);
void paraCima(int *parede, int *saida);
void paraDireita(int *parede, int *saida);
void paraEsquerda(int *parede, int *saida);
int maiorGene();
int roleta();
int mutacao();
int **alocaMapa(int l, int c);
int fitness(int l, int c);
long int * melhorIndivid(long int * vet[1000], int choice);
int ponto(int i);
void quicksort(long int *vet, int ini, int final);

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    for (int j = 0; j < 1000; j++)
    {
        indCriado->genes[j] = -1;
    }
    indCriado->geracaoAtual = 0;
    indCriado->fitness = 0;

    return indCriado;
}

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

void iniciaPopulacao(individuo **ind, int *parede, int *saida)
{
    int aux;
    srand(time(NULL));
    *ind = cria_individuo();
    //individuo *vet = (individuo *)malloc(sizeof(individuo));
    for (i = 0; i < 1000; i++)
    {
        individuo *ind_local = *ind;

        ind_local->genes[i] = rand() % 4;
        //vet[i] = &ind_local;
        printf("crom: %d\n", ind_local->genes[i]);
        percurso(ind_local->genes[i], parede, saida);

        if (*saida == 1)
        {
            break;
        }
        else if (*parede == 1)
        {
            break;
        }
    }
    for (int y = 0; y < i; y++)
    {
        //aux = melhorIndivid(vet[y], y);
    }
    
    linha_atual = 1;
    coluna_atual = 1;
}

void percurso(int opcao, int *parede, int *saida)
{
    switch (opcao)
    {
    case 0:
        paraBaixo(parede, saida);
        system("clear");
        desenhar_mapa();
        break;
    case 1:
        paraCima(parede, saida);
        system("clear");
        desenhar_mapa();
        break;
    case 2:
        paraDireita(parede, saida);
        system("clear");
        desenhar_mapa();
        break;
    case 3:
        paraEsquerda(parede, saida);
        system("clear");
        desenhar_mapa();
        break;

    default:
        printf("\nopção invalida");
        break;
    }
}

void crossOver(individuo **ind, int *parede, int *saida)
{
    srand(time(NULL));
    linha_atual = 1;
    coluna_atual = 1;
    individuo *ind_filho = cria_individuo();
    for (i = 0; i < 1000; i++)
    {

        ind_filho->genes[i] = rand() % 4;
        printf("\nindividuo %d\n", i);
        printf("crom: %d\n", ind_filho->genes[i]);
        percurso(ind_filho->genes[i], parede, saida);

        if (*saida == 1)
        {
            break;
        }
        else if (*parede == 1)
        {
            break;
        }
    }
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

long int * melhorIndivid(long int * vet[1000], int cont)
{
    
    //quicksort(vet, 0, cont - 1);

    return *vet;
}

// void quicksort(long int *vet, int ini, int final)
// {
//     int i, j, meio, aux;

//     i = ini;
//     j = final;
//     meio = vet[(ini + final) / 2];

//     do
//     {
//         while (vet[i] < meio)
//             i++;

//         while (vet[j] > meio)
//             j--;

//         if (i <= j)
//         {
//             aux = vet[i];
//             vet[i] = vet[j];
//             vet[j] = aux;
//             i++;
//             j--;
//         }
//     } while (i <= j);

//     if (ini < j)
//         quicksort(vet, ini, j);

//     if (i < final)
//         quicksort(vet, i, final);
// }

void paraBaixo(int *parede, int *saida)
{
    if (mapa[linha_atual + 1][coluna_atual] == PAREDE)
    {
        *parede = 1;
    }
    else
    {
        linha_atual = 1 + linha_atual;
        passos = passos + 1;
    }
    if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        *saida = 1;
    }
}

void paraCima(int *parede, int *saida)
{
    if (mapa[linha_atual - 1][coluna_atual] == PAREDE || mapa[linha_atual - 1][coluna_atual] == TETO)
    {
        *parede = 1;
    }
    else
    {
        linha_atual = linha_atual - 1;
        passos = passos + 1;
    }
    if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        *saida = 1;
    }
}

void paraDireita(int *parede, int *saida)
{
    if (mapa[linha_atual][coluna_atual + 1] == PAREDE || mapa[linha_atual][coluna_atual + 1] == TETO)
    {
        *parede = 1;
    }
    else
    {
        coluna_atual = coluna_atual + 1;
        passos = passos + 1;
    }
    if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        *saida = 1;
    }
}

void paraEsquerda(int *parede, int *saida)
{
    if (mapa[linha_atual][coluna_atual - 1] == PAREDE || mapa[linha_atual][coluna_atual - 1] == TETO)
    {
        *parede = 1;
    }
    else
    {
        coluna_atual = coluna_atual - 1;
        passos = passos + 1;
    }

    if (mapa[linha_atual][coluna_atual] == SAIDA)
    {
        *saida = 1;
    }
}

int main()
{
    individuo *ind;
    individuo *vetInd[tampop];
    int pergunta, perg;
    int parede = 0;
    int saida = 0;
    int contador = 0;
    int *pontSaida = &saida;
    int *pontParede = &parede;
    long int *vet[1000];
    gera_mapa();
    desenhar_mapa();

    // for (int p = 0; p <= 5000; p++)
    // {
    //     vetor_ind[p] = cria_individuo();
    // }

    printf("começar labirinto?1 - sim, 2 - nao\n");
    scanf("%d", &pergunta);

    if (pergunta == 1)
    {

        do
        {

            iniciaPopulacao(&ind, pontParede, pontSaida);
            vetInd[contador] = ind;
            printf("indviduo: %d \n", contador);
            if (saida == 1)
            {
                break;
            }
            contador += 1;

        } while (contador != tampop);
    }
    else
    {
        printf("ta bom, tchau\n");
    }

    printf("começar proxima geracao?1 - sim, 2 - nao\n");
    scanf("%d", &pergunta);
    contador = 0;

    if (pergunta == 1)
    {
        do
        {
            crossOver(&vetInd[contador], pontSaida, pontSaida);
            if (contador == numGeracoes)
            {
                break;
            }
            else if (saida == 1)
            {
                break;
            }
            contador += 1;
        } while (saida == 0);
    }
    else
    {
        printf("ta bom, tchau\n");
    }

    int remove = 0;

    printf("apagar?1 - sim, 2 - nao\n");
    scanf("%d", &remove);

    if (remove == 1)
    {
        free(ind);
    }

    return 0;
}
