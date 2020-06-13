#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE}inputType;

int* genera_array   (int, inputType);
void merge          (int[], int[], int, int, int);
void mergesort      (int[], int[], int, int);
void adatta         (int[], int, int);
void heapsort       (int[],int);
void makeHeap       (int[],int[],int);
void swap           (int* ,int* );

int main() {
    srand(time(NULL));
    int dimArray,i,choice;
    int *lista=NULL, *ordinata=NULL, *heap;
    printf("Heap Merge");
    printf("\nInsert array size :");
    scanf("%d",&dimArray);
    getchar();

    lista=genera_array(dimArray, CASUALE);
    ordinata=(int*)malloc((dimArray)*sizeof(int));

    if (ordinata == NULL)
        exit(-1);

    printf("\nUnordered array :\n");
    for(i=0;i<dimArray;i++)
        printf("%d ",lista[i]);

    do{
        printf("\nChoose algorithm :\
               \n\t(0) Merge Sort\
               \n\t(1) Heap Sort");

        scanf("%d",&choice);
        switch (choice){
            case 0:{
                mergesort(lista,ordinata,0,dimArray-1);

                printf("\nOrdered array : \n");
                for(i=0;i<dimArray;i++)
                    printf("%d ",lista[i]);
                break;
            }
            case 1:{
                heap=(int*)malloc((dimArray+1)*sizeof(int));
                if (heap == NULL)
                    exit(-1);
                makeHeap(lista,heap,dimArray);
                heapsort(heap,dimArray);

                 printf("\nOrdered array : \n");
                for(i=0;i<dimArray;i++)
                    printf("%d ",heap[i+1]);
                break;
            }
            default:
                printf("\nWrong choice, goodbye");
        }
    }
    while(choice < 0 || choice > 1);

    free(ordinata);
    free(lista);
    return 0;
}

int* genera_array(int dim, inputType tipo){
    int *array,i,aux=0;
    array=(int*)malloc(dim*sizeof(int));
    if (array == NULL)
        exit(-1);
    switch (tipo){
        case(ORDINATO):{ //caso ordinato
            for(i=0;i<dim;i++) {
                aux=aux+rand()%20;
                array[i] = aux;
            }
            break;
        }
        case(QUASI_ORDINATO):{ //caso parzialmente ordinato
            for(i=0;i<dim/2;i++) {
                aux=aux+rand()%20;
                array[i] = aux;
            }
            for(;i<dim;i++) {
                array[i] = rand()%100;
            }
            break;
        }
        case(INV_ORDINATO):{ //caso inversamente ordinato
            for(i=dim-1;i>=0;i--) {
                aux=aux+rand()%20;
                array[i] = aux;
            }
            break;
        }
        case(CASUALE):{ //caso ordine random
            for(i=0;i<dim;i++) {
                array[i] = rand()%100;
            }
        }
    }
    return array;
}

void mergesort(int lista[], int ordinata[], int lower, int upper){
    int medium;

    if (lower >= upper)
        return;

    medium = (lower + upper)/2;

    mergesort(lista, ordinata, lower, medium);
    mergesort(lista, ordinata, medium+1, upper);
    merge(lista, ordinata, lower, medium, upper);
}

void merge(int lista[], int ordinata[], int i, int m, int n) {
    int j, k, pos_iniziale, t ,z;

    j = m + 1; //indice per la seconda lista
    k = i; //indice per la lista ordinata
    pos_iniziale = i; //posizione iniziale nella lista
    while (i <= m && j <= n) {
        if (lista[i] <= lista[j]) {
            ordinata[k] = lista[i];
            i++;
            k++;
        } else {
            ordinata[k] = lista[j];
            j++;
            k++;
        }
    }

    if (i > m) {//unisco nella lista gli elementi non inseriti di uno dei due sotto array in attesa
        // ordinata[k],..., ordinata[n] ← lista[j],..., lista[n]
        for (t = j; t <= n; t++)
            ordinata[k + t - j] = lista[t];
    } else
        // ordinata[k],..., ordinata[n] ← lista[i],..., lista[m]
        for (t = i; t <= m; t++)
            ordinata[k + t - i] = lista[t];

    for (z=pos_iniziale;z<=n;z++){
        lista[z] = ordinata[z];
    }
    free(ordinata);
}

void adatta(int lista[], int radice, int n) {
    int temp, figlio;

    temp = lista[radice];
    figlio = 2 * radice; //figlio sx

    while (figlio <= n){ //trova il maggiore tra il figlio sx e figlio dx
        if (figlio < n && lista[figlio] < lista[figlio + 1] )
            figlio = figlio + 1;

        // confronta la radice e figlio max
        if (temp > lista[figlio])
            break; //il padre di figlio sara' la posizione corretta
        else {
            lista[figlio / 2] = lista[figlio]; // il figlio si sposta verso il padre
            //ripeti sul sottoalbero selezionato
            figlio = 2 * figlio;
        }
    }
    lista[figlio/2] = temp; // copia la radice nella posizione corretta
}

void heapsort(int lista[],int n){
    int i;
    // Si costruisce l' heap associato all'insieme da ordinare
    for( i = (n)/2; i != 0; i--) {
        adatta(lista, i, n);
    }

    for(i = n - 1; i != 0; i--) {
        //si estrae, di volta in volta, il massimo lista[1] e lo si posiziona in fondo alla sequenza
        swap(&lista[1], &lista[i + 1]);
        // si opera nuovamente sullo heap ridotto di un elemento
        adatta(lista, 1, i);
    }
}

void makeHeap(int array[],int heap[],int dim){
    int i,l=0;
    heap[0]=dim;
    for(i=1;i<=dim;i++) {
        heap[i]=array[l];
        l++;
    }
}
void swap(int* max, int* min){
    int aux;
    aux = *max;
    *max = *min;
    *min = aux;
}