#include <stdio.h>
#include <stdlib.h>

#define DIM_NOME 50
#define DIM_HEAP 50

//stuttura che rappresenta un Pronto soccorso
typedef struct{
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
//funzioni studente
char     codeName[][7]   =  {"BIANCO", "VERDE", "GIALLO", "ROSSO"} ;
int      priorita           (Paziente p1, Paziente p2);
void     insert_heap        (Paziente * coda, Paziente p, int *size);
Paziente delete_heap        (Paziente heap[], int* dim);
void     print_heap         (Paziente *heap, int size);
void     printPaziente      (Paziente p);
void     clearScreen        ();

int main()
{
  //inizializzazione pronto soccorso
    ProntoSoccorso ps;
    ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;

    //inizializzazione della Coda con priorita'
    Paziente codaPrio[DIM_HEAP];

    int heap_size = 0;
    int *heap_size_pointer = &heap_size;
    
    int choice = -1;
    do{
        clearScreen();
        printf("\nEmergency Department");
        printf("\nThere area currently (%d) patients\n", heap_size);
        printf("\n\t(1) Insert patient \
                \n\t(2) Print patients order\
                \n\t(3) Remove next patient\
                \n\n\t(0) Exit");
        do{
            printf("\n\nChoice : ");
            scanf("%d", &choice);
            getchar();
            if(choice < 0 || choice > 3)
                printf("\nInvalid choice\nChoice : ");
        }while(choice < 0 || choice > 3);

        switch(choice){
            case 1:{
                insert_heap(codaPrio, nuovoPaziente(&ps), heap_size_pointer);
                break;
            }
            case 2:{
                printf("\nPatients in queue (heap)\n");
                print_heap(codaPrio, heap_size);
                break;
            }
            case 3:{
                if(heap_size != 0){
                    printf("Removing patient");
                    Paziente paziente = delete_heap(codaPrio, heap_size_pointer);
                    printPaziente(paziente);
                    printf("\n");
                    printf("\nRemaining patients : ");
                    print_heap(codaPrio, heap_size);
                }
                else printf("\nEmpty heap");
                break;
            }
        }
        if(choice != 0){
            printf("\nPress any key to continue");
            getchar();
        }
        
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
    
    printPaziente(coda[i]);
   
}
Paziente delete_heap(Paziente heap[], int* dim){
    Paziente item=heap[1], temp=heap[*dim];
    int padre=1,figlio=2;
    *dim=*dim-1;

    while(figlio <= *dim){
        if (figlio < *dim && priorita(heap[figlio],heap[figlio + 1])==0)
            figlio = figlio + 1;
        if (priorita(temp,heap[figlio]))
            break;

        heap[padre] = heap[figlio];
        padre = figlio;
        figlio = 2 * figlio;
    }
    heap[padre] = temp;
    return item;
}

void print_heap(Paziente *heap, int size){
    for(int i = 1; i <= size; i++){
        printPaziente(heap[i]);
        printf("\n");
    }
}
void printPaziente(Paziente p){
    printf("\nNome: %s\nCodice: %s\nOrdine d'arrivo: %u", p.nome, codeName[p.codice], p.ordine);
}

void clearScreen(){
#ifdef _WIN32
        system("cls");
#else 
        system("clear");
#endif
}