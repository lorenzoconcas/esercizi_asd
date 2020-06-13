/*
es: Selection Sort
pseudo codice :
algoritmo selectionSort(array A, int n)
for i ← 0 to n-2 do
	min ← i 
	for j ← i+1 to n-1 do 
	if (A[j] < A[min]) then 
		min ← j 
		scambia A[min] con A[i]
*/
//written by lorenzo l. concas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZES 	6
#define ORDERS_SIZE		4

typedef enum 			{ ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE } ARRAY_ORDER;
int 					array_sizes[] = 	{100, 1000, 10000, 100000, 200000, 500000}; 

char* 					order_names[15] = 	{"ORDINATO", "QUASI_ORDINATO", "INV_ORDINATO", "CASUALE"};
char* 					size_names[ARRAY_SIZES] = 	{"100", "1000", "10K", "100K", "200K", "500K"};

double					results[ARRAY_SIZES][ORDERS_SIZE];
double					resultsRecursive[ARRAY_SIZES][ORDERS_SIZE];

void SelectionSort		(int, int*);
void swap				(int*, int*);
int* buildArray			(int size, ARRAY_ORDER type);
void printArray			(int size, int* array);
int rnd 				(int min, int max);
void printTable			();

void SelectionSortRec	(int size, int* array, int start);
int findmin				(int size, int* array, int minpos, int start);
double Sort 			(int recursive, int order_type, int arraySize, int autoprint);
void AutoSort			(int recursive);

int main(void){
	srand((unsigned int) time(NULL));
	
	int choice = 0;
	int choosenAlg, choosenSize, choosenOrder;
	printf("SelectionSort Algorithm Test\n");
	
	printf("Please choose an option : \
			\n\n\t(1) AutoTest\n\t\tThis will test both SelectionSort and SelectionSortRecursive with all the arrays sizes and orders\
			\n\n\t(2) AutoTest SelectionSort\n\t\tThis will test SelectionSort with all the arrays sizes and orders\
			\n\n\t(3) AutoTest SelectionSortRecursive\n\t\tThis will test SelectionSortRecursive with all the arrays sizes and orders\
			\n\t\tImportant note : the total time of autotests can take up from 30 minutes to 1 hour, choose carefully\
			\n\n\t(4) ManualTest\n\t\tYou choose algorithm, array size and array order\
			\n\n\t(0) Exit");
	printf("\n\nChoice:> ");
	
	do{
		scanf("%d", &choice);
		getchar();
		if(choice < 0 || choice >4)
			printf("\nInvalid Choice, try again\nChoice:>");
	}while(choice < 0 || choice >4);
	
	switch(choice){
		case 1:{
			AutoSort(0);
			AutoSort(1);
			printf("\nSelectionSort Results");
			printTable(0);
			printf("\n\nSelectionSort Recursive Results");
			printTable(1);
			break;
		}
		case 2:{
			AutoSort(0);
			printTable(0);
			break;
		}
		case 3:{
			AutoSort(1);
			printTable(1);
			break;
		}
		case 4:{
			printf("\nPlease select the algorithm : \n\n\t(1) SelectionSort\n\n\t(2) SelectionSort Recursive\n\n");
			printf("Choice:> ");
			do{
				scanf("%d", &choice);
				if(choice < 1 || choice >2)
					printf("\nInvalid Choice, try again\nChoice:>");
			}while(choice < 1 || choice >2);
			choosenAlg = choice;

			printf("\nSelect array size\n");
			printf("\t(1) 100\n\t(2) 1000\n\t(3) 10K\n\t(4) 100K\n\t(5) 200K\n\t(6) 500K\n");
			printf("\n\tImportant note : RecursiveSSort will crash with big arrays (100k+) if you don't change heap settings\n");
			printf("Choice:> ");
			do{
				scanf("%d", &choice);
				if(choice < 1 || choice >6)
					printf("\nInvalid Choice, try again\nChoice:>");
			}while(choice < 1 || choice >6);
			choosenSize = choice;

			printf("\nSelect array order\n");
			printf("\t(1) Ordinato\n\t(2) Quasi Ordinato\n\t(3) Inversamente Ordinato\n\t(4) Casuale\n");
			printf("Choice:> ");
			do{
				scanf("%d", &choice);
				if(choice < 1 || choice >4)
					printf("\nInvalid Choice, try again\nChoice:>");
			}while(choice < 1 || choice >4);
			choosenOrder = choice;
			
			printf("\nOk Starting test...\n\n");
			Sort(choosenAlg == 2, choosenOrder-1, array_sizes[choosenSize-1], 0);
			break;
		}
	}

	printf("\n\nDone! Goodbye");
	return 0;
}
void AutoSort(int recursive){
	printf("Automatically building and sorting arrays starts now...\n");
	
	int array_size = 0;
	for(int i = 0; i < ARRAY_SIZES; i++){
		array_size = array_sizes[i];//set the array size

		printf("\nTesting array of size : %d\n", array_size);
		for(int j = 0 ; j < ORDERS_SIZE; j++){
			if(recursive)
				results[i][j] = Sort(recursive, j, array_size, 0);
			else
				resultsRecursive[i][j] = Sort(recursive, j, array_size, 0);			
		}
	}	
}
double Sort(int recursive, int orderType, int arraySize, int autoprint){
	clock_t start, end;
	double time_elapsed; 
	int *array;
	printf("Building array (%s)...\t", order_names[orderType]);

	array = buildArray(arraySize, orderType);
	if(autoprint){
		printf("\n");
		printArray(arraySize, array);
	}
	printf("Built! Now starting timer and sorting (program may look locked)\n");

	start = clock();
	if(recursive)
		SelectionSortRec(arraySize, array, 0);
	else
		SelectionSort(arraySize, array);
	end = clock();
	time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	//print results (all results will be printed at the end in a table)
	printf("Sorted! Time : %lf for %s and %d elements\n", time_elapsed, order_names[orderType], arraySize);
	if(autoprint){
		printf("\n");
		printArray(arraySize, array);
	}
	return time_elapsed;	
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
		printf("%d  ", array[i]);
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
void SelectionSortRec(int size, int* array, int start){

	if(start >= size -1)
		return;

	int minIndex = findmin(size, array, start, start);
	
	swap(&array[minIndex], &array[start]);
	SelectionSortRec(size, array, start+1);
}
int findmin(int size, int* array, int minpos, int start){

	if(start == size)
		return minpos;
	if(array[start] < array[minpos])
		minpos = start;
	return findmin(size, array, minpos, start+1);
}