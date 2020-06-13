/**
 Implementare:
        - creazione matrice sparsa, chiedendo le triple in input (inserite gli stessi valori della matrice classica, vedi slide)
        - stampa matrice sparsa
        - ricerca di un elemento all'interno della matrice sparsa
        - trasposizione rapida della matrice sparsa.
 */
#include <stdio.h>
#include <stdlib.h>

#define NUMC 15
#define NUMR 10

int numUsedIntegerClassic;  //variabile da usare per contare il numero di interi nella matrice tradizionale
int numUsedIntegerSparse;   //variabile da usare per contare il numero di interi nella matrice sparsa

/**codice mio*/
typedef struct {
    int riga;
    int colonna;
    int valore;
}Matrix;
/************************/

void fill_classic_matrix                (int matrix[][NUMC], int numr, int numc);
void print_classic_matrix               (int matrix[][NUMC], int numr, int numc);
void search_element_in_classic_matrix   (int matrix[][NUMC], int numr, int numc, int numric);
Matrix* fill_dinamic_matrix             (Matrix*);
void print_matr_sparsa                  (Matrix*);
void ricerca_mtr_sprs                   (Matrix*,int);
Matrix* trasp_rapida                    (Matrix*,Matrix*);

int main() {
    int matrix[NUMR][NUMC] = {{0}};
    int numric = 71;

    // Test classic matrix
    fill_classic_matrix(matrix, NUMR, NUMC);
    printf("\n");
    print_classic_matrix(matrix, NUMR, NUMC);
    search_element_in_classic_matrix(matrix, NUMR, NUMC, numric);
    // end

    
    Matrix *triple=NULL;
    Matrix *trasposta=NULL;

    triple=fill_dinamic_matrix(triple);

    print_matr_sparsa(triple); 
    ricerca_mtr_sprs(triple,71);

    trasposta=trasp_rapida(triple,trasposta);

    printf("\n\nMatrice trasposta\n");
    print_matr_sparsa(trasposta); //stampa matrice trasposta

    printf("\n\n\tLocazioni usate:\n"
           "Classica = %d\n"
           "Sparsa=%d",numUsedIntegerClassic,numUsedIntegerSparse);

    free(triple);
    free(trasposta);

    return 0;
}

/**MIE FUNZIONI*/
Matrix* fill_dinamic_matrix(Matrix* triple){
    int i;
    Matrix intestazione;

    printf("\nInserisci numero righe della matrice sparsa:");
    scanf("%d",&intestazione.riga);
    printf("\nInserisci numero colonne della matrice sparsa:");
    scanf("%d",&intestazione.colonna);
    printf("\nInserisci numero di valori da inserire:");
    scanf("%d",&intestazione.valore);

    triple=(Matrix*)malloc((intestazione.valore+1)*sizeof(Matrix)); //oltre al numero dei valori aggiungo l'intestazione

    triple[0].valore=intestazione.valore;
    triple[0].riga=intestazione.riga;
    triple[0].colonna=intestazione.colonna;
    for(i=1;i<=triple[0].valore;i++){
        printf("\nIn quale riga si trova il valore?");
        scanf("%d",&triple[i].riga);
        printf("\nIn quale colonna si trova il valore?");
        scanf("%d",&triple[i].colonna);
        printf("\nQuale valore vuoi inserire?");
        scanf("%d",&triple[i].valore);
    }
    numUsedIntegerSparse=triple[0].valore*3;
    return triple;
}

void print_matr_sparsa(Matrix* triple){
    int i,j,k=1;
    for(i=0;i<triple[0].riga;i++){
        if(triple[k].riga == i){
            if(triple[k].riga != triple[k-1].riga) {
                for (j = 0; j < triple[k].colonna; j++)
                    printf("0\t");
            }
            else{
                for (j = 0; j < (triple[k].colonna-triple[k-1].colonna-1); j++)
                    printf("0\t");
            }
            printf("%d\t", triple[k].valore);
            if (triple[k].riga != triple[k + 1].riga) {
                for (j = (triple[k].colonna + 1); j < triple[0].colonna; j++)
                    printf("0\t");
                printf("\n\n");
            }
                if(k != triple[0].valore && triple[k].riga == triple[k + 1].riga)
                    i--;
            k++;
        }
        else {
            for (j = 0; j < triple[0].colonna; j++)
                printf("0\t");
            printf("\n\n");
        }
    }
}

void ricerca_mtr_sprs(Matrix* arr,int num){
    int i;
    for(i=1; i<=arr[0].valore; i++){
        if(num==arr[i].valore) {
            printf("Elemento %d trovato in posizione (%d, %d).\n", num, arr[i].riga, arr[i].colonna);
            return;
        }
    }
    printf("Elemento non trovato.\n");
}

Matrix* trasp_rapida(Matrix* arr,Matrix* trasp){
    int num_col = arr[0].colonna, num_val = arr[0].valore, i, cur_pos;
    int* termini_riga = NULL,* pos_iniziale = NULL;
    trasp = (Matrix*)malloc((arr[0].valore+1) * sizeof(Matrix)); //oltre al numero dei valori aggiungo l'intestazione
    trasp[0].riga = num_col;
    trasp[0].colonna = arr[0].riga;
    trasp[0].valore = num_val;
    termini_riga = (int*)malloc(trasp[0].riga * sizeof(int));
    pos_iniziale = (int*)malloc(trasp[0].riga * sizeof(int));

    if(num_val > 0){
        //creazione termini_riga
        for(i=0; i < num_col; i++)
            termini_riga[i] = 0;
        for(i=1; i <= num_val; i++)
            termini_riga[arr[i].colonna] = termini_riga[arr[i].colonna] + 1;

        //creazione pos_iniziale
        pos_iniziale[0] = 1;
        for(i=1; i < num_col; i++)
            pos_iniziale[i] = pos_iniziale[i-1] + termini_riga[i-1];

        //trasposizione
        for(i=1; i <= num_val; i++){
            cur_pos = pos_iniziale[arr[i].colonna];
            pos_iniziale[arr[i].colonna] = pos_iniziale[arr[i].colonna] + 1;
            trasp[cur_pos].riga = arr[i].colonna;
            trasp[cur_pos].colonna = arr[i].riga;
            trasp[cur_pos].valore = arr[i].valore;
        }
    }

    free(termini_riga);
    free(pos_iniziale);
    return trasp;
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