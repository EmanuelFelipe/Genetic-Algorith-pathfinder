#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define numGeracoes 5000

typedef struct individuo
{
    int genes[1000];
    int geracaoAtual;
} individuo;

int parede = 0;
int saida = 0;
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

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    for (int i = 0; i <= 1000; i++)
    {
        for (int j = 0; j <= 80; j++)
        {
            indCriado->genes[j] = -1;
        }
        indCriado->geracaoAtual = 0;
    }
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

void iniciaPopulacao(individuo *ind)
{
    srand(time(NULL));
    long int * vet[5000];
    do
    {
        ind = cria_individuo();
        ind->genes[i] = rand() % 3;
        vet[i] = ind;
        printf("\nindividuo 1\n");
        printf("crom: %d\n", vet[i]);
        percurso(ind->genes[i]);
        i++;
        if (saida == 1)
        {
            break;
        }
        else if (parede == 1)
        {
            break;
        }
    } while (i < 1000);
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
    linha_atual = 1 + linha_atual; //TODO: verificar se nao é maior que o mapa, ou se esta passando algum limite;
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
    individuo *ind;
    long int *vetor_ind[5000];
    int pergunta, perg;
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

            iniciaPopulacao(ind);
            

            if (saida == 1)
            {
                break;
            }
        } while (ind->geracaoAtual != 5000);
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
            if (ind->geracaoAtual == numGeracoes)
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

    int remove = 0;

    printf("apagar?1 - sim, 2 - nao\n");
    scanf("%d", &remove);

    if (remove == 1)
    {
        free(ind);
    }

    return 0;
}
