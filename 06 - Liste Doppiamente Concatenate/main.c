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
void insertTVSeries     (PlayList *pl, TVS * t);
TVS* findTVSeries       (PlayList *pl, char * title);
void deleteTVSeries     (PlayList *pl, TVS* t);
void printPlaylist      (PlayList * pl);
TVS* nextTVSeries       (TVS* t);
TVS* prevTVSeries       (TVS* t);
void mergePlayList      (PlayList *plA,PlayList * plB, PlayList *plC);
void editTVSeries       (PlayList *pl);
void reorder            (TVS* first, TVS* change);
void clearScreen        ();

int main(){
  //Creazione di una PLAYLIST. Utilizzare e riempire questa playlist
    PlayList p;
    strcpy(p.name, "Djanny TV Series");
    p.top = NULL;

    //altre chiamate e istruzioni per testare il funzionamento delle funzioni create
    //...
   
    int choice = 0;
    int cycle = 1;
    TVS * serie = (TVS*)malloc(sizeof(TVS));
    while(cycle){
        clearScreen();
        printf("Double linked lists");
        printf("\nPlease choose an option\n");
        printf("\n\t(1) Insert a new TV Series\
                \n\t(2) Find a TV Series \
                \n\t(3) Edit a TV Series \
                \n\t(4) Delete a TV Series \
                \n\t(5) Print entire playlist \
                \n\t(6) Browse TV series \
                \n\t(7) Merge two playlist \
                \n\t(8) Print playlist fusion\
                \n\n\t(0) Exit");
        printf("\n\nChoice : ");
        do{
            scanf("%d", &choice);
            getchar();
            if(choice < 0 || choice > 8)
                printf("Invalid choice\nChoice : ");
        }while(choice < 0 || choice > 8);
       

        switch(choice){
            case 1:{
                serie =acquireTVSeries();
                insertTVSeries(&p, serie);
                break;
            }
            case 2:{
                printf("\nEnter name of TV Series : ");
                char name[DIM_NAME];
                scanf("%s", name);
                getchar();
                printf("%s", name);
                serie = findTVSeries(&p, name);
                if(serie == NULL)
                    printf("\nTV Series not found");
                else 
                    printTVSeries(serie);
                break;
            }
            case 3:{
                editTVSeries(&p);
                break;
            }
            case 4:{
                printf("\nEnter name of TV Series to be deleted : ");
                char name[DIM_NAME];
                scanf("%s", name);
                getchar();
                printf("%s", name); 
                TVS * tvs = findTVSeries(&p, name);
                if(tvs == NULL)
                    printf("\nTV Series not found");
                else             
                    deleteTVSeries(&p, tvs);
                break;
            }
            case 5:{
                printPlaylist(&p);
                break;
            }
            case 6:{
				int cycle = 1;
				serie = NULL;				
				while(cycle){
					clearScreen();
					printf("Browsing playlists \
						\n\t(1) Next playlist \
						\n\t(2) Previous playlist \
						\n\n\t(0) Main Menu\
						\n\nChoice : ");
				
					do{
						scanf("%d", &choice);
						getchar();
						if(choice < 0 || choice > 2)
							printf("\nInvalid choice, retry\nChoice : ");
					}while(choice < 0 || choice > 2);
					
					switch(choice){
						case 0:{
							cycle = 0;
							break;
						}
						case 1:{
							if(serie == NULL)
								serie = p.top;
							else
								serie = nextTVSeries(serie);
							if(serie == NULL)
								printf("\nYou reached the end");
							else
								printTVSeries(serie);
							break;
						}
						case 2:{
							if(serie == NULL)
								serie = p.top;
							else
								serie = prevTVSeries(serie);
							if(serie == NULL)
								printf("\nYou reached the end");
							else
								printTVSeries(serie);
							break;
						}
					}
					if(choice != 0){
						printf("\nPress any key to continue");
						getchar();
					}
				}
				
				break;
			}
            case 0:{
                cycle = 0;
                printf("\nGoodbye");
                exit(0);
            }
                
        }
        printf("\nPress any key to continue");
        getchar();
    }


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

void reorder(TVS* first, TVS* change){
    TVS* tmp=change;

    if(first->next!=NULL) {//caso in cui la lista non sia composta da un singolo nodo
        /*riallaccio la lista*/
        if (change->prev != NULL) //caso in cui non sia la testa
            change->prev->next = change->next;
        else
            change->next->prev = NULL;

        if (change->next != NULL) //caso in cui non sia la coda
            change->next->prev = change->prev;
        else
            change->prev->next = NULL;

        if (strcmp(first->title, tmp->title) < 0) {
            while (first->next != NULL && strcmp(first->next->title, tmp->title) < 0) { //scorre la lista in avanti sino a trovare la corrispondente posizione
                first = first->next;
            }
            tmp->next = first->next;
            tmp->prev = first;
            first->next->prev = tmp;
            first->next = tmp;
        }
        else { //caso in cui il nodo modificato debba essere inserito in testa
            tmp->next = first;
            first->prev = tmp;
            first = tmp;
        }
    }
}

void insertTVSeries(PlayList *pl, TVS * t){
    TVS* newNode = t;
    //se il nodo iniziale è vuoto la playlist è vuota e inseriamo la serie tv all'inizio
    if(pl->top == NULL){
        pl->top = (TVS*)malloc(sizeof(TVS));
        pl->top = t;
        pl->top->next = NULL;
        return;
    }

    TVS * tmpPrev = NULL, \
        * tmpNext = pl->top;

    while(tmpNext != NULL && strcmp(tmpNext->title, t->title) == 0){
        tmpPrev = tmpNext;
        tmpNext = tmpPrev->next;
    }

    if(tmpNext == NULL){ //dobbiamo inserire in coda 
      newNode->prev = tmpPrev;
      newNode->next = NULL;
      if(tmpPrev != NULL)
        tmpPrev->next = newNode;
    }
    else if(tmpPrev == NULL){//in testa
        newNode->next = tmpNext;
        tmpNext->prev = newNode;
        pl->top = newNode;
    }else{
        newNode->next = tmpNext;
        newNode->prev = tmpPrev;
        tmpPrev->next = newNode;
        tmpNext->prev = newNode;
    }
}

TVS* findTVSeries(PlayList *pl, char * title){
    TVS* temp = pl->top;
    while(temp != NULL){
        if(strcmp(temp->title, title) == 0)
            return temp;
        temp = temp->next;
    }
    return temp;

}
void deleteTVSeries(PlayList *pl, TVS* t){
    TVS* temp = pl->top, * head = pl->top;
    TVS *before, *after;

    if (t == NULL) return;
    
    //cancellazione della testa
    if(strcmp(temp->title, t->title) == 0){
        pl->top = pl->top->next;
        if(pl->top != NULL)
            pl->top->prev = NULL;
        free(temp);
        return;
    }
    //se non è la testa cerco il nodo corretto con un while
    while (strcmp(pl->top->title, t->title) != 0)
        pl->top = pl->top->next;

    temp =pl->top;
    pl->top->prev->next=temp->next; //riaggancio la lista

    if(pl->top->next!=NULL) {
        pl->top->next->prev = temp->prev; //aggancio il nodo successivo (se esiste) a quello precedente
    }

    free(temp);
    pl->top=head; //recupero l'inizio della lista
}
void printPlaylist(PlayList * pl){
    TVS* temp = pl->top;
    if(temp == NULL){
        printf("\nPlaylist is empty");
        return;
    }
    int i = 1;
    printf("Playlist content : \n");
    while(temp != NULL){      
        printf("%d\n" , i);
        printTVSeries(temp);
        temp = temp->next;
        i++;
    }
}
TVS* nextTVSeries(TVS* t){
    return t->next;
}
TVS* prevTVSeries(TVS* t){
    return t->prev;
}
void mergePlayList(PlayList *plA,PlayList * plB, PlayList *plC){
    TVS* headC = plC->top, \
        *headA = plA->top, \
        *headB = plB->top;
        
    while(headC != NULL){
        headC = headC->next;
    }
    headC->next = headA;
    while(headC != NULL){
        headC = headC->next;
    }
     headC->next = headB;
}
void editTVSeries(PlayList *pl){
    TVS *serie = NULL;
    char serieName[DIM_NAME];
    printf("\nInsert series name : ");
    scanf("%s", serieName);
    int choice = 0;
    serie = findTVSeries(pl, serieName);
    if(serie == NULL)
        printf("\nSeries not found, returning to main menu");
    else{
        do{
        clearScreen();
        printTVSeries(serie);
        printf("\nWhat do you want to edit?\n \
                \n\t(1) Title \
                \n\t(2) Genre \
                \n\t(3) Episodes\
                \n\n\t(4) Exit to Main Menu \
                \n\nChoice : ");
                do{
                    scanf("%d", &choice);
                    getchar();
                    if(choice < 1 || choice > 4)
                        printf("\nInvalid choice\nChoice : ");
                }while(choice < 1 || choice > 4);
                switch(choice){
                    case 1:{
                        printf("\nPlease enter a new title : ");
                        scanf("%s", serie->title);
                        getchar();
                        printf("\nNew title : %s\n", serie->title);
                        reorder(pl->top, serie);
                        break;
                    }
                    case 2:{
                        printf("\nPlease enter a new genre : ");
                        scanf("%s", serie->genre);
                        getchar();
                        printf("\nNew genre : %s\n", serie->genre);
                        break;
                    }
                    case 3:{
                        printf("\nPlease enter a new episode count : ");
                        scanf("%d", &serie->num_episodes);
                        getchar();
                        printf("\nSeries contains now : %d episode(s)\n", serie->num_episodes);
                        break;
                    }

                }
                if(choice != 4){
                    printf("Press any key to continue");
                    getchar();
                }
                
        }while(choice != 4);
    }
}
void clearScreen(){
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif
}
