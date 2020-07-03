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
#define qtdGenes 200
// #define tampop 10
// #define qtdGenes 30
#define qtdFilhos tampop + tampop
#define numGeracoes 5000
#define mapaX 30
#define mapaY 30

long int percorrido[mapaX][mapaY];

typedef struct individuo
{
    long int genes[qtdGenes];
    double fitness;
    long int ordem;
    long int posicaoFinal[2];
    long int saiu;
    long int colidiu;
} individuo;

typedef struct populacao
{
    long int geracao;
    individuo *inds[tampop];
} populacao;

long int s1, s2, melhor1, melhor2, melhor3, melhor4;

// long int linha, coluna;

long int mapa[mapaX][mapaY];

individuo *crossOver(individuo **pop, individuo *ind);
individuo *iniciaPopulacao(individuo *ind_local);
void geracoes(populacao *populacao);
void percurso(individuo *ind, long int slow);
void gera_mapa();
void quicksort(individuo **vet, long int ini, long int final);
void limpar_labirinto();
void movimentaAtualiza(individuo *ind, long int index, long int valor);
void limpaPercorrido();
long int movimenta(long int movimento, long int *linha, long int *coluna);
long int desenhar_mapa();
long int maiorGene();
long int roleta();
long int mutacao();
long int ponto(long int i);
long int **alocaMapa(long int l, long int c);
double fitness(long int l, long int c);

void clear()
{
    printf("\033[H\033[J");
    // system("clear");
    usleep(10000);
}

individuo *cria_individuo()
{
    individuo *indCriado = (individuo *)malloc(sizeof(individuo));

    // for (long int j = 0; j < qtdGenes; j++)
    // {
    //     indCriado->genes[j] = -1;
    // }
    indCriado->fitness = 0;
    indCriado->ordem = 0;
    indCriado->posicaoFinal[0] = 1;
    indCriado->posicaoFinal[1] = 1;
    indCriado->saiu = 0;
    indCriado->colidiu = 0;

    return indCriado;
}

void resetaInd(individuo *ind)
{
    for (long int j = 0; j < qtdGenes; j++)
    {
        ind->genes[j] = -1;
    }
    ind->fitness = 0;
    ind->ordem = 0;
    ind->posicaoFinal[0] = 1;
    ind->posicaoFinal[1] = 1;
    ind->saiu = 0;
    ind->colidiu = 0;
}

