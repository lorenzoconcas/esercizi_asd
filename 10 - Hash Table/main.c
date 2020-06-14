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


void carica_auto_test               (Nodo* parcheggio[]);
//funzioni studente
void inserisci_auto                 (Nodo *parcheggio[], Auto);
int  hash_code                      (char targa[]);
void delete_auto                    (Nodo * parcheggio[], char * targa);
void printAuto                      (Auto a);
void printParking                   (Nodo *parcheggio[]);
void printLevel                     (Nodo *parcheggio, int level);
int  countCars                      (Nodo *parcheggio[]);
Auto find_auto                      (Nodo * parcheggio[], char * targa);
void clearScreen                    ();

int main(void){
    Nodo * parcheggio[NUM_PIANI], *temp;
    for(int i = 0; i < NUM_PIANI; i++)
        parcheggio[i] = NULL;
   
    int choice = -1;

    do{
        clearScreen();      
        printf("Hash Table\
                \n\t(1) : Insert Car\
                \n\t(2) : Search Car\
                \n\t(3) : Print parking\
                \n\t(4) : Print level\
                \n\t(5) : Load Test\
                \n\t(6) : Remove Car\
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
                Auto car;
                printf("\nInsert car plate number : ");
                scanf("%s", car.targa);
                getchar();
                printf("\nInsert time of arrival\
                        \nHour : ");
                scanf("%d", &car.ora);
                getchar();
                printf("Minute : ");
                scanf("%d", &car.min);
                getchar();
                printf("\nInserting car in level %d", hash_code(car.targa));
                inserisci_auto(parcheggio, car);
                break;
            }
            case 2:{   
                char plate[MAX_TARGA];
                printf("\nInsert car plate number : ");
                scanf("%s", plate);
                getchar();
                Auto car = find_auto(parcheggio, plate);
                if(strcmp(car.targa, plate) == 0){
                    printf("Car found at level %d", hash_code(plate));
                    printAuto(car);
                }
                break;
            }
            case 3:{
                printf("\nAuto in parking : ");
                printParking(parcheggio);
                break;
            }
            case 4:{
                int level = 0;
                printf("\nPlease choose a level (0 - %d) : ", NUM_PIANI);
                do{
                    scanf("%d", &level);
                    getchar();
                    if(level < 0 || level > NUM_PIANI)
                        printf("\nInvalid choice, try again : ");
                }while(level < 0 || level > NUM_PIANI);
                printLevel(parcheggio[level], level);
                break;
            }
            case 5:{
                printf("\nInserting test cars...");
                carica_auto_test(parcheggio);
                printf("\nDone!");
                break;
            }
            case 6:{
                char plate[MAX_TARGA];
                printf("\nInsert car plate number : ");
                scanf("%s", plate);
                getchar();
                Auto car = find_auto(parcheggio, plate);
                if(strcmp(car.targa, plate) == 0){
                   delete_auto(parcheggio, plate);
                   printf("\nCar deleted successfully");
                }
                else printf("\nCar not found");
                break;
            }
        }
        if(choice != 0){
            printf("\nPress any key to continue");
            getchar();
        }
    }while(choice != 0);
   
	printf("\nDone Goodbye");
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

//funzioni studente
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
    printf("Car : %s (arrived at %d:%d)", a.targa, a.ora, a.min);
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
    }else{//we need to find the previous node of the car
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
Auto find_auto(Nodo * parcheggio[], char * targa){
    //we need to search the auto first
    int location = hash_code(targa);
    Nodo *node = parcheggio[location], *temp;
    if(strcmp(node->info.targa, targa) == 0){
        return node->info;      
    }else{//we need to find the previous node of the car
        while(node->link != NULL){
           if(strcmp(node->info.targa, targa) == 0)
                return node->info;      
            node = node->link;
        }
    }      
}
void printParking(Nodo *parcheggio[]){
    Nodo *temp = NULL;
    for(int i = 0; i < NUM_PIANI; i++)
        printLevel(parcheggio[i], i);    
}

void printLevel(Nodo *parcheggio, int level){
    printf("\nLevel (%d) ", level);
    if(parcheggio == NULL)
        printf(" is empty");
    else{
        printf(":");
        while(parcheggio != NULL){
            printf("\n\t");
            printAuto(parcheggio->info);
            parcheggio = parcheggio->link;
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

void clearScreen(){
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}
