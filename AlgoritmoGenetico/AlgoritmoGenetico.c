#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define CHAO 0
#define PAREDE 1
#define SAIDA 4
#define inicio 2
#define TETO 3
#define tampop 1000
#define qtdFilhos tampop + tampop
#define qtdGenes 200
#define numGeracoes 5000
#define mapaX 30
#define mapaY 30

int percorrido[mapaX][mapaY];

typedef struct individuo
{
    int genes[qtdGenes];
    float fitness;
    int ordem;
    int posicaoFinal[2];
    int saiu;
    int colidiu;
} individuo;

typedef struct populacao
{
    int geracao;
    individuo *inds[tampop];
} populacao;

int s1, s2, melhor1, melhor2, melhor3, melhor4;

// int linha, coluna;

int mapa[mapaX][mapaY];

individuo *crossOver(individuo **ind, int *parede, int *saida);
individuo *iniciaPopulacao(int *parede, int *saida);
void percurso(individuo *ind, int slow);
void gera_mapa();
void quicksort(individuo **vet, int ini, int final);
void limpar_labirinto();
void movimentaAtualiza(individuo *ind, int index, int valor);
void limpaPercorrido();
int movimenta(int movimento, int *linha, int *coluna);
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

void clear()
{
    printf("\033[H\033[J");
    usleep(10000);
}

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    // for (int j = 0; j < qtdGenes; j++)
    // {
    //     indCriado->genes[j] = -1;
    // }
    indCriado->fitness = 0;
    indCriado->ordem = 0;
    indCriado->posicaoFinal[0] = 1;
    indCriado->posicaoFinal[1] = 1;
    indCriado->saiu = 0;

    return indCriado;
}

void limpar_labirinto()
{
    int m, n;
    int linha1, coluna1;

    for (m = 0; m < mapaX; m++)
    {
        for (n = 0; n < mapaY; n++)
        {
            mapa[m][n] = 0;
        }
    }
    for (linha1 = 0; linha1 < mapaX; linha1++)
    {
        for (coluna1 = 0; coluna1 < mapaY; coluna1++)
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
    // srand(time(NULL));

    for (m = 0; m < mapaX; m++)
    {
        for (n = 0; n < mapaY; n++)
        {
            if (mapa[m][n] == 0)
            {
                mapa[m][n] = rand() % 3;
                // mapa[m][n] = CHAO;
                // mapa[mapaX / 2][n] = PAREDE;

                mapa[mapaX / 2][mapaY - 2] = CHAO;

                mapa[1][1] = 0;
                if (mapa[m][n] == 2)
                {
                    mapa[m][n] = 0;
                }
            }
            mapa[0][n] = 3;
            mapa[mapaX - 1][n] = 3;
            mapa[m][0] = 1;
            mapa[m][mapaY - 1] = 1;
        }
    }
    s1 = rand() % mapaY;
    s2 = rand() % mapaX;
    // s1 = 1;
    // s2 = mapaX - 2;
    mapa[s2][s1] = 4;
}

int desenhar_mapa(int linha_atual, int coluna_atual)
{
    int linha1, coluna1;
    int ponto;
    for (linha1 = 0; linha1 < mapaX; linha1++)
    {
        for (coluna1 = 0; coluna1 < mapaY; coluna1++)
        {
            ponto = mapa[linha1][coluna1];

            if ((linha1 == linha_atual) && (coluna1 == coluna_atual))
            {
                switch (ponto)
                {
                case CHAO:
                    printf("\033[1;31mO\033[0m");
                    break;
                case SAIDA:
                    printf("\033[1;32mO\033[0m");
                    break;
                default:
                    printf("\033[1;31m#\033[0m");
                    break;
                }
            }
            else
            {
                switch (ponto)
                {
                case CHAO:
                    printf(" ");
                    break;

                case SAIDA:
                    printf("\033[1;32mX\033[0m");
                    break;

                default:
                    printf("\033[0;36m#\033[0m");
                    break;
                }
            }
            printf(" ");
        }
        printf("\n");
    }
    return 1;
}

individuo *iniciaPopulacao(int *parede, int *saida)
{
    individuo *ind_local = cria_individuo();
    int novoValor;

    limpaPercorrido();
    for (int i = 0; i < qtdGenes; i++)
    {
        novoValor = rand() % 4;
        movimentaAtualiza(ind_local, i, novoValor);
        printf("%d", ind_local->genes[i]);
    }
    printf("\n");

    ind_local->fitness += fitness(ind_local->posicaoFinal[0], ind_local->posicaoFinal[1]);
    return ind_local;
}

int movimenta(int movimento, int *linha, int *coluna)
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

    *linha = linhaMovimento;
    *coluna = colunaMovimento;

    if (posicao == PAREDE || posicao == TETO)
        return 0;
    else if (posicao == SAIDA)
        return 2;
    return 1;
}