void limpar_labirinto()
{
    long int m, n;
    long int linha1, coluna1;

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
    long int m, n;
    // srand(time(NULL));

    for (m = 0; m < mapaX; m++)
    {
        for (n = 0; n < mapaY; n++)
        {
            if (mapa[m][n] == 0)
            {
                mapa[m][n] = rand() % 3;
                // mapa[m][n] = CHAO;
                // mapa[mapaX / 3][n] = PAREDE;
                // mapa[(mapaX / 3) + (mapaX / 3)][n] = PAREDE;

                // mapa[mapaX / 3][mapaY - 2] = CHAO;
                // mapa[(mapaX / 3) + (mapaX / 3)][1] = CHAO;

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
    // s1 = mapaY - 2;
    // s2 = mapaX - 2;
    mapa[s2][s1] = 4;
}

long int desenhar_mapa(long int linha_atual, long int coluna_atual)
{
    long int linha1, coluna1;
    long int ponto;
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

individuo *iniciaPopulacao(individuo *ind_local)
{
    resetaInd(ind_local);
    long int novoValor;

    limpaPercorrido();
    for (long int i = 0; i < qtdGenes; i++)
    {
        novoValor = rand() % 4;
        movimentaAtualiza(ind_local, i, novoValor);
        // printf("%ld", ind_local->genes[i]);
    }
    // printf("\n");

    ind_local->fitness += fitness(ind_local->posicaoFinal[0], ind_local->posicaoFinal[1]);
    return ind_local;
}

long int movimenta(long int movimento, long int *linha, long int *coluna)
{
    long int linhaMovimento = *linha;
    long int colunaMovimento = *coluna;
    long int posicao;

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

void percurso(individuo *ind, long int slow)
{
    long int linha_atual = 1;
    long int coluna_atual = 1;
    long int i;
    long int resMovimento;

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
    long int i, j;
    for (i = 0; i < mapaX; i++)
        for (j = 0; j < mapaY; j++)
            percorrido[i][j] = 0;
}

void movimentaAtualiza(individuo *ind, long int index, long int valor)
{
    long int resMovimento = -1;
    long int x, y;

    // if (index == 0)
    // {
    //     ind->posicaoFinal[0] = 1;
    //     ind->posicaoFinal[1] = 1;
    // }
    ind->genes[index] = valor;

    if (!ind->colidiu && !ind->saiu)
    {
        resMovimento = movimenta(ind->genes[index], &ind->posicaoFinal[0], &ind->posicaoFinal[1]);
        x = ind->posicaoFinal[0];
        y = ind->posicaoFinal[1];

        if (percorrido[x][y])
            ind->fitness += 10;
        else
            percorrido[x][y] = 1;

        if (!resMovimento)
        {
            ind->fitness += mapaX * mapaY * 1000;
            ind->colidiu = 1;
        }
        else
        {
            //ind->fitness -= 10;
            //ind->fitness++;
        }

        if (resMovimento == 2 && !ind->saiu)
            ind->saiu = 1;
    }
}

individuo *crossOver(individuo **pop, individuo *ind) //esse foi a funÃ§Ã£o, onde os indviduos pegariam genes de individuos(podendo ou nao ser os melhores indviduos)
{
    resetaInd(ind);
    long int mutar = 0;
    individuo *y = pop[roleta()];
    individuo *z = pop[roleta()];
    mutar = mutacao();
    long int novoValor;
    long int i, j, trueIndex;

    long int tamSeq = (rand() % ((qtdGenes / 2) - (qtdGenes / 3))) + (qtdGenes / 3);

    long int i1 = ponto(qtdGenes);
    long int i2 = ponto(qtdGenes);

    for (i = i1; i < i1 + tamSeq; i++)
    {
        trueIndex = i % qtdGenes;
        ind->genes[trueIndex] = z->genes[trueIndex];
    }

    for (j = 0; j < qtdGenes - tamSeq; j++)
    {
        ind->genes[(j + i) % qtdGenes] = y->genes[(j + i2) % qtdGenes];
    }

    if (mutar)
    {
        ind->genes[ponto(qtdGenes)] = rand() % 4;
    }

    limpaPercorrido();
    for (long int i = 0; i < qtdGenes; i++)
    {
        movimentaAtualiza(ind, i, ind->genes[i]);
    }

    ind->fitness += fitness(ind->posicaoFinal[0], ind->posicaoFinal[1]);

    return ind;
}

long int mutacao()
{
    long int aleatorio, mutar;
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

long int ponto(long int i)
{
    long int aleatorio;
    aleatorio = rand() % i;
    return aleatorio;
}

long int roleta()
{
    // escolhe aleatoriamente um indviduo, entre 1Âº, 2Âº, 3Âº e 4Âº;
    long int aleatorio;
    long int primeiro = rand() % (qtdGenes / 2);
    long int segundo = (rand() % (qtdGenes / 2)) + (qtdGenes / 2) - 1;

    aleatorio = rand() % 10;

    aleatorio = aleatorio + 1;

    if (aleatorio >= 4 && aleatorio <= 11)
    {
        return primeiro % tampop;
    }
    else if (aleatorio >= 1 && aleatorio <= 3)
    {
        return segundo % tampop;
    }
}

double fitness(long int l, long int c)
{
    return sqrt(pow(s2 - l, 2) + pow(s1 - c, 2));
}

void quicksort(individuo **vet, long int ini, long int final)
{
    long int i, j;
    double meio;
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

void geracoes(populacao *populacao)
{
    individuo *pop[tampop];
    individuo *filhos[qtdFilhos];
    individuo *total[tampop + qtdFilhos];
    populacao->geracao = 1;

    long int i, j;
    long int saiu = 0;

    // Inicializa todos os ponteiros
    for (i = 0; i < tampop; i++)
    {
        pop[i] = cria_individuo();
        pop[i]->ordem = i + 1;
    }

    for (i = 0; i < qtdFilhos; i++)
    {
        filhos[i] = cria_individuo();
        pop[i]->ordem = i + 1;
    }

    // Inicializa populacao
    for (i = 0; i < tampop; i++)
        iniciaPopulacao(pop[i]);

    quicksort(pop, 0, tampop - 1);

    //usleep(100000);
    percurso(pop[0], 0);
    printf("Percurso da geracao: %ld\n", populacao->geracao);
    printf("melhor Fitness: %f\n", pop[0]->fitness);

    do
    {

        for (i = 0; i < qtdFilhos; i++)
        {
            crossOver(pop, filhos[i]);
            pop[i]->ordem = i != 1000? i + 1:i + 1 + 1000;
            filhos[i]->ordem = i != 1000? i + 1:i + 1 + 1000;
        }

        for (i = 0; i < tampop; i++)
            total[i] = pop[i];

        for (i = 0; i < qtdFilhos; i++)
            total[i + tampop] = filhos[i];

        quicksort(total, 0, tampop + qtdFilhos - 1);

        for (i = 0; i < tampop; i++)
        {
            pop[i] = total[i];
            if (pop[i]->saiu == 1)
                saiu = 1;
        }

        for (i = 0; i < qtdFilhos; i++)
        {
            filhos[i] = total[i + tampop];
            if (filhos[i]->saiu == 1)
                saiu = 1;
        }

        populacao->geracao++;

        if (populacao->geracao % 1000 == 0)
        {
            percurso(pop[0], 0);
            printf("Percurso da geracao: %ld\n", populacao->geracao);
            printf("melhor Fitness: %f\n", pop[0]->fitness);
            printf("melhor Individuo: %ld\n", pop[0]->ordem - 1000);
        }

    } while (!saiu);

    for (i = 0; i < tampop; i++)
        populacao->inds[i] = pop[i];

    percurso(pop[0], 0);
    printf("Percurso da geracao: %ld\n", populacao->geracao);
    printf("melhor Fitness: %f\n", pop[0]->fitness);
    printf("melhor Individuo: %ld\n", pop[0]->ordem - 1000);
}

long int main()
{
    srand(time(NULL));
    populacao pop;
    long int pergunta, perg;
    long int parede = 0;
    long int saida = 0;
    long int contador = 0;
    long int repete = 0;
    long int *pontSaida = &saida;
    long int *pontParede = &parede;
    long int vet[1000];
    long int geracao = 0;
    long int i;

    do
    {
        printf("Digite sua opcao\n");
        printf("0 - sair\n");
        printf("1 - gerar labirinto\n");
        printf("2 - comeÃ§ar labirinto\n");
        printf("3 - repetir individuo final\n");
        printf("4 - free individuos\n");
        printf("5 - limpar labirinto\n");
        printf("6 - limpar e gerar novo labirinto\n");
        scanf("%ld", &perg);

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
            // clear();
            geracoes(&pop);
            break;
        case 3:

            printf("saida: %ld", saida);

            saida = 0;
            // linha_atual = 1;
            // coluna_atual = 1;
            percurso(pop.inds[0], 1);

            printf("indviduo: %ld \n", pop.inds[0]->ordem);
            printf("Geracao: %ld \n", pop.geracao);
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
            printf("Digite uma opÃ§Ã£o valida\n");
            break;
        }
    } while (perg != 0);
    return 0;
}