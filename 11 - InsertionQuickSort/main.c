#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_VALUE 1000

void insertionSort  (int size, int * array);
void quickSort      (int *array, int u, int v);
int perno           (int *array, int first, int last);
void swap           (int *one, int * two);
void quickInsertionSort(int *array, int first, int last, int half);
void insertionQuickSort(int* array, int first, int last);
int* buildArray     (int size);
void printArray     (int * array, int size);
int rnd             (int min, int max);

int main(void){
    srand((unsigned int) time(NULL));
    int *array = NULL;
    clock_t start, end;
    double elapsed_time;
    int choice = 0, size;

    printf("\nQuick/Selection Sort\n");

    printf("\nInsert size of random array : ");
    scanf("%d", &size);
    getchar();
    array = buildArray(size);
    printf("\nArray preview : ");
    printArray(array, size);

    printf("\n\nPick an algorithm\
            \n\t(1) Insertion Sort\
            \n\t(2) QuickSort\
            \n\t(3) Quick-Insertion Sort\
            \n\n\t(0) Exit\
            \n\nChoice : ");
    do{
        scanf("%d", &choice);
        getchar();
        if(choice < 0 || choice > 3)
            printf("\nInvalid choice\nChoice : ");
    }while(choice < 0 || choice > 3);

    switch(choice){
        case 1:{
            printf("\nSorting with Insertion Sort");
            start = clock();
            insertionSort(size, array);
            end = clock();
            elapsed_time = ((double) (end-start) / CLOCKS_PER_SEC);
            printf("\nInsertion sort required : %lf s", elapsed_time);
            break;
        }
        case 2:{
            printf("\nSorting with Quick Sort");
            start = clock();
            quickSort(array, 0, size-1);
            end = clock();
            elapsed_time = ((double) (end-start) / CLOCKS_PER_SEC);
            printf("Quick sort required : %lf s", elapsed_time);
            break;
        }
        case 3:{
            printf("\nQuickInsertion Sort");
            int half = 0;
            printf("\nInsert half : ");
            scanf("%d", &half);
            start = clock();
            quickInsertionSort(array, 0, size-1, half);
            end = clock();
            elapsed_time = ((double) (end-start) / CLOCKS_PER_SEC);
            printf("Quick-Insertion sort required : %lf s", elapsed_time);

        }
    }
    return 0;
}
int* buildArray(int size){
    int *array = NULL, tmp;
    array = (int*)malloc(sizeof(int)*size);
    if(array == NULL)
        exit(-1);
    for(int i = 0; i < size; i++)
        array[i] = rnd(1, MAX_VALUE);
    return array;
}
void printArray(int * array, int size){
    printf("\n");
    for(int i = 0; i < size; i++){
        printf("%d\t", array[i]);
    }
}
int rnd(int min, int max){
    return  min + rand()%(max-min+1);
}
void quickInsertionSort(int *array, int first, int last, int half){
    int q;
    if(first == last) return;
    if(last - first <= half){
        insertionQuickSort(array, first, last);
    }else{
        q = perno(array, first, last);
        if(first < q)
            quickSort(array, first, q - 1);
        else
            quickSort(array, q - 1, last);
    }
}
void insertionQuickSort(int* array, int first, int last){ //custom insertionsort
    int next, j;
    for(int i = first; i < last; i++){
        next=array[i];
        for(j = i - 1; j >= first; j--){ //j non puo' mai essere minore del primo indice preso in considerazione
            if(next < array[j])
                array[j + 1]=array[j];
            else
                break;
        }
        array[j+1]=next;
    }
}
void insertionSort(int size, int * array){
    int next, i, j;
    for(i = 1; i < size-1; i++){
        next = array[i];
        for(j = i -1; i > 0; i--){
            if(next < array[j])
                array[j+1] = array[j];
            else
                break;
        }
        array[j+1] = next;
    }
}
void quickSort(int *array, int u, int v){
    if(u==v) return;
    int q = perno(array, u, v);
    if(u < q) quickSort(array, u, q-1);
    if(q < v) quickSort(array, q+1, v);
}
int perno(int *array, int first, int last){
    int i = first;
    int j = last+1;
    int pivot = array[first];

    while(i < j){
        do{
            i++;
        }while(array[i] <= pivot && i <= last);
        do{
            j--;
        }while(array[j] >= pivot && j >= first);
        if(i < j)
            swap(&array[i], &array[j]);
    }
    return j;
}
void swap(int *one, int * two){
    int temp = *one;
    *one = *two;
    *two = temp;
}
