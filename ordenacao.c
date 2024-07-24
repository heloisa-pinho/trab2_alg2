#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

void getNome(char nome[]) {
    // substitua por seu nome
    strncpy(nome, "Heloisa de Oliveira Pinho", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20231961; }

int aleat(int min, int max){
    return min + (rand() % (max - min + 1));
}

void preencheVetorAleatorio(int *vetor, int tam){
    srand(time(NULL));

	for (int i = 0; i < tam; ++i)
		vetor[i] = aleat(0,50);
}

//preenche o vetor ordenado seguindo o numero do indice
void preencheVetorOrdenado (int *vetor, int tam) {
	int i;
	for (i = 0; i < tam; i++)
		vetor[i]= i;
}

void imprimeVetor(int vetor[], int tam){
	for (int i = 0; i < tam; i++){
		printf("[%d] ", vetor[i]);
	}
	printf("\n");
}

//troca elementos do vetor
void troca(int v[], int a, int b){
	int aux;
	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

//------Merge Sort Recursivo------

void copia_Vetor(int v[], int V_aux[], int tam) {
    int i;

	for(i = 0; i < tam; i++)
		v[i] = V_aux[i];
    
	return;
}

/*ordena o vetor usando um vetor secundário. 
Ela divide o vetor principal ao M e ordena nesse subvetor criado. */
int merge(int v[], int ini, int meio, int fim, uint64_t *numComparacoes) {
    if (ini >= fim)
        return -1;
    
    int i,j,k,aux,tam;

    tam = fim - ini + 1;

    //cria vetor auxiliar
    int *v_Aux = malloc(tam * sizeof(int));
	if (v_Aux == NULL){
		printf("Falha fatal. Impossível alocar memoria.");
		return -1;
	}

    aux = k = 0;
	i = ini;
	j = meio +1;

    while (k <= fim - ini) {
		if (j > fim || (i <= meio && v[i] <= v[j])) {
			aux = i;
			i++;
		}
		else {
			aux = j;
			j++;
		}
		(*numComparacoes)++;
		v_Aux[k] = v[aux];
		k++;
	}

    copia_Vetor(v + ini,v_Aux, tam);
    free(v_Aux);

    return 1;
}

/* Função auxiliar responsável por particionar os 
subvetores para permitir que sejam agrupados de forma ordenada. */
int auxMergeSort(int v[], int ini, int fim, uint64_t *numComparacoes) {
	if (ini >= fim)
		return -1;

	int meio;
	meio = (ini + fim) / 2;

	auxMergeSort(v, ini, meio, numComparacoes);
	auxMergeSort(v, meio + 1, fim, numComparacoes);
	merge(v, ini, meio, fim, numComparacoes);

	return 1;
}

uint64_t mergeSort(int vetor[], size_t tam) {
    uint64_t numComparacoes = 0;
    int ini,fim;

    ini = 0;
    fim = tam - 1;

    auxMergeSort(vetor, ini, fim, &numComparacoes);

    return numComparacoes;
}

//---Quick Sort Recursivo---

/* coloca o pivo no seu devido lugar, todos os elementos à direita do pivô são maiores,
 e os da esquerda são menores. */
int particiona(int v[], int ini, int fim, uint64_t *numComparacoes) {
    int p,m,i;

    p = v[fim]; //pivo
    m = ini;

    for (i = ini; i <= fim-1; i++){
        if (v[i] <= p){
            troca(v,m,i);
            m++;
            (*numComparacoes)++;
        }
    }

    troca(v,m,fim);

    return m;
}

// Função auxiliar do QuickSort que particiona o vetor e chama recursivamente para as subpartes.
int auxQuickSort(int v[], int ini, int fim, uint64_t *numComparacoes) {
    if (ini >= fim)
        return -1;

    int m;
    m = particiona(v,ini,fim,numComparacoes);
    auxQuickSort(v,ini,m-1,numComparacoes);
    auxQuickSort(v,m+1,fim,numComparacoes);

    return 1;
}

uint64_t quickSort(int vetor[], size_t tam) {
    uint64_t numComparacoes = 0;
    int ini,fim;

    ini = 0;
    fim = tam - 1;

    auxQuickSort(vetor,ini,fim,&numComparacoes);

    return numComparacoes;
}

//---Heap Sort Recursivo---

/* cria uma maxHeap recursivamente conforme o nodo pai de indice i */
void maxHeapfy(int h[], int i, int tam, uint64_t *numComparacoes){
	int maior,E,D;

    E = 2*i+1;
    D = 2*i+2;
	
	if (( (E < tam) && (h[E] > h[i]) ))
		maior = E;
	else
		maior = i;
    (*numComparacoes)++;    
	
	if(( (D < tam) && (h[D] > h[maior]) )){
		(*numComparacoes)++;
		maior = D;
	}

	if(maior != i){ //confere se o nodo pai já não é o maior
		troca(h, i, maior);
		maxHeapfy(h, maior, tam, numComparacoes);
	}

	return;
}

void constroi_MaxHeap(int h[], int tam, uint64_t *numComparacoes){
    int i;

	for(i = (tam/2) - 1; i >= 0; i--)
			maxHeapfy(h, i, tam, numComparacoes);

	return;
}

/* Função auxiliar que ordena o vetor trocando a raiz (maior valor) da maxHeap
pelo ultimo indice, chamando maxHeapfy para n-1 */
int auxHeapSort (int h[], int tam, uint64_t *numComparacoes){
    int i;
    constroi_MaxHeap(h,tam,numComparacoes);

    for (i = tam - 1; i > 0; i--){
        troca(h,0,i);
        maxHeapfy(h,0,i,numComparacoes);
    }

    return 1;
}

uint64_t heapSort(int vetor[], size_t tam) {
    uint64_t numComparacoes = 0;

    auxHeapSort(vetor,tam, &numComparacoes);

    return numComparacoes;
}

//---Merge Sort Iterativo---

/* ordena o vetor comparando os dois vetores auxiliares,
assim coloca no vetor original o menor entre eles */
int mergeSR(int v[], int esq, int meio, int dir, uint64_t *numComparacoes){
    int tamE = meio - esq + 1;
    int tamD = dir - meio;
    int* vEsq = (int*)malloc(tamE * sizeof(int));
    int* vDir = (int*)malloc(tamD * sizeof(int));

    for (int i = 0; i < tamE; i++)
        vEsq[i] = v[esq + i];
    for (int i = 0; i < tamD; i++)
        vDir[i] = v[meio + 1 + i];
    
    int i = 0, j = 0, k = esq;
    
    while (i < tamE && j < tamD){
        if (vEsq[i] <= vDir[j]){
            v[k] = vEsq[i];
            i++;
        } else {
            v[k] = vDir[j];
            j++;
        }
        k++;
        (*numComparacoes)++;
    }
    
    while (i < tamE){
        v[k] = vEsq[i];
        i++;
        k++;
    }
    
    while (j < tamD){
        v[k] = vDir[j];
        j++;
        k++;
    }
    
    free(vEsq);
    free(vDir);
    
    return 1;
}

// Função auxiliar que implementa o MergeSort não-recursivo utilizando três pilhas
int auxmergeSortSR(int v[], size_t tam, uint64_t *numComparacoes){
    if (tam <= 1)
        return 0;
    
    int* pilhaE = (int*)malloc(tam * sizeof(int));
    int* pilhaD = (int*)malloc(tam * sizeof(int));
    int* pilhaM = (int*)malloc(tam * sizeof(int));
    int topo = -1;

    if ((pilhaE == NULL || pilhaE == NULL || pilhaM == NULL)){
        printf("Erro,falha ao alocar memoria.\n");
        return 0;
    }
    
    pilhaE[++topo] = 0;
    pilhaD[topo] = tam - 1;
    pilhaM[topo] = -1;
    
    while (topo >= 0){
        int esq = pilhaE[topo];
        int dir = pilhaD[topo];
        int meio = pilhaM[topo];
        topo--;
        
        if (meio == -1){
            if (esq < dir) {
                meio = esq + (dir - esq) / 2;
                pilhaE[++topo] = esq;
                pilhaD[topo] = dir;
                pilhaM[topo] = meio;
                pilhaE[++topo] = esq;
                pilhaD[topo] = meio;
                pilhaM[topo] = -1;
                pilhaE[++topo] = meio + 1;
                pilhaD[topo] = dir;
                pilhaM[topo] = -1;
            }
        } else {
            *numComparacoes+= mergeSR(v, esq, meio, dir,numComparacoes);
        }
    }
    
    free(pilhaE);
    free(pilhaD);
    free(pilhaM);
    
    return 1;
}

uint64_t mergeSortSR(int vetor[], size_t tam){
    uint64_t numComparacoes = 0;

    auxmergeSortSR(vetor, tam, &numComparacoes);

    return numComparacoes;
}

//--- Quick Sort Iterativo---

// Função auxiliar que implementa o QuickSort não-recursivo utilizando pilha
int auxQuickSortSR(int v[], int tam, uint64_t *numComparacoes ){
    if (tam <= 1)
        return 0;

    int *pilha = (int *)malloc(tam * sizeof(int));

    if (pilha == NULL){
        printf("Erro,falha ao alocar memoria.\n");
        return 0;
    }

    int topo = -1;

    // Empilha os índices iniciais
    pilha[++topo] = 0;
    pilha[++topo] = tam - 1;

    while (topo >= 0){

        // Desempilha os índices dos sub-arrays
        int fim = pilha[topo--];
        int ini = pilha[topo--];
        int p = particiona(v, ini, fim, numComparacoes);

        // Se houver elementos à esquerda do pivô, empilha os índices dos elementos menores que p
        if (p - 1 > ini){
            pilha[++topo] = ini;
            pilha[++topo] = p - 1;
        }

        // Se houver elementos à direita do pivô, empilha os índices dos elementos maiores que p
        if (p + 1 < fim){
            pilha[++topo] = p + 1;
            pilha[++topo] = fim;
        }
    }

    free(pilha);

    return 1;
}

uint64_t quickSortSR(int v[], size_t tam){
    uint64_t numComparacoes = 0;

    auxQuickSortSR(v, tam, &numComparacoes);

    return numComparacoes; 
}

//---Heap Sort Iterativo---

/* cria uma maxHeap sem recursividade conforme o nodo pai de indice i */
void maxHeapfySR(int h[], int i, int tam, uint64_t *numComparacoes){
    int maior = i; 
    int E, D; 

    while (maior < tam / 2){
        E = 2 * i + 1; 
        D = 2 * i + 2;

        if (E < tam && h[E] > h[maior]){
            maior = E;
            (*numComparacoes)++;
        }

        if (D < tam && h[D] > h[maior]){
            maior = D;
            (*numComparacoes)++;
        }

        if (maior != i){
            troca(h, i, maior); 
            i = maior; 
        }
        else
            return;
    }
}

/* Função auxiliar que ordena o vetor trocando a raiz (maior valor) da maxHeap
pelo ultimo indice, chamando maxHeapfy para n-1  */
int auxHeapSortSR(int h[], int tam, uint64_t *numComparacoes){
    int i;

    constroi_MaxHeap(h,tam,numComparacoes);

    for (i = tam - 1; i > 0; i--){
        troca(h,0,i);
        maxHeapfySR(h,0,i,numComparacoes);
    }

    return 1;
}

uint64_t heapSortSR(int vetor[], size_t tam){
    uint64_t numComparacoes = 0;

    auxHeapSortSR(vetor,tam, &numComparacoes);

    return numComparacoes;
}