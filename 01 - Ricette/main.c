/*Creare e popolare un array distrutture che rappresentano delle ricette.
• Una Ricetta dovrà essere così definita:

typedef struct {
 	char nome[DIM_NOME];	//Nome rappresenta il titolo della ricetta;
  	double tempo; 			//Tempo rappresenta i minuti necessari per la sua realizzazione
	int difficolta; 		//Difficoltà è rappresentata da un intero compreso tra 1 (molto semplice) e 10 (estremamente complessa).
 } Ricetta;
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DIM_NOME 33
#define MAX_RICETTE 10000

typedef struct {
 	char nome[DIM_NOME];	
 	double tempo;
	int difficolta; //MIN 1 MAX 10
} Ricetta;

Ricetta ricette[MAX_RICETTE]; /* = {
	{"Vellutata di carne", 20.0, 8},
	{"Frittata di pesce", 25.0, 5},
	{"Insalata di pasta", 6.0, 1},
};*/

void SelectionSort();
int compare(Ricetta ricetta1, Ricetta ricetta2);
void swap(Ricetta *ricetta1, Ricetta *ricetta2);
void PrintRicette();
void PrintRicetta(Ricetta *ricetta);
int rnd 			(int min, int max);
void BuildRicette();

int main(void){
	srand((unsigned int) time(NULL));
	clock_t start, end;
	double time_elapsed; 
	printf("MasterSort - Il SelectionSort per le ricette\n");

	printf("\nPremi un tasto qualsiasi per avviare il test");
	getchar();
	BuildRicette();
	PrintRicette();
			
	printf("\nSorting\n\n");

	start = clock();
	SelectionSort();
	end = clock();
	time_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

	PrintRicette();
	printf("\nFatto! Tempo : %.3lf s per %d elementi\n", time_elapsed, MAX_RICETTE);
}

void SelectionSort(){
	int i = 0, j = 0, min = 0;
	for(i = 0; i < MAX_RICETTE - 1; i++){
		min = i;
		for(j = i + 1; j < MAX_RICETTE; j++)
			if(compare(ricette[min],ricette[j]))
				min = j;
		
		swap(&ricette[min], &ricette[i]);		
	}
}

int compare(Ricetta ricetta1, Ricetta ricetta2){
	if(ricetta1.tempo < ricetta2.tempo)
		return 0;
	if((ricetta1.tempo == ricetta2.tempo) && (ricetta1.difficolta < ricetta2.difficolta))
		return 0;
	return 1;
}
//must pass arguments with & before, even with arrays
void swap(Ricetta *ricetta1, Ricetta *ricetta2){	
	Ricetta temp;
    temp=*ricetta1;
    *ricetta1=*ricetta2;
    *ricetta2=temp;  
}
void PrintRicette(){
	for(int i = 0; i < MAX_RICETTE; i++){
		PrintRicetta(&ricette[i]);
	}
}
void PrintRicetta(Ricetta * ricetta){
	//printf("###Ricetta###\n");
	printf("Nome : %s\tTempo : %lf\tDiff : %d\n", 
		ricetta->nome, ricetta->tempo, ricetta->difficolta);	
}

void BuildRicette(){
	char preparazioni[][10] = {"Vellutata", "Frittata","Insalata", "Bollito", "Frullato", "Grigliata"}; //6
	char prodotti	 [][8]	= {"carne ", "pasta ", "verdura", "pesce ", "gelato", "elicriso"}; //5

	for(int i = 0; i<MAX_RICETTE; i++){
		strcpy(ricette[i].nome,preparazioni[rnd(0, 5)]);
		strcat(ricette[i].nome," di ");
		strcat(ricette[i].nome,prodotti[rnd(0, 4)]);
		ricette[i].tempo = rnd(1, 50);
		ricette[i].difficolta = rnd(1, 10);
	}
}
int rnd(int min, int max){
	return  min + rand()%(max-min+1);
}