#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define tampop 50
#define numGeracoes 5000

typedef struct individuo
{
    int genes[50];
    float fitness;
    int ordem;
    int posicaoFinal[2];
} individuo;

typedef struct populacao
{
    int geracao;
    individuo *inds[50];
} populacao;

int s1, s2, melhor1, melhor2, melhor3, melhor4;

int linha, coluna;

int mapa[20][30];

individuo *crossOver(individuo **ind, int *parede, int *saida);
individuo *iniciaPopulacao(int *parede, int *saida);
void percurso(individuo *ind);
void gera_mapa();
void quicksort(individuo *vet[1000], int ini, int final);
void limpar_labirinto();
void movimenta(int movimento, int *linha, int *coluna);
int paraBaixo(int *parede, int *saida);
int paraCima(int *parede, int *saida);
int paraDireita(int *parede, int *saida);
int paraEsquerda(int *parede, int *saida);
int desenhar_mapa();
int maiorGene();
int roleta();
int mutacao();
int **alocaMapa(int l, int c);
float fitness(int l, int c);
int ponto(int i);

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    for (int j = 0; j < 50; j++)
    {
        indCriado->genes[j] = -1;
    }
    indCriado->fitness = 0;
    indCriado->ordem = 0;
    indCriado->posicaoFinal[0] = 1;
    indCriado->posicaoFinal[1] = 1;

    return indCriado;
}

