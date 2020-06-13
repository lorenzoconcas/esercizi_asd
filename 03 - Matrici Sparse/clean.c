#include <stdio.h>
#include <stdlib.h>

#define NUMC 15
#define NUMR 10

int numUsedIntegerClassic; 
int numUsedIntegerSparse;

void print_classic_matrix(int matrix[][NUMC], int numr, int numc);
void fill_classic_matrix(int matrix[][NUMC], int numr, int numc);
void search_element_in_classic_matrix(int matrix[][NUMC], int numr, int numc, int numric);

int main(){
    int matrix[NUMR][NUMC] = {{0}};
    int numric = 71;  
}

// Funzione che riempie (con i valori dell'esempio presenti nelle slide della lezione 3) la matrice classica passata in ingresso
void fill_classic_matrix(int matrix[][NUMC], int numr, int numc) {
    numUsedIntegerClassic=numr*numc;
    matrix[1][0] = 71;
    matrix[2][14] = 99;
    matrix[3][11] = 53;
    matrix[4][7] = 95;
    matrix[6][14] = 39;
    matrix[8][1] = 27;
    matrix[9][14] = 14;
}

// Funzione che stampa a video una matrice classica
void print_classic_matrix(int matrix[][NUMC], int numr, int numc) {
    int i, j = 0;
    for(i=0; i<numr; i++)
    {
        for(j=0; j<numc; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

}

// Funzione che implementa la ricerca di un elemento (numric) in una matrice classica
void search_element_in_classic_matrix(int matrix[][NUMC], int numr, int numc, int numric) {
    int i, j = 0;
    for (i = 0; i < numr; i++) {
        for (j = 0; j < numc; j++) {
            if (matrix[i][j] == numric) {
                printf("Elemento %d trovato in posizione (%d, %d).\n", numric, i, j);
                return;
            }
        }
    }
    printf("Elemento non trovato.\n");
}