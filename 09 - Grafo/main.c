#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICI 20
#define DIM 50
#define NUM_NODI_TEST 11

typedef struct node{
    int vertex_id;
    struct node* link;
}Node;

typedef struct{
    char nome[DIM];
    int  abitanti;
    char nazione[DIM];
    Node* lista_adj;
}Citta;

typedef struct{
    Node* front;
    Node* back;
    int cont;
}Queue;

/* ==============================
 * Funzioni gia' implementate
 * ============================== */
void carica_citta_test(Citta grafo[], int *num_nodi);
void carica_grafo_test_orientato(Citta grafo[], int *num_nodi);
void carica_grafo_test_non_orientato(Citta grafo[], int *num_nodi);


/** ==============================
 * Funzioni da completare
* ================================ */
void aggiungi_nodo                  (Citta grafo[], int *num_nodi);
void linkCity                       (Citta grafo[],int num,int choise);
void crea_arco                      (Citta grafo[], int id_coda, int id_testa);
void stampa_liste_adiacenze         (Citta grafo[], int num_nodi);
void DFS                            (Citta grafo[], int visited[], int start_id);
void BFS                            (Citta grafo[], int visited[], int start_id);
Queue* pushQueue                    (Queue*, int);
bool isEmptyQueue                   (Queue* );
bool isFullQueue                    (Queue* );
int popQueue                        (Queue* );
void cancella_arco_orientato        (Citta grafo[], int id_coda, int id_testa);
void cancella_arco_non_orientato    (Citta grafo[], int id_coda, int id_testa);
void componenti_connesse            (Citta grafo[], int visited[], int num_nodi);
void clearScreen                    ();
//
int main(){
    Citta grafo[MAX_VERTICI];

    int num_nodi = 0,
        choice,
       *pNumNodi = &num_nodi,
        i,
        j,
        id_coda,
        id_testa,
        start_id;

    Node* temp;

    int *visited; //controllo visite

    //Inserire qui le chiamate per testare le varie funzioni e il menu'
    do{
        clearScreen();
        printf("\nGraphs\
                \n\t(1) : Insert city\
                \n\t(2) : Load test cities (oriented graph)\
                \n\t(3) : Load test cities (un-oriented graph)\
                \n\t(4) : Print adjacencies list\
                \n\t(5) : DFS - Depth visit\
                \n\t(6) : BFS - Broad visit\
                \n\t(7) : Remove route (oriented graph)\
                \n\t(8) : Remove route (unoriented graph)\
                \n\t(9) : Print aircover (connected components - unoriented graph)\
                \n\n\t(0) : Exit\
                \n\nChoice : ");

        do{
            scanf("%d",&choice);
            getchar();
            if(choice < 0 || choice > 9)
                printf("\nInvalid choice\nChoice : ");
        }while(choice < 0 || choice > 9);

        switch(choice){
            case 1:{
              aggiungi_nodo(grafo,pNumNodi);
              break;
            }
            case 2:{
              carica_grafo_test_orientato(grafo,pNumNodi);
              printf("\nDone");
              break;
            }
            case 3:{
                carica_grafo_test_non_orientato(grafo,pNumNodi);
                printf("\nDone");
                break;
            }
            case 4:{
                if(num_nodi!=0) {
                    printf("\nAdjacencies list:");
                    stampa_liste_adiacenze(grafo, num_nodi);
                }
                else
                    printf("\nNo routes in list");
                break;
            }
            case 5:{
                printf("\nChoose which city to start from");
                for(i=0;i<num_nodi;i++)
                    printf("%d -> %s\n", i, grafo[i].nome);
                do{
                    printf("\nChoice : ");
                    scanf("%d",&start_id);
                    getchar();
                    if(start_id>=num_nodi)
                        printf("\nCity not found");
                }
                while(start_id>=num_nodi);

                visited = (int*)calloc(sizeof(int)*num_nodi, sizeof(int));

                printf("\nDepth visit:\n");
                DFS(grafo, visited, start_id);

                //free(visited);
                break;
            }
            case 6:{
                printf("\nChoose which city to start from");
                printf("\n");
                for(i=0;i<num_nodi;i++)
                    printf("%d -> %s\n", i, grafo[i].nome);
                do{
                printf("\nChoice : ");
                    scanf("%d",&start_id);
                    getchar();
                    if(start_id>=num_nodi)
                        printf("\nCity not found");
                }
                while(start_id>=num_nodi);

                visited = (int*)calloc(sizeof(int)*(num_nodi), sizeof(int));

                printf("\nBroad visit : ");
                BFS(grafo, visited, start_id);

                free(visited);
                break;
            }
            case 7:{
                printf("\nChoose the city of departure of the section to be deleted");
                printf("\n");
                for(i=0;i<num_nodi;i++)
                    printf("%d -> %s\n",i,grafo[i].nome);
                do{
                    scanf("%d",&id_coda);
                }
                while(id_coda>=num_nodi);
                if(grafo[id_coda].lista_adj!=NULL) {
                    temp=grafo[id_coda].lista_adj;
                    printf("\nChoose the city of arrival of the section to be deleted\n");
                    for (i = 0; grafo[id_coda].lista_adj != NULL; i++) {
                        printf("%d -> %s\n", i, grafo[grafo[id_coda].lista_adj->vertex_id].nome);
                        grafo[id_coda].lista_adj=grafo[id_coda].lista_adj->link;
                    }
                    do {
                        scanf("%d", &id_testa);
                    } while (id_testa >= i);

                    grafo[id_coda].lista_adj=temp;
                    cancella_arco_orientato(grafo, id_coda, id_testa);
                }
                else
                    printf("\nNo route from this city");
                break;
            }
            case 8:{
                printf("\nChoose first city of the route to be deleted :\n");
                for(i=0;i<num_nodi;i++)
                    printf("%d -> %s\n",i,grafo[i].nome);
                do{
                    scanf("%d",&id_coda);
                    if(id_coda >= i)
                        printf("\nNumero errato");
                }
                while(id_coda>=num_nodi);

                if(grafo[id_coda].lista_adj!=NULL) {
                    temp=grafo[id_coda].lista_adj;
                    printf("\nChoose second city of the route to be deleted :\n");
                    for (i = 0; grafo[id_coda].lista_adj != NULL; i++) {
                        printf("%d -> %s\n", i, grafo[grafo[id_coda].lista_adj->vertex_id].nome);
                        grafo[id_coda].lista_adj=grafo[id_coda].lista_adj->link;
                    }
                    do {
                        scanf("%d", &id_testa);
                        if(id_testa >= i)
                            printf("\nWrong number");
                    } while (id_testa >= i);
                    grafo[id_coda].lista_adj=temp;

                    for(j=0;j<id_testa;j++){
                        grafo[id_coda].lista_adj=grafo[id_coda].lista_adj->link;
                    }
                    i=0;
                    while(strcmp(grafo[i].nome,grafo[grafo[id_coda].lista_adj->vertex_id].nome)!=false){
                        i++;
                    }
                    id_testa=i;
                    grafo[id_coda].lista_adj=temp;

                    cancella_arco_non_orientato(grafo, id_coda, id_testa);
                }
                else
                    printf("\nNo route from this city");
                break;
            }
            case 9:{
                visited = (int*)calloc(sizeof(int)*(num_nodi), sizeof(int)); //controllo visite

                printf("\nConnected components : \n");
                componenti_connesse(grafo,visited,num_nodi);

                free(visited);
                break;
            }
       }
       printf("\nPress any key to continue");
       getchar();
    }while(choice!=0);
    printf("\nGoodbye");
    return 0;
}
//
void carica_citta_test(Citta grafo[],int* num){
    //Cagliari
    strcpy(grafo[*num].nome, "Cagliari");
    strcpy(grafo[*num].nazione, "Italia");
    grafo[*num].abitanti = 300000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Zurigo
    strcpy(grafo[*num].nome, "Zurigo");
    strcpy(grafo[*num].nazione, "Svizzera");
    grafo[*num].abitanti = 400000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Lione
    strcpy(grafo[*num].nome, "Lione");
    strcpy(grafo[*num].nazione, "Francia");
    grafo[*num].abitanti = 500000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Genova
    strcpy(grafo[*num].nome, "Genova");
    strcpy(grafo[*num].nazione, "Italia");
    grafo[*num].abitanti = 800000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Roma
    strcpy(grafo[*num].nome, "Roma");
    strcpy(grafo[*num].nazione, "Italia");
    grafo[*num].abitanti = 4000000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //New York
    strcpy(grafo[*num].nome, "New York");
    strcpy(grafo[*num].nazione, "USA");
    grafo[*num].abitanti = 8500000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Bilbao
    strcpy(grafo[*num].nome, "Bilbao");
    strcpy(grafo[*num].nazione, "Spagna");
    grafo[*num].abitanti = 350000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Berlino
    strcpy(grafo[*num].nome, "Berlino");
    strcpy(grafo[*num].nazione, "Germania");
    grafo[*num].abitanti = 3500000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Londra
    strcpy(grafo[*num].nome, "Londra");
    strcpy(grafo[*num].nazione, "Gran Bretagna");
    grafo[*num].abitanti = 8700000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Miami
    strcpy(grafo[*num].nome, "Miami");
    strcpy(grafo[*num].nazione, "USA");
    grafo[*num].abitanti = 450000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;

    //Tokyo
    strcpy(grafo[*num].nome, "Tokyo");
    strcpy(grafo[*num].nazione, "Giappone");
    grafo[*num].abitanti = 13700000;
    grafo[*num].lista_adj = NULL;
    *num=*num+1;
}
void carica_grafo_test_orientato(Citta grafo[], int* num_nodi){
    carica_citta_test(grafo,num_nodi);

    //Creazione archi
    crea_arco(grafo, 0+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 0+*num_nodi-11, 4+*num_nodi-11);

    crea_arco(grafo, 1+*num_nodi-11, 0+*num_nodi-11);
    crea_arco(grafo, 1+*num_nodi-11, 2+*num_nodi-11);

    crea_arco(grafo, 2+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 2+*num_nodi-11, 3+*num_nodi-11);

    crea_arco(grafo, 4+*num_nodi-11, 0+*num_nodi-11);
    crea_arco(grafo, 4+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 4+*num_nodi-11, 5+*num_nodi-11);
    crea_arco(grafo, 4+*num_nodi-11, 6+*num_nodi-11);

    crea_arco(grafo, 5+*num_nodi-11, 1+*num_nodi-11);

    crea_arco(grafo, 6+*num_nodi-11, 7+*num_nodi-11);

    crea_arco(grafo, 8+*num_nodi-11, 9+*num_nodi-11);

    crea_arco(grafo, 9+*num_nodi-11, 8+*num_nodi-11);
    crea_arco(grafo, 9+*num_nodi-11, 10+*num_nodi-11);
}
void carica_grafo_test_non_orientato(Citta grafo [], int* num_nodi){
    carica_citta_test(grafo,num_nodi);

    //Creazione archi
    crea_arco(grafo, 0+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 1+*num_nodi-11, 0+*num_nodi-11);

    crea_arco(grafo, 0+*num_nodi-11, 4+*num_nodi-11);
    crea_arco(grafo, 4+*num_nodi-11, 0+*num_nodi-11);

    crea_arco(grafo, 1+*num_nodi-11, 2+*num_nodi-11);
    crea_arco(grafo, 2+*num_nodi-11, 1+*num_nodi-11);

    crea_arco(grafo, 2+*num_nodi-11, 3+*num_nodi-11);
    crea_arco(grafo, 3+*num_nodi-11, 2+*num_nodi-11);

    crea_arco(grafo, 4+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 1+*num_nodi-11, 4+*num_nodi-11);

    crea_arco(grafo, 4+*num_nodi-11, 5+*num_nodi-11);
    crea_arco(grafo, 5+*num_nodi-11, 4+*num_nodi-11);

    crea_arco(grafo, 4+*num_nodi-11, 6+*num_nodi-11);
    crea_arco(grafo, 6+*num_nodi-11, 4+*num_nodi-11);

    crea_arco(grafo, 5+*num_nodi-11, 1+*num_nodi-11);
    crea_arco(grafo, 1+*num_nodi-11, 5+*num_nodi-11);

    crea_arco(grafo, 6+*num_nodi-11, 7+*num_nodi-11);
    crea_arco(grafo, 7+*num_nodi-11, 6+*num_nodi-11);

    crea_arco(grafo, 8+*num_nodi-11, 9+*num_nodi-11);
    crea_arco(grafo, 9+*num_nodi-11, 8+*num_nodi-11);

    crea_arco(grafo, 9+*num_nodi-11, 10+*num_nodi-11);
    crea_arco(grafo, 10+*num_nodi-11, 9+*num_nodi-11);
}

