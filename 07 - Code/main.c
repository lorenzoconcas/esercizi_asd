#include <stdio.h>
#include <stdlib.h>

#define DIM_NOME 50
#define DIM_HEAP 50

//stuttura che rappresenta un Pronto soccorso
typedef struct
{
    int numeroB;
    int numeroG;
    int numeroV;
    int numeroR;
} ProntoSoccorso;

//enumerazione che rappresenta i codici del pronto soccorso
typedef enum {BIANCO, VERDE, GIALLO, ROSSO} Codice;

//struttura che rappresenta un Paziente
typedef struct
{
    char nome[DIM_NOME];
    Codice codice;
    int ordine;
}Paziente;

//funzione che chiede i dati relativi ad un nuovo paziente e lo restituisce (con la priorita' gia' impostata) pronto per essere inserito nella coda con priorita' (heap)
Paziente nuovoPaziente(ProntoSoccorso *ps);
//
char codeName[][6] = {"BIANCO", "VERDE", "GIALLO", "ROSSO"} ;
int priorita(Paziente p1, Paziente p2);
void insert_heap(Paziente * coda, Paziente p, int *size);
void delete_heap();
void print_heap(Paziente *heap, int size);
void clearScreen();
int main()
{
  //inizializzazione pronto soccorso
    ProntoSoccorso ps;
    ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;

    //inizializzazione della Coda con priorita'
    Paziente codaPrio[DIM_HEAP];
    int dim_coda = 0;
   
    int choice = -1;
    do{
        clearScreen();
        printf("\nEmergency Department");
        printf("\n\t(1) Insert patient \
                \n\t(2) Print patients order\
                \n\t(3) Remove patient\
                \n\n\t(0) Exit");
        do{
            printf("\nChoice : ");
            scanf("%d", &choice);
            getchar();
            if(choice < 0 || choice > 3)
                printf("\nInvalid choice\nChoice : ");
        }while(choice < 0 || choice > 3);

        switch(choice){
            case 1:{
                insert_heap(codaPrio, nuovoPaziente(&ps), &dim_coda);
                break;
            }
            case 2:{
                print_heap(codaPrio, dim_coda);
                break;
            }
            case 3:{
                break;
            }
        }
        printf("\nPress any key to continue");
        getchar();
    }while(choice != 0);
    return 0;
}

Paziente nuovoPaziente(ProntoSoccorso *ps)
{
    Paziente p;

    printf("\nNome paziente -> ");
    scanf("%[^\n]s", p.nome);
    getchar();

    do
    {
        printf("\nCodice paziente (0 = bianco, 1 = verde, 2 = giallo, 3 = rosso)-> ");
        scanf("%u", &p.codice);
        getchar();

        if(p.codice < BIANCO || p.codice > ROSSO)
            printf("\nCodice non valido");
    }while(p.codice < BIANCO || p.codice > ROSSO);

    if(p.codice == BIANCO)
    {
        ps->numeroB++;
        p.ordine = ps->numeroB;
    }
    else if(p.codice == GIALLO)
    {
        ps->numeroG++;
        p.ordine = ps->numeroG;

    }
    else if (p.codice == VERDE)
    {
        ps->numeroV++;
        p.ordine = ps->numeroV;
    }
    else
    {
        ps->numeroR++;
        p.ordine = ps->numeroR;
    }

    return p;
}

int priorita(Paziente p1, Paziente p2){
   /* if(p1.codice > p2.codice)
        return 1;
    else if(p1.codice == p2.codice && p1.ordine < p2.ordine)
            return 1;*/
    // return 0;
    return ((p1.codice > p2.codice) || \
           (p1.codice == p2.codice && p1.ordine < p2.ordine))\
           ? 1 : 0;

   
}
void insert_heap(Paziente * coda, Paziente p, int *size){
    if(*size == DIM_HEAP){
        printf("\nHeap Full");
        return;
    }
    *size = *size+1; //cause we can't size++
    int i = *size;
    while(i != 1 && priorita(p, coda[i/2])){
        coda[i] = coda[i/2];
        i /= 2;
    }
    coda[i] = p;
}
void delete_heap(){}
void print_heap(Paziente *heap, int size){
  for(int i = 0; i < size; i++)
    printf("\nNome: %s\nCodice: %s\nOrdine d'arrivo: %d", heap[i].nome, heap[i].codice,heap[i].ordine);
}
void clearScreen(){
#ifdef _WIN32
        system("cls");
#else 
        system("clear");
#endif
}