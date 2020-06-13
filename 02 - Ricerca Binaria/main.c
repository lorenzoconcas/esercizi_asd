/*
es: ricercabinaria
*/
//written by lorenzo l. concas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZES 		6
#define ORDERS_SIZE			4

typedef enum 				{ ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE } ARRAY_ORDER;
int 						array_sizes[] = 	{100, 1000, 10000, 100000, 200000, 500000}; 

char* 						order_names[15] = 	{"ORDINATO", "QUASI_ORDINATO", "INV_ORDINATO", "CASUALE"};
char* 						size_names[ARRAY_SIZES] = 	{"100", "1000", "10K", "100K", "200K", "500K"};

double						results[ARRAY_SIZES][ORDERS_SIZE];
double						resultsRecursive[ARRAY_SIZES][ORDERS_SIZE];

void SelectionSort			(int size,int *array);
void swap					(int*, int*);
int* buildArray				(int size, ARRAY_ORDER type);
void printArray				(int size, int* array);
int rnd 					(int min, int max);

int ricercaBanale			(int size, int* array, int searchedNumber);
int ricercaBinariaIterativa	(int size, int * array, int searchedNumber);
int ricercaBinariaRicorsiva	(int * array, int first, int last, int searchedNumber);
	
int main(void){
	srand((unsigned int) time(NULL));
	int *array;
	int choice, size, pos;
	clock_t start, end;
	double time_elapsed; 

	printf("\nSelect array size\n");
	printf("\t(1) 100\n\t(2) 1000\n\t(3) 10K\n\t(4) 100K\n\t(5) 200K\n\t(6) 500K\n");
	printf("Choice:> ");
	do{
		scanf("%d", &choice);
		if(choice < 1 || choice >6)
			printf("\nInvalid Choice, try again\nChoice:>");
	}while(choice < 1 || choice >6);
	size = array_sizes[choice-1];
	printf("\nBuilding array");
	array = buildArray(size, CASUALE);
	printf("\nBuilt...\tNow sorting...");
	start = clock();
	SelectionSort(size, array);
	end = clock();
	time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	printArray(size, array);
	printf("\nSorted (in %lf seconds)\n", time_elapsed);
	do{
		printf("\nScegli un numero da cercare : ");
		scanf("%d", &choice);

		start = clock();
		pos = ricercaBanale(size, array, choice);
		end = clock();
		time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
		if(pos == -1){
			printf("Non presente nell'array");
			return 0;
		}
		printf("Found %d at : %d time : %lf\n", choice, pos, time_elapsed);

		start = clock();
		pos = ricercaBinariaIterativa(size, array, choice);
		end = clock();
		time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Found %d at : %d time : %lf\n", choice, pos, time_elapsed);

		start = clock();
		pos = ricercaBinariaRicorsiva(array, 0, size, choice);
		end = clock();
		time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Found %d at : %d time : %lf\n", choice, pos, time_elapsed);
		printf("Search another number?\n\t(1) Yes\n\t(2) No\n Choice :> ");
		do{
			scanf("%d", &choice);
			if(choice < 1 || choice > 2)
				printf("\nInvalid choice\nChoice :> ");
		}while(choice < 1 || choice > 2);

	}while(choice == 1);
	printf("\n\nDone! Goodbye");
	return 0;
}

void SelectionSort(int size,int *array){
	int i = 0, j = 0, min = 0;
	for(i = 0; i < size - 1; i++){
		min = i;
		for(j = i + 1; j < size; j++)
			if(array[j] < array[min])
				min = j;
		swap(&array[min], &array[i]);
	}
}
//must pass arguments with & before, even with arrays
void swap(int *element1, int *element2){	
	int temp;
    temp=*element1;
    *element1=*element2;
    *element2=temp;
}
int* buildArray(int size, ARRAY_ORDER type){
	int * array =  (int*)malloc(size*sizeof(int));
	int i = 0;
	switch(type){
		case ORDINATO:{
			for(i = 0; i<size; i++){
				array[i] = i ;
			}			
			break;
		}
		case QUASI_ORDINATO:{
			for(i = 0; i<size/2; i++){
				array[i] = i ;
			}
			for(; i<size; i++){
				array[i] = rnd(1, size);
			}
			break;
		}
		case INV_ORDINATO:{
			for(i = 0; i<size; i++){
				array[i] = size-i-1; //es 99->0		
			}
			break;
		}
		case CASUALE:{
			for(i = 0; i<size; i++){
				array[i] = rnd(1, size);		
			}
			break;
		}
	}
	/*printf("Array Built (type %d) :\n", type);
	printArray(size, array);
	printf("\n");*/
	return array;
}
void printArray(int size, int* array){
	printf("==============================\n");
	for(int i = 0; i < size; i++){
		printf("(%d) %d \n", i, array[i]);
	}
	printf("\n==============================\n");
}
int rnd(int min, int max){
	return  min + rand()%(max-min+1);
}
void printTable(int mode){
	double total = 0;
	printf("\n\n===========================================================================\n");
	printf("#####   ");
	for(int i = 0; i<ORDERS_SIZE; i++){
		printf("%s    ", order_names[i]);
	}
	printf("\n");
	for(int i = 0; i < ARRAY_SIZES; i++){
		printf("%s\t", size_names[i]);
		for(int j = 0; j < ORDERS_SIZE; j++){
			if(mode){
				printf("%.3lf\t\t",	(double) results[i][j]);
				total += results[i][j];
			}
			else{
				printf("%.3lf\t\t",	(double) resultsRecursive[i][j]);
				total += resultsRecursive[i][j];
			}
			
		}
		printf("\n");
	}
	printf("\nTotal time elapsed %.3lf", total);
}
int ricercaBanale(int size, int* array, int searchedNumber){
	int pos = 0;
	while(pos < size && array[pos] <= searchedNumber){
		if(searchedNumber == array[pos]) return pos;
		else pos++;		
	}
	return -1;
}
int ricercaBinariaIterativa(int size, int * array, int searchedNumber){
	int first = 0, last = size-1, half;
	while(first <= last){
		half = (first+last)/2;
		if(searchedNumber < array[half])
			last = half - 1;
		else if(searchedNumber == array[half])
			return half;
		else
			first = half+1;
	}
	return -1;
}

int ricercaBinariaRicorsiva(int * array, int first, int last, int searchedNumber){
	if(first > last) return -1;

	int half = (first + last)/2;

	if(array[half] == searchedNumber) return half;
	else if (array[half] < searchedNumber) return ricercaBinariaRicorsiva(array, half+1, last, searchedNumber);
	else return ricercaBinariaRicorsiva(array, first, half-1, searchedNumber);
}