//student funcs
void aggiungi_nodo(Citta grafo[], int *num_nodi){
    int i, choice, archi;
    if(*num_nodi < NUM_NODI_TEST){
        printf("\nInsert city name : ");
        scanf("%s", grafo[*num_nodi].nome);
        printf("\nInsert nation name : ");
        scanf("%s", grafo[*num_nodi].nazione);
        printf("\nInsert number of residents : ");
        scanf("%d", &grafo[*num_nodi].abitanti);

        grafo[*num_nodi].lista_adj = NULL;
        *num_nodi = *num_nodi+1;

        if(*num_nodi > 1){
            printf("\nInsert numbers of flights from and to city : ");
            scanf("%d", &archi);
            do{
                printf("\nAre the flights :\n\t(0) one way\n\t(1) ound trip : ");
                printf("\nChoice : ");
                scanf("%d", &choice);

                if(choice == 0 || choice == 1)
                    for(i = 0; i < archi; i++)
                        linkCity(grafo,*num_nodi, choice);
                else
                    printf("\nInvalid value, Choice : ");

            }while(choice < 0 || choice > 1);
        }
    }
    else
        printf("\nMax number of nodes reached!");
}
void linkCity(Citta grafo[], int num, int choice){
    char city[DIM];
    int i, match = 0;
    do{
        printf("\nInsert wich city you want to connect : ");
        scanf("%s", city);
        getchar();
        for(i = 0; i <= num; i++)
            if(strcmp(city, grafo[i].nome) == 0)
                match = i +1;
        if(match != 0){
            crea_arco(grafo, num, match -1);
            if(choice != 0) //or choice == 1
                crea_arco(grafo, match-1, num);
        }
        else
        printf("\nCity not found!");

    }while(match == 0);
}
void crea_arco(Citta grafo[], int id_coda, int id_testa){
    Node* node, *temp;
    node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
        exit(-1); //memory full

    node->vertex_id = id_testa;
    node->link = NULL;
    if(grafo[id_coda].lista_adj == NULL)
        grafo[id_coda].lista_adj = node;
    else{
        temp = grafo[id_coda].lista_adj;
        while(grafo[id_coda].lista_adj->link != NULL){
            grafo[id_coda].lista_adj = grafo[id_coda].lista_adj->link;
        }
        grafo[id_coda].lista_adj->link = node;
        grafo[id_coda].lista_adj = temp;
    }
}
void stampa_liste_adiacenze(Citta grafo[], int num_nodi){
    Node *node;
    for(int i = 0; i < num_nodi; i++){
        node = grafo[i].lista_adj;
        printf("\n%s", grafo[i].nome);
        while(grafo[i].lista_adj != NULL){
            printf(" -> %s", grafo[grafo[i].lista_adj->vertex_id].nome);
            grafo[i].lista_adj = grafo[i].lista_adj->link;
        }
        grafo[i].lista_adj = node;
    }
}
void DFS(Citta grafo[], int visited[], int start_id){
    Node * node;
    int id_next;
    printf("%s", grafo[start_id].nome);
    visited[start_id] = true;
    node = grafo[start_id].lista_adj;
    while(node != NULL){
        id_next = node->vertex_id;
        if(visited[id_next] == false){
            printf(", ");
            DFS(grafo, visited, id_next);
        }
        node = node->link;
    }
    free(visited);
}
void BFS(Citta grafo[], int visited[], int start_id){
    Node *node;
    Queue queue, *pQueue;

    printf("%s", grafo[start_id].nome);
    visited[start_id] = true;

    queue.back = NULL;
    queue.front = NULL;
    queue.cont = 0;
    pQueue = &queue;
    pushQueue(pQueue, start_id);

    while(isEmptyQueue(pQueue)){
        if(!visited[node->vertex_id]){
            pushQueue(pQueue, node->vertex_id);
            printf(", %s", grafo[node->vertex_id].nome);
            visited[node->vertex_id] = true;
        }
        node = node->link;
    }
}
_Bool isFullQueue(Queue * queue){
    return (queue->cont == NUM_NODI_TEST) ? true : false;
}
_Bool isEmptyQueue(Queue * queue){
    return (queue->front == NULL && queue->back == NULL) ? true : false;
}
Queue * pushQueue(Queue *queue, int id){
    Node * newNode = NULL;
    if(isFullQueue(queue))
        printf("\nOverflow error!");
        return queue;

    newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
        exit(-1);

    newNode->vertex_id = id;
    newNode->link = NULL;

    queue->back = newNode;
    if(isEmptyQueue(queue))
            queue->front = newNode;
        else
            queue->back->link = newNode;
        queue->cont++;

    return queue;
}
int popQueue(Queue * queue){
    if(isEmptyQueue(queue)){
        printf("\nUnderflow error!");
        exit(-1);
        return -1;
    }

    Node * node;
    int id;
    node = queue->front;
    id = queue->front->vertex_id;

    if(queue->front == queue->back){
        queue->back = NULL;
        queue->front = NULL;
    }
    else
        queue->front = queue->front->link;
    queue->cont--;
    free(node);
    return id;
}
void cancella_arco_orientato(Citta grafo[], int id_coda, int id_testa){
    Node * node = grafo[id_coda].lista_adj,
         * aux;
    int i;

    if(grafo[id_coda].lista_adj->link == NULL){
        for(i = 0; i != id_testa; i++){
            node = grafo[id_coda].lista_adj;
            grafo[id_coda].lista_adj = grafo[id_coda].lista_adj->link;
        }
        aux = grafo[id_coda].lista_adj;

        if(i != false)
            node->link = grafo[id_coda].lista_adj->link;
        else
            grafo[id_coda].lista_adj = grafo[id_coda].lista_adj->link;
        free(aux);
    }else{
        free(grafo[id_coda].lista_adj);
        grafo[id_coda].lista_adj = NULL;
    }
}
void cancella_arco_non_orientato(Citta grafo[], int id_coda, int id_testa){
    Node* node = grafo[id_coda].lista_adj,* aux,* testa=grafo[id_coda].lista_adj;

    /*eliminazione dalla lista di adiacenza della città id_coda*/
    if(grafo[id_coda].lista_adj->link!=NULL) { //se non è l'unica tratta
        while(strcmp(grafo[id_testa].nome , grafo[grafo[id_coda].lista_adj->vertex_id].nome)!= false){
            grafo[id_coda].lista_adj=grafo[id_coda].lista_adj->link;
        }

        aux=grafo[id_coda].lista_adj; //nodo da eliminare
        grafo[id_coda].lista_adj=testa;

        if(strcmp(grafo[id_testa].nome , grafo[grafo[id_coda].lista_adj->vertex_id].nome) != false){ //non si elimina il primo nodo
            node->link=grafo[id_coda].lista_adj->link;
            free(aux);
        }
        else{ //si elimina il primo nodo
            testa=grafo[id_coda].lista_adj->link;
            free(aux);
        }
    }
    else{ /**unica scelta*/
        free(grafo[id_coda].lista_adj);
        grafo[id_coda].lista_adj=NULL;
    }
    grafo[id_coda].lista_adj=testa;

    /*eliminazione dalla lista di adiacenza della città id_testa*/
    testa=grafo[id_testa].lista_adj;
    if(grafo[id_testa].lista_adj->link!=NULL) { //se non è l'unica tratta
        while(strcmp(grafo[id_coda].nome , grafo[grafo[id_testa].lista_adj->vertex_id].nome)!= false){
            grafo[id_coda].lista_adj=grafo[id_coda].lista_adj->link;
        }

        aux=grafo[id_testa].lista_adj; //nodo da eliminare
        grafo[id_testa].lista_adj=testa;

        if(strcmp(grafo[id_coda].nome , grafo[grafo[id_testa].lista_adj->vertex_id].nome) != false){ //non si elimina il primo nodo
            node->link=grafo[id_testa].lista_adj->link;
            free(aux);
        }
        else{ //si elimina il primo nodo
            grafo[id_testa].lista_adj=grafo[id_testa].lista_adj->link;
            free(aux);
        }
        grafo[id_testa].lista_adj=testa;
    }
    else{ /**unica scelta*/
        free(grafo[id_testa].lista_adj);
        grafo[id_testa].lista_adj=NULL;
    }
}

