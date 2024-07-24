#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main() {
    char nome[MAX_CHAR];
    int numComp;
    int tamVetor = 50;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    clock_t start, end; // Declare as variáveis
    double total;
    
    //---Merge Sort Recursivo---
    printf("-----Merge Sort Recursivo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = mergeSort(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    //---Quick Sort Recursivo---
    printf("-----Quick Sort Recursivo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = quickSort(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    //---Heap Sort Recursivo---
    printf("-----Heap Sort Recursivo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = heapSort(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    //---Merge Sort Iterativo---
    printf("-----Merge Sort Iterativo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = mergeSortSR(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    //---Quick Sort Iterativo---
    printf("-----Quick Sort Iterativo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = quickSortSR(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    //---Heap Sort Iterativo---
    printf("-----Heap Sort Iterativo-----\n");
    preencheVetorAleatorio(vetor, tamVetor);
    printf("Vetor: ");
    imprimeVetor (vetor, tamVetor);
    start = clock(); // start recebe o "ciclo" corrente
	numComp = heapSortSR(vetor, tamVetor);
    end = clock();
	printf("Vetor ordenado: ");
    imprimeVetor(vetor, tamVetor);
	printf("\n");
	total = ((double)end - start) / CLOCKS_PER_SEC;
	printf ("Resultado: com %d elementos fez %d comparacoes em %f segundos\n", tamVetor, numComp, total);
    printf("\n");

    free(vetor);

    return 0;
}