void percurso(individuo *ind, int slow)
{
    int linha_atual = 1;
    int coluna_atual = 1;
    int i;
    int resMovimento;

    for (i = 0; i < qtdGenes; i++)
    {
        resMovimento = movimenta(ind->genes[i], &linha_atual, &coluna_atual);
        clear();
        desenhar_mapa(linha_atual, coluna_atual);

        if (slow)
            usleep(100000);

        if (resMovimento == 2 || !resMovimento)
            break;
    }
    // usleep(1000000);
}

void limpaPercorrido()
{
    int i, j;
    for (i = 0; i < mapaX; i++)
        for (j = 0; j < mapaY; j++)
            percorrido[i][j] = 0;
}

void movimentaAtualiza(individuo *ind, int index, int valor)
{
    int resMovimento = -1;
    int x, y;

    if (index == 0)
    {
        ind->posicaoFinal[0] = 1;
        ind->posicaoFinal[1] = 1;
    }
    ind->genes[index] = valor;

    if (!ind->colidiu && !ind->saiu)
    {
        resMovimento = movimenta(ind->genes[index], &ind->posicaoFinal[0], &ind->posicaoFinal[1]);
        x = ind->posicaoFinal[0];
        y = ind->posicaoFinal[1];

        if (percorrido[x][y])
            ind->fitness += 1;
        else
            percorrido[x][y] = 1;
    }

    if (!resMovimento)
    {
        ind->fitness += mapaX * mapaY * 1000;
        ind->colidiu = 1;
    }
    else
    {
        // ind->fitness -= 0.5;
        ind->fitness++;
    }

    if (resMovimento == 2 && !ind->saiu)
        ind->saiu = 1;
}

individuo *crossOver(individuo **ind, int *parede, int *saida) //esse foi a função, onde os indviduos pegariam genes de individuos(podendo ou nao ser os melhores indviduos)
{
    //// srand(time(NULL));
    individuo *ind_filho = cria_individuo();
    int x, y, z, mutar = 0;
    x = ponto(qtdGenes);
    y = roleta();
    z = roleta();
    mutar = mutacao();
    int novoValor;
    int i, j, trueIndex;

    int tamSeq = (rand() % ((qtdGenes / 2) - (qtdGenes / 3))) + (qtdGenes / 3);

    int i1 = ponto(qtdGenes);
    int i2 = ponto(qtdGenes);

    for (i = i1; i < i1 + tamSeq; i++)
    {
        trueIndex = i % qtdGenes;
        ind_filho->genes[trueIndex] = ind[z]->genes[trueIndex];
    }

    for (j = 0; j < qtdGenes - tamSeq; j++)
    {
        ind_filho->genes[(j + i) % qtdGenes] = ind[y]->genes[(j + i2) % qtdGenes];
    }

    if (mutar == 1)
    {
        ind_filho->genes[ponto(qtdGenes)] = rand() % 4;
    }

    limpaPercorrido();
    for (int i = 0; i < qtdGenes; i++)
    {
        movimentaAtualiza(ind_filho, i, ind_filho->genes[i]);
    }

    ind_filho->fitness += fitness(ind_filho->posicaoFinal[0], ind_filho->posicaoFinal[1]);

    return ind_filho;
}

int mutacao()
{
    //// srand(time(NULL));
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
    //// srand(time(NULL));

    int aleatorio;

    aleatorio = rand() % i;
    return aleatorio;
}

int roleta()
{
    //// srand(time(NULL));
    // escolhe aleatoriamente um indviduo, entre 1º, 2º, 3º e 4º;
    int aleatorio, primeiro = rand() % (qtdGenes / 2), segundo = (rand() % (qtdGenes / 2)) + (qtdGenes / 2) - 1;

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

int main()
{
    srand(time(NULL));
    individuo *newInd[qtdFilhos + tampop];
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
        printf("6 - limpar e gerar novo labirinto\n");
        scanf("%d", &perg);

        switch (perg)
        {
        case 0:
            printf("saindo do programa\n");
            break;

        case 1:
            clear();
            gera_mapa();
            desenhar_mapa(1, 1);
            break;
        case 2:
            clear();
            saida = 0;
            for (i = 0; i < tampop; i++)
            {
                pop.inds[i] = iniciaPopulacao(pontParede, pontSaida);
                pop.inds[i]->ordem = i + 1;
                if (pop.inds[i]->saiu && !saida)
                    saida = 1;
            }
            pop.geracao = 1;

            quicksort(pop.inds, 0, tampop - 1);
            contador = 0;

            percurso(pop.inds[0], 0);

            if (saida)
                break;

            float menor;
            int contador = 0;
            do
            {

                pop.geracao++;
                for (i = 0; i < qtdFilhos; i++)
                {
                    newInd[i] = crossOver(pop.inds, pontParede, pontSaida);
                    individuo *ind = pop.inds[i];
                    newInd[i]->ordem = i + 1;
                }
                // return 0;

                for (i = 0; i < tampop; i++)
                {
                    newInd[qtdFilhos + i] = pop.inds[i];
                    newInd[qtdFilhos + i]->ordem = i + qtdFilhos + 1;
                }

                quicksort(newInd, 0, qtdFilhos + tampop - 1);

                menor = newInd[0]->fitness;

                for (i = 0; i < tampop; i++)
                {
                    pop.inds[i] = newInd[i];
                    menor = newInd[i]->fitness < menor ? newInd[i]->fitness : menor;
                    // saida = pop.inds[i]->fitness == 0;

                    if (pop.inds[i]->saiu && !saida)
                        saida = 1;
                }
                
                // for (i = 0; i < 2000; i++)
                // {
                //     free(newInd[tampop + i]);
                // }

                //free(newInd);

                if (pop.geracao % 1000 == 0)
                {
                    percurso(pop.inds[0], 0);
                    printf("Percurso da geracao: %d\n", pop.geracao);
                }
                if (pop.geracao == 4000)
                {
                    break;
                }
            } while (saida == 0 /*|| ++contador < 5000*/);

            // for (int i = 0; i < 50; i++)
            // {
            //     percurso(newInd[0]->genes[i], pontParede, pontSaida);
            // }
            // ind = newInd[contador];
            clear();
            printf("indviduo: %d \n", pop.inds[0]->ordem);
            printf("Geracao: %d \n", pop.geracao);
            printf("Fitness: %f \n", pop.inds[0]->fitness);
            printf("Saiu: %d \n", pop.inds[0]->saiu);
            break;

        case 3:

            printf("saida: %d", saida);

            saida = 0;
            // linha_atual = 1;
            // coluna_atual = 1;
            percurso(pop.inds[0], 1);

            printf("indviduo: %d \n", pop.inds[0]->ordem);
            printf("Geracao: %d \n", pop.geracao);
            break;
        case 4:
            clear();
            break;
        case 5:
            limpar_labirinto();
            clear();
            break;
        case 6:
            limpar_labirinto();
            clear();
            gera_mapa();
            desenhar_mapa(1, 1);
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