void limpar_labirinto()
{
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

int desenhar_mapa(int linha_atual, int coluna_atual)
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

individuo *iniciaPopulacao(int *parede, int *saida)
{
    srand(time(NULL));
    int aux, somatorio;
    int linha_atual = 1;
    int coluna_atual = 1;
    individuo *ind_local = cria_individuo();

    for (int i = 0; i < 50; i++)
    {

        ind_local->genes[i] = rand() % 4;
        //printf("crom: %d\n", ind_local->genes[i]);
        // percurso(ind_local->genes[i], parede, saida);

        movimenta(ind_local->genes[i], &linha_atual, &coluna_atual);

        // switch (ind_local->genes[i])
        // {
        // case 0:
        //     linha_atual += paraBaixo(linha_atual, coluna_atual);
        //     break;
        // case 1:
        //     linha_atual -= paraCima(linha_atual, coluna_atual);
        //     break;
        // case 2:
        //     coluna_atual += paraDireita(linha_atual, coluna_atual);
        //     break;
        // case 3:
        //     coluna_atual -= paraEsquerda(linha_atual, coluna_atual);
        //     break;
        // }
    }
    
    ind_local->fitness = fitness(linha_atual, coluna_atual);
    return ind_local;
}

void movimenta(int movimento, int *linha, int *coluna)
{
    int linhaMovimento = *linha;
    int colunaMovimento = *coluna;
    int posicao;

    switch (movimento)
    {
    case 0:
        linhaMovimento += 1;
        break;
    case 1:
        linhaMovimento -= 1;
        break;
    case 2:
        colunaMovimento += 1;
        break;
    case 3:
        colunaMovimento -= 1;
        break;
    }

    posicao = mapa[linhaMovimento][colunaMovimento];

    if (posicao != PAREDE && posicao != TETO)
    {
        *linha = linhaMovimento;
        *coluna = colunaMovimento;
    }
}

void percurso(individuo *ind)
{
    int linha_atual = 1;
    int coluna_atual = 1;
    int i;

    for (i = 0; i < 50; i++)
    {
        system("clear");
        desenhar_mapa(linha_atual, coluna_atual);
        movimenta(ind->genes[i], &linha_atual, &coluna_atual);
    }
}

individuo *crossOver(individuo **ind, int *parede, int *saida) //esse foi a função, onde os indviduos pegariam genes de individuos(podendo ou nao ser os melhores indviduos)
{
    srand(time(NULL));
    individuo *ind_filho = cria_individuo();
    int linha_atual = 1;
    int coluna_atual = 1;
    int x, y, z, mutar = 0;
    x = ponto(50);
    y = roleta();
    z = roleta();
    mutar = mutacao();

    for (int i = 0; i < 50; i++)
    {
        if (i <= x)
        {
            ind_filho->genes[i] = ind[y]->genes[i];
        }
        if (i > x)
        {
            ind_filho->genes[i] = ind[z]->genes[i];
        }

        movimenta(ind_filho->genes[i], &linha_atual, &coluna_atual);

        //percurso(ind_filho->genes[i], parede, saida);

        // if (*saida == 1)
        // {
        //     break;
        // }
        // switch (ind_filho->genes[i])
        // {
        // case 0:
        //     ind_filho->posicaoFinal[1] += paraBaixo(&linha_atual, &coluna_atual);
        //     break;
        // case 1:
        //     ind_filho->posicaoFinal[1] -= paraCima(&linha_atual, &coluna_atual);
        //     break;
        // case 2:
        //     ind_filho->posicaoFinal[0] += paraDireita(&linha_atual, &coluna_atual);
        //     break;
        // case 3:
        //     ind_filho->posicaoFinal[0] -= paraEsquerda(&linha_atual, &coluna_atual);
        //     break;
        // }
    }
    if (mutar == 1)
    {
        ind_filho->genes[ponto(50)] = rand() % 4;
    }
    ind_filho->fitness = fitness(linha_atual, coluna_atual);

    return ind_filho;
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
    srand(time(NULL));
    // escolhe aleatoriamente um indviduo, entre 1º, 2º, 3º e 4º;
    int aleatorio, primeiro = rand() % 5, segundo = (rand() % 5) + 5;

    aleatorio = rand() % 10;

    aleatorio = aleatorio + 1;

    if (aleatorio >= 4 && aleatorio <= 11)
    {
        return primeiro;
    }
    else if (aleatorio >= 1 && aleatorio <= 3)
    {
        return segundo;
    }
}

float fitness(int l, int c)
{

    return sqrt(pow(s2 - l, 2) + pow(s1 - c, 2));
}

// int maiorGene()
// {
//     if (i > j && i > k && i > l)
//     {
//         return i;
//     }
//     else if (j > i && j > k && j > l)
//     {
//         return j;
//     }
//     else if (k > i && k > j && k > l)
//     {
//         return k;
//     }
//     else
//     {
//         return l;
//     }
// }

void quicksort(individuo **vet, int ini, int final)
{
    int i, j;
    float meio;
    individuo *aux;

    i = ini;
    j = final;
    meio = vet[(ini + final) / 2]->fitness;

    do
    {
        while (vet[i]->fitness < meio)
            i++;

        while (vet[j]->fitness > meio)
            j--;

        if (i <= j)
        {
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (ini < j)
        quicksort(vet, ini, j);

    if (i < final)
        quicksort(vet, i, final);
}

// int paraBaixo(int *parede, int *saida)
// {
//     if (mapa[linha_atual + 1][coluna_atual] == PAREDE || mapa[linha_atual + 1][coluna_atual] == TETO)
//     {
//         *parede = 1;
//         return 0;
//     }
//     else
//     {
//         linha_atual = 1 + linha_atual;
//         passos = passos + 1;
//     }
//     if (mapa[linha_atual][coluna_atual] == SAIDA)
//     {
//         *saida = 1;
//     }
//     return 1;
// }

// int paraCima(int *parede, int *saida)
// {
//     if (mapa[linha_atual - 1][coluna_atual] == PAREDE || mapa[linha_atual - 1][coluna_atual] == TETO)
//     {
//         *parede = 1;
//         return 0;
//     }
//     else
//     {
//         linha_atual = linha_atual - 1;
//         passos = passos + 1;
//     }
//     if (mapa[linha_atual][coluna_atual] == SAIDA)
//     {
//         *saida = 1;
//     }
//     return 1;
// }

// int paraDireita(int *parede, int *saida)
// {
//     if (mapa[linha_atual][coluna_atual + 1] == PAREDE || mapa[linha_atual][coluna_atual + 1] == TETO)
//     {
//         *parede = 1;
//         return 0;
//     }
//     else
//     {
//         coluna_atual = coluna_atual + 1;
//         passos = passos + 1;
//     }
//     if (mapa[linha_atual][coluna_atual] == SAIDA)
//     {
//         *saida = 1;
//     }
//     return 1;
// }

// int paraEsquerda(int *parede, int *saida)
// {
//     if (mapa[linha_atual][coluna_atual - 1] == PAREDE || mapa[linha_atual][coluna_atual - 1] == TETO)
//     {
//         *parede = 1;
//         return 1;
//     }
//     else
//     {
//         coluna_atual = coluna_atual - 1;
//         passos = passos + 1;
//     }

//     if (mapa[linha_atual][coluna_atual] == SAIDA)
//     {
//         *saida = 1;
//     }
//     return 1;
// }

int main()
{
    individuo *indSaida = NULL;
    individuo *newInd[tampop + 25];
    // individuo *aux[tampop];
    populacao pop;
    int pergunta, perg;
    int parede = 0;
    int saida = 0;
    int contador = 0;
    int repete = 0;
    int *pontSaida = &saida;
    int *pontParede = &parede;
    int vet[1000];
    int geracao = 0;
    int i;

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
            desenhar_mapa(1, 1);
            break;
        case 2:
            system("clear");
            for (i = 0; i < 50; i++)
            {
                pop.inds[i] = iniciaPopulacao(pontParede, pontSaida);
                pop.inds[i]->ordem = i + 1;
            }
            pop.geracao = 1;

            quicksort(pop.inds, 0, tampop - 1);
            contador = 0;

            do
            {
                for (i = 0; i < 25; i++)
                {
                    newInd[i] = crossOver(pop.inds, pontParede, pontSaida);
                    newInd[i]->ordem = i + 1;
                }

                for (i = 0; i < 50; i++)
                {
                    newInd[i + 25] = pop.inds[i];
                    newInd[i + 25]->ordem = i + 26;
                }

                quicksort(newInd, 0, tampop + 24);

                float menor = newInd[0]->fitness;

                for (i = 0; i < 50; i++)
                {
                    pop.inds[i] = newInd[i];
                    saida = pop.inds[i]->fitness == 0;
                    menor = newInd[0]->fitness < menor ? newInd[0]->fitness : menor;
                }
                pop.geracao++;
                for (int i = 0; i < 50; i++)
                {
                    for (int j = 0; j < 50; j++)
                    {
                        // percurso(pop.inds[i]);
                        system("clear");
                        printf("individuo: %d\n", i);
                        printf("geracao: %d\n", pop.geracao);
                        printf("fitness: %f\n", pop.inds[i]->fitness);
                        printf("Menor fitness: %f\n", menor);
                        if (saida)
                        {
                            break;
                        }
                    }
                    if (saida)
                    {
                        break;
                    }
                }

                // if (contador < 25)
                // {
                //     newInd[50 + contador] = crossOver(newInd, pontParede, pontSaida);
                // }
                // else
                // {
                //     quicksort(newInd, 0, tampop - 1);
                //     pop.geracao++;
                // }

                // if (newInd[contador]->geracaoAtual == numGeracoes)
                // {
                //     if (contador == 50)
                //     {
                //         break;
                //     }
                // }
                // else if (saida == 1)
                // {
                //     break;
                // }
                // contador++;
                // if (contador > 50)
                // {
                //     contador = 0;
                // }
                // for (int i = 0; i < 50; i++)
                // {
                //     percurso(newInd[0]->genes[i], pontParede, pontSaida);

                //     if (saida == 1)
                //     {
                //         break;
                //     }
                // }

                //aux = newInd;
            } while (saida == 0);

            // for (int i = 0; i < 50; i++)
            // {
            //     percurso(newInd[0]->genes[i], pontParede, pontSaida);
            // }
            // ind = newInd[contador];
            system("clear");
            printf("indviduo: %d \n", pop.inds[0]->ordem);
            printf("Geracao: %d \n", pop.geracao);
            break;

        case 3:

            printf("saida: %d", saida);

            saida = 0;
            // linha_atual = 1;
            // coluna_atual = 1;
            percurso(pop.inds[0]);

            printf("indviduo: %d \n", contador);
            printf("Geracao: %d \n", pop.geracao);
            break;
        case 4:
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
