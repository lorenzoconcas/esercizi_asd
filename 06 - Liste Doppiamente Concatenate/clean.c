#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_TITLE 50
#define DIM_GENRE 50
#define DIM_NAME 50

//struttura che rappresenta una SERIE TV
struct tvs
{
    char title[DIM_TITLE];
    char genre[DIM_GENRE];
    int num_episodes;
    struct tvs* prev;
    struct tvs* next;
};

typedef struct tvs TVS;

//struttura che rappresenta una PLAYLIST
struct playlist
{
    char name[DIM_NAME];
    TVS* top;
};

typedef struct playlist PlayList;

//funzioni (gia' definite) per l'acquisizione e per la stampa di una serie tv
TVS* acquireTVSeries(); //acquisisce i dati di UNA serie tv chiedendoli all'utente
void printTVSeries(TVS* t); //stampa i dati relativi ad UNA serie tv (passata tramite puntatore)

//prototipi funzioni STUDENTE
//...

int main()
{
  //Creazione di una PLAYLIST. Utilizzare e riempire questa playlist
    PlayList p;
    strcpy(p.name, "Djanny TV Series");
    p.top = NULL;

    //altre chiamate e istruzioni per testare il funzionamento delle funzioni create
    //...


    return 0;
}


/* ---------------------------------------------
* funzioni da NON modificare
* --------------------------------------------*/
TVS* acquireTVSeries()
{
    TVS* new_s = (TVS*)malloc(sizeof(TVS));
    printf("\nInsert title -> ");
    scanf("%[^\n]s", new_s->title);
    getchar();

    printf("Insert genre -> ");
    scanf("%[^\n]s", new_s->genre);
    getchar();

    printf("Insert number of episodes -> ");
    scanf("%d", &(new_s->num_episodes));
    getchar();

    new_s->prev = NULL;
    new_s->next = NULL;

    return new_s;
}

void printTVSeries(TVS* t)
{
    printf("TITLE    :\t %s \n", t->title);
    printf("GENRE    :\t %s \n", t->genre);
    printf("EPISODES :\t %d \n\n", t->num_episodes);
}

/* ---------------------------------------------
* funzioni STUDENTE
* --------------------------------------------*/
//...