void componenti_connesse(Citta grafo[], int visited[], int num_nodi){
    /** stampa le varie componenti connesse del grafo
    (NB: usare un grafo NON orientato!).
     Hint: Sfruttare una delle visite implementate finché non si sono visitati
     tutti i nodi del grafo.*/
    int current,i,component=0;
    Node* tmp;
    Queue coda,*pCoda;

    for(current=0;current<num_nodi;current++){ //per ogni nodo del grafo
        if(visited[current]==false){ //se non è ancora stato visitato
            /*visito in ampiezza il nodo*/
            component++;
            printf("\nComponenti connesse #%d:\n(%s",component,grafo[current].nome);
            visited[current]=true;

            coda.back=NULL;
            coda.front=NULL;
            coda.cont=0;
            pCoda=&coda;
            pushQueue(pCoda, current);

            while (isEmptyQueue(pCoda)!= true) {
                i = popQueue(pCoda);
                tmp = grafo[i].lista_adj;

                while (tmp != NULL) {
                    if (visited[tmp->vertex_id] == false) {
                        pushQueue(pCoda, tmp->vertex_id);
                        printf(", %s", grafo[tmp->vertex_id].nome);
                        visited[tmp->vertex_id] = true;
                    }
                    tmp = tmp->link;
                }
            }
            printf(")\n");
        }
    }
}

void clearScreen(){
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}
