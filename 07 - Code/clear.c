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


int main()
{
  //inizializzazione pronto soccorso
    ProntoSoccorso ps;
    ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;

    //inizializzazione della Coda con priorita'
    Paziente codaPrio[DIM_HEAP];
    int dim_coda = 0;

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
