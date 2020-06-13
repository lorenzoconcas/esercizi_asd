#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TARGA 8
#define NUM_PIANI 7

typedef struct{
	char targa[MAX_TARGA];
	int ora;
	int min;
}Auto;

typedef struct nodo{
	Auto info;
	struct nodo *link;
}Nodo;


void carica_auto_test(Nodo* parcheggio[]);
//
void inserisci_auto(Nodo *parcheggio[], Auto);
int hash_code(char targa[]);
void delete_auto(Nodo * parcheggio[], char * targa);
void printAuto(Auto a);
void printParking(Nodo *parcheggio[]);
int countCars(Nodo *parcheggio[]);
int main(void){
    Nodo * parcheggio[NUM_PIANI], *temp;
    for(int i = 0; i < NUM_PIANI; i++)
        parcheggio[i] = NULL;
   
    carica_auto_test(parcheggio);
   
    printParking(parcheggio);
    printf("\nFound %d cars\nDeleting auto", countCars(parcheggio));
    delete_auto(parcheggio, "CA220TO");
    printf("\nDeleted...");
    printParking(parcheggio);
    printf("\nFound %d cars", countCars(parcheggio));
	
    return 0;
}

void carica_auto_test(Nodo* parcheggio[]){
    Auto a0 = {"PI555TA", 12, 15};
    Auto a1 = {"CA220TO", 7, 59};
    Auto a2 = {"EG000AL", 19, 45};
    Auto a3 = {"GO000LE", 15, 20};
    Auto a4 = {"BA220TO", 10, 35};
    Auto a5 = {"AP111LE", 15, 20};
    Auto a6 = {"MI123FT", 18, 40};
    Auto a7 = {"NO985LE", 20, 30};
    Auto a8 = {"GI124CH", 11, 20};
    Auto a9 = {"LO199RE", 9, 30};
    Auto a10 = {"ZA156KF", 7, 10};

    inserisci_auto(parcheggio, a0);
    inserisci_auto(parcheggio, a1);
    inserisci_auto(parcheggio, a2);
    inserisci_auto(parcheggio, a3);
    inserisci_auto(parcheggio, a4);
    inserisci_auto(parcheggio, a5);
    inserisci_auto(parcheggio, a6);
    inserisci_auto(parcheggio, a7);
    inserisci_auto(parcheggio, a8);
    inserisci_auto(parcheggio, a9);
    inserisci_auto(parcheggio, a10);
}
//
int hash_code(char targa[]){
	int i = 0;
	for(int j = 0; j < MAX_TARGA; j++)
		i += (int)targa[j];
	return  i % NUM_PIANI;
}
void inserisci_auto(Nodo * parcheggio[], Auto car){
    int location = hash_code(car.targa);
    Nodo * temp = NULL;
    if(parcheggio[location] == NULL){
        parcheggio[location] = (Nodo*)malloc(sizeof(Nodo));
        temp = parcheggio[location];
    }
    else{
        temp = parcheggio[location];
        while(temp->link != NULL){         
            temp = temp->link;
        }        
        temp->link = (Nodo*)malloc(sizeof(Nodo));         
        temp = temp->link;
    }
    temp->info = car;
    temp->link = NULL;    
}
void printAuto(Auto a){
    printf("Auto : %s %d:%d", a.targa, a.ora, a.min);
}
void delete_auto(Nodo * parcheggio[], char * targa){
    //we need to search the auto first
    int location = hash_code(targa);
    Nodo *node = parcheggio[location], *temp;
    if(strcmp(node->info.targa, targa) == 0){
        node = parcheggio[location]->link;
        free(parcheggio[location]);
        parcheggio[location] = node;
        return;
    }else{//we need to find the previouse node of the car
        while(node->link != NULL){
            if(strcmp(node->link->info.targa, targa) == 0){
                temp = node->link->link;//the node behind the one we want to free
                free(node->link);
                node->link = temp;
                return;
            }
            node = node->link;
        }
    }
  
}
void printParking(Nodo *parcheggio[]){
    Nodo *temp = NULL;
    for(int i = 0; i < NUM_PIANI; i++){
        temp = parcheggio[i];
        printf("\nLevel (%d) ", i);
        if(temp == NULL)
            printf("empty");
        else{
            
            printf(":");
            while(temp != NULL){
                printf("\n\t");
                printAuto(temp->info);
                temp = temp->link;
            }
        }
    }
}
int countCars(Nodo *parcheggio[]){
    Nodo *temp = NULL;
    int total = 0;
    for(int i = 0; i < NUM_PIANI; i++){
        temp = parcheggio[i];
        if(temp != NULL)
            while(temp != NULL){
                temp = temp->link;
                total++;
            }
    }
    return total;
}