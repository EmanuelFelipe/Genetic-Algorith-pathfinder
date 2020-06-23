#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define tampop 50
#define numGeracoes 5000

typedef struct individuo
{
    int genes[500];
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
void paraBaixo(int *parede, int *saida);
void crossOver();
void paraCima(int *parede, int *saida);
void paraDireita(int *parede, int *saida);
void paraEsquerda(int *parede, int *saida);
void limpar_labirinto();
void quicksort(individuo *vet, int ini, int final);
int desenhar_mapa();
int iniciaPopulacao(individuo **ind, int *parede, int *saida);
int maiorGene();
int roleta();
int mutacao();
int **alocaMapa(int l, int c);
int fitness(int l, int c);
int ponto(int i);
long int *melhorIndivid(individuo *vet[1000], int choice);

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    for (int j = 0; j < 500; j++)
    {
        indCriado->genes[j] = -1;
    }
    indCriado->geracaoAtual = 0;
    indCriado->fitness = 0;

    return indCriado;
}

void limpar_labirinto(){
    int m, n;
    int linha1, coluna1;

    for (m = 0; m < 20; m++)
    {
        for (n = 0; n < 30; n++)
        {
                mapa[m][n] = 0;
        }
    }
    for (linha1 = 0; linha1 < 20; linha1++)
    {
        for (coluna1 = 0; coluna1 < 30; coluna1++)
        {
            if (mapa[linha1][coluna1] == CHAO)
                printf(" ");
        }
        printf("\n");
    }
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
            mapa[19][n] = 3;
            mapa[m][0] = 1;
            mapa[m][29] = 1;
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

int iniciaPopulacao(individuo **ind, int *parede, int *saida)
{
    srand(time(NULL));
    int aux, somatorio;
    linha_atual = 1;
    coluna_atual = 1;
    *ind = cria_individuo();

    for (i = 0; i < 500; i++)
    {
        individuo *ind_local = *ind;

        ind_local->genes[i] = rand() % 4;
        //printf("crom: %d\n", ind_local->genes[i]);
        percurso(ind_local->genes[i], parede, saida);

        if (*saida == 1)
        {
            break;
        }
    }

    aux = fitness(linha_atual, coluna_atual);

    return aux;
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

void crossOver(individuo **ind, int *parede, int *saida) //esse foi a função, onde os indviduos pegariam genes de individuos(podendo ou nao ser os melhores indviduos)
{
    srand(time(NULL));
    linha_atual = 1;
    coluna_atual = 1;
    individuo *ind_filho = cria_individuo();
    int x = 0;

    for (i = 0; i < 500; i++)
    {
        //individuo *ind_local = *ind;
        x = rand() % 100;
        ind_filho->genes[i] = ind[x]->genes[x];
        printf("\nindividuo %d\n", i);
        //printf("crom: %d\n", ind_filho->genes[i]);
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
    int aleatorio, primeiro = 1, segundo = 2, terceiro = 3, quarto = 4;
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

//long int *melhorIndivid(individuo *vet[1000], int cont)
//{

//     for (int i = 0; i<cont; i++){

//     }

//     return *vet;
// }

void paraBaixo(int *parede, int *saida)
{
    if (mapa[linha_atual + 1][coluna_atual] == PAREDE || mapa[linha_atual + 1][coluna_atual] == TETO)
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
    individuo *newInd[tampop];
    int pergunta, perg;
    int parede = 0;
    int saida = 0;
    int contador = 0;
    int repete = 0;
    int *pontSaida = &saida;
    int *pontParede = &parede;
    int vet[1000];
    int geracao = 0;

    do
    {
        printf("Digite sua opcao\n");
        printf("0 - sair\n");
        printf("1 - gerar labirinto\n");
        printf("2 - começar labirinto\n");
        printf("3 - repetir individuo final\n");
        printf("4 - free individuos\n");
        printf("5 - limpar labirinto\n");
        scanf("%d", &perg);

        switch (perg)
        {
        case 0:
            printf("saindo do programa\n");
            break;

        case 1:
            system("clear");
            gera_mapa();
            desenhar_mapa();
            break;
        case 2:
            system("clear");
            do
            {

                vet[contador] = iniciaPopulacao(&ind, pontParede, pontSaida);
                ind->fitness = vet[contador];
                newInd[contador] = ind;
                printf("indviduo: %d \n", contador + 1);
                printf("Geracao: %d \n", geracao + 1);
                if (saida == 1)
                {
                    break;
                }
                if (contador == tampop)
                {
                    break;
                }
                contador += 1;
                repete = contador;
            } while (saida == 0);

            if (saida == 0)
            {
                do
                {
                    crossOver(&ind, pontParede, pontSaida);
                    printf("indviduo: %d \n", contador);
                    printf("Geracao: %d \n", geracao + 1);
                    if (contador == numGeracoes)
                    {
                        break;
                    }
                    else if (saida == 1)
                    {
                        break;
                    }
                    contador += 1;
                    geracao += 1;
                } while (saida == 0);
            }
            break;

        case 3:
            printf("repetir ultimo?\n");
            scanf("%d", &perg);

            *pontSaida = 0;
            linha_atual = 1;
            coluna_atual = 1;

            if (perg == 1)
            {

                for (int i = 0; i < 500; i++)
                {
                    percurso(ind->genes[i], pontParede, pontSaida);

                    if (saida == 1)
                    {
                        break;
                    }
                }
            }
            break;
        case 4:
            free(ind);
            system("clear");
            break;
        case 5:
            limpar_labirinto();
            system("clear");
            break;
        default:
            printf("Digite uma opção valida\n");
            break;
        }
    } while (perg != 0);

    // if (pergunta == 1)
    // {

    //     do
    //     {

    //         vet[contador] = iniciaPopulacao(&ind, pontParede, pontSaida);
    //         ind->fitness = vet[contador];
    //         newInd[contador] = ind;
    //         printf("indviduo: %d \n", contador + 1);
    //         printf("Geracao: %d \n", geracao);
    //         if (saida == 1)
    //         {
    //             break;
    //         }
    //         if (contador == tampop)
    //         {
    //             break;
    //         }
    //         contador += 1;
    //         repete = contador;

    //     } while (saida == 0);

    //     //tivemos alguns problemas com o crossover dos indiduos,
    //     //onde eles nao recebiam os valores corretos e os individuos nao conseguiam chegar ao objetivo;

    //     //por isso desabilitamos ela para refazer os testes, ao longo do projeto tentamos resolver,
    //     //mas nao conseguimos, e estamos fazendo o possivel para resolver a problematica;

    //     contador = 0;
    //     if (saida == 0)
    //     {

    //         do
    //         {
    //             crossOver(&newInd, pontParede, pontSaida);
    //             printf("indviduo: %d \n", contador);
    //             printf("Geracao: %d \n", geracao);
    //             if (contador == numGeracoes)
    //             {
    //                 break;
    //             }
    //             else if (saida == 1)
    //             {
    //                 break;
    //             }
    //             contador += 1;
    //             geracao += 1;
    //         } while (saida == 0);
    //     }
    // }

    // printf("repetir ultimo?\n");
    // scanf("%d", &perg);

    // *pontSaida = 0;
    // linha_atual = 1;
    // coluna_atual = 1;

    // if (perg == 1)
    // {

    //     for (int i = 0; i < 500; i++)
    //     {
    //         percurso(ind->genes[i], pontParede, pontSaida);

    //         if (saida == 1)
    //         {
    //             break;
    //         }
    //     }
    // }

    // int remove = 0;

    // printf("apagar?1 - sim, 2 - nao\n");
    // scanf("%d", &remove);

    // if (remove == 1)
    // {
    //     free(ind);
    // }

    return 0;
}
