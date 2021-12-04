#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//MERGE

/* Recebe um vetor v que está ordenado de
   ini até meio e de meio+1 até fim.
   Junta o conteúdo das duas metades em um
   único vetor ordenado. */
void merge(int v[], int aux[], int ini, int meio, int fim) {
    int i, esq, dir;
    esq = ini, dir = meio+1;
    // copio sempre o menor entre o da esquerda e o da direita
    for (i = esq; esq <= meio && dir <= fim; i++) {
        if (v[esq] <= v[dir]) 
            aux[i] = v[esq++];
        else
            aux[i] = v[dir++];
    }

    // obs.: só um desses vai rodar!
    while (dir <= fim)
        aux[i++] = v[dir++];
    while (esq <= meio)
        aux[i++] = v[esq++];

    for (i = ini; i <= fim; i++)
        v[i] = aux[i];
}

void mergesort(int v[], int aux[], int ini, int fim) {
    if (ini == fim)
        // só tem um elemento! já está ordenado
        return; 
    int meio = (ini+fim)/2;
    mergesort(v, aux, ini, meio);
    mergesort(v, aux, meio+1, fim);
    merge(v, aux, ini, meio, fim);
}

void ordena(int v[], int tamanho) {
    int * aux = malloc(tamanho*sizeof (int));
    mergesort(v, aux, 0, tamanho-1);
    free(aux);
}
//MERGE

//BUBBLE
void swap(int x[], int i, int j) {
    int aux = x[i];
    x[i] = x[j];
    x[j] = aux;
}

// versão 1.0
void bubbleSort(int v[], int n) {
    bool fez_swap;
    // j é a quantidade de passadas que vou fazer
    for (int j = 0; j < n-1; j++) {
        fez_swap = false;
        for (int i = 0; i < n-1-j; i++)
            if (v[i] > v[i+1]) {
                swap(v, i, i+1);
                fez_swap = true;
            }
        if (!fez_swap) break;
    }
}
//BUBBLE

//Funcao que preenche todas posicoes dos dois vetores (todas posicoes tem que ter o mesmo valor nos dois vetores)
void preencheVetores(int* vetor1, int* vetor2,int N){
    for(int i = 0; i < N;i++){
        vetor1[i] = (rand() % (N*2) + 1);
        vetor2[i] = vetor1[i];
    }
}
/*
Funcao principal que aloca a memoria pros dois vetores que vamos utilizar,
chama a funcao que preenche todas as posicoes dos vetores 10 vezes diferentes
e ordena os dois vetores todas as vezes, somando o tempo de execucao
e fazendo a media dos tempos.
*/
void calcularPerformance(int N){
    int *vetor = malloc(sizeof (int) * N);
    int *vetor2 = malloc(sizeof (int) * N);

    clock_t inicio, final;
    double tempoBubble = 0, tempoMerge = 0;

    for(int i = 0;i < 10;i++){
        preencheVetores(vetor, vetor2, N);
        //Bubble
        inicio = clock();
        bubbleSort(vetor, N);
        final = clock();
        tempoBubble += ((double) (final-inicio)/CLOCKS_PER_SEC);
        //Merge
        inicio = clock();
        ordena(vetor2, N);
        final = clock();
        tempoMerge += ((double) (final-inicio)/CLOCKS_PER_SEC);
    }

    tempoBubble = tempoBubble/10;
    tempoMerge = tempoMerge/10; 
    printf("N = %d\n", N);
    printf("Bubble : %f segundos em media\n", tempoBubble);
    printf("Merge : %f segundos em media\n", tempoMerge);

    free(vetor);
    free(vetor2);
}

int main(void){
    srand(time(NULL));

    int N = 10;
    for(int i = 0;i < 10;i++){
        calcularPerformance(N);
        if(i % 2 == 0)
            N *= 2;
        else
            N *= 5;

        printf("\n");
    }
    return 0;
}