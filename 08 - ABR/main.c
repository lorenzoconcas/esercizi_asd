#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_NOME 50
#define NUM_TEST 15

typedef struct{
    char nome[DIM_NOME];
    float gradi;
    int bottiglie;
} Birra;

typedef struct nodo{
    Birra key;
    struct nodo *parent;
    struct nodo *left;
    struct nodo *right;
} Nodo;

/** -------------------------------
 Funzioni gia' implementate:
 ------------------------------- */
Birra acquisisci_birra();
void stampa_birra(Birra b);

Nodo* crea_nodo(Birra b);
Nodo* carica_test();

/** -------------------------------
 Funzioni da implementare:
 ------------------------------- */
Nodo* insert_nodo   (Nodo* root, Nodo* new_node);
void inorder        (Nodo* root);
void preorder       (Nodo* root);
void postorder      (Nodo* root);
int profondita      (Nodo* root);
int max             (int v1, int v2);
Nodo* ricerca       (Nodo* root, char* nome_birra);
Nodo* abr_min       (Nodo* root);
Nodo* abr_max       (Nodo* root);
Nodo* abr_succ      (Nodo* x);
Nodo* abr_pred      (Nodo* x);
Nodo* delete_node   (Nodo* root, Nodo* nodo);
void clearScreen    ();

int main(){
    Nodo *root = NULL; // Radice dell'ABR

    Nodo * node;
    int choice = -1;
    do{
        clearScreen();
        printf("ABR");
        printf("\n\t(1)  Insert new beer \
                \n\t(2)  Remove a beer \
                \n\t(3)  Load test beers (empty abr)\
                \n\t(4)  Search a beer\
                \n\t(5)  Search a minimum\
                \n\t(6)  Search a maximum\
                \n\t(7)  Search previus\
                \n\t(8)  Search next\
                \n\t(9)  ABR Depth\
                \n\t(10) Inorder visit\
                \n\t(11) Preorder visit\
                \n\t(12) Postorder visit\
                \n\n\t(0)  Exit");
        printf("\n\nChoice : ");
        do{
            scanf("%d", &choice);
            getchar();
            if(choice < 0 || choice > 12)
                printf("\nInvalid choice\nChoice : ");
        }while(choice < 0 || choice > 12);

        switch(choice){
            case 1:{
                Birra beer = acquisisci_birra();
                node = crea_nodo(beer);
                root = insert_nodo(root, node);
                break;
            }
            case 2:{
                char beerName[DIM_NOME];
                printf("\nType a beer name : ");
                scanf("%s", beerName);
                getchar();
                node = ricerca(root, beerName);
                if(node == NULL)
                    printf("\nBeer not found");
                else{
                    root = delete_node(root, node);
                    printf("\nRemoved");
                }
                break;
            }
            case 3:{
                root = carica_test();
                printf("\nTest loaded");
                break;
            }
            case 4:{
                char beerName[DIM_NOME];
                printf("\nType a beer name : ");
                scanf("%s", beerName);
                getchar();
                node = ricerca(root, beerName);
                if(node != NULL)
                    stampa_birra(node->key);
                else
                    printf("\nBeer not found");
                break;
            }
            case 5:{
                node = abr_min(root);
                stampa_birra(node->key);
                break;
            }
            case 6:{
                node = abr_max(root);
                stampa_birra(node->key);
                break;
            }
            case 7:{
                if(node == NULL)
                    printf("\nSearch a beer first");
                else{
                    node = abr_pred(node);
                    stampa_birra(node->key);
                }
                break;
            }
            case 8:{
                 if(node == NULL)
                    printf("\nSearch a beer first");
                else{
                    node = abr_succ(node);
                    stampa_birra(node->key);
                }
                break;
            }
            case 9:{
                if(root == NULL)
                    printf("\nABR empty");
                else
                    printf("\nABR depth : %d", profondita(root));
                break;
            }
            case 10:{
                inorder(root);
                break;
            }
            case 11:{
                preorder(root);
                break;
            }
            case 12:{
                postorder(root);
                break;
            }
        }

        if(choice != 0){
            printf("\nPress any key to continue");
            getchar();
        }
    }while(choice != 0);
    printf("\nGoodbye");
    return 0;
}

/** -------------------------------
 Funzioni gia' implementate (NON MODIFICARE):
 ------------------------------- */
Birra acquisisci_birra(){
    Birra b;
    getchar();

    printf("nome: ");
    scanf("%[^\n]s", b.nome);
    getchar();

    printf("gradi: ");
    scanf("%f", &b.gradi);

    printf("bottiglie: ");
    scanf("%d", &b.bottiglie);

    return b;
}

void stampa_birra(Birra b){
    printf("--------------------- \n");
    printf("nome:  %s \n", b.nome);
    printf("gradi: %.1f \n", b.gradi);
    printf("bottiglie: %d \n", b.bottiglie);
    printf("--------------------- \n");
}

Nodo* crea_nodo(Birra b){
    Nodo* new_node = (Nodo*)malloc(sizeof(Nodo));
    if(new_node != NULL)
    {
        new_node->key = b;
        new_node->parent = NULL;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

Nodo* carica_test(){
    Nodo *root = NULL;
    int i;
    Birra elenco[NUM_TEST] = {{"Ichnusa", 4.7, 3}, {"Founders", 5.7, 15}, {"Peroni", 4.7, 2},
                              {"San Miguel", 3.2, 4}, {"Miller", 4.7, 7}, {"Guinnes", 4.2, 1},
                              {"Best Brau", 4.7, 12}, {"Barley", 5.0, 7}, {"Chouffe", 8.0, 12},
                              {"Franziskaner", 5, 10}, {"Heineken", 5.0, 7}, {"Kwak", 8.0, 14},
                              {"Paulaner", 5.5, 10}, {"Rubiu", 4.5, 10}, {"Tuborg", 5.0, 3}};


    for(i = 0; i < NUM_TEST; i++){
        Nodo *new_birra = crea_nodo(elenco[i]);
        root = insert_nodo(root, new_birra);
    }

    printf("\nTest caricato correttamente!\n");
    return root;
}

/** -------------------------------
 Funzioni da implementare:
 ------------------------------- */

int profondita(Nodo * root){
    if(root == NULL) //albero  vuoto
        return 0;

    return 1 + max(profondita(root->left), profondita(root->right));
}
Nodo* insert_nodo(Nodo* root, Nodo* new_node){
    Nodo* parent=NULL,*temp=root;

    while (temp!=NULL){
        parent=temp;
        temp = (strcmp(new_node->key.nome, temp->key.nome) < 0 ) ? temp->left : temp->right;
    }

    new_node->parent=parent;

    if(parent==NULL)
        root=new_node;
    else if (strcmp(new_node->key.nome, parent->key.nome) < 0)
            parent->left = new_node;
    else
            parent->right = new_node;

    return root;
}
void inorder(Nodo* root){
    if(root == NULL)
        return;
    inorder(root->left);
    stampa_birra(root->key);
    inorder(root->right);
}
void preorder(Nodo* root){
    if(root == NULL)
        return;

    stampa_birra(root->key);
    preorder(root->left);
    preorder(root->right);
}
void postorder(Nodo* root){
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    stampa_birra(root->key);
}
int max(int v1, int v2){
     return (v1 > v2) ? v1 : v2;
}
Nodo* ricerca(Nodo* root, char* nome_birra){
    Nodo *temp = root;
    int compare = strcmp(temp->key.nome, nome_birra);
    if(compare == 0)
        return temp;

    return (compare > 0) ? ricerca(temp->left, nome_birra) : ricerca(temp->right, nome_birra);
}
Nodo* abr_min(Nodo* root){
    Nodo* temp = root;
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}
Nodo* abr_max(Nodo* root){
    Nodo* temp = root;
    while(temp->right != NULL)
        temp = temp->right;
    return temp;
}
Nodo* abr_succ(Nodo* x){
    Nodo* y=NULL;

    if(x->right != NULL)
        return abr_min(x->right);
    y = x->parent;
    while(y != NULL && x == y->right)
        x = y;
    y = y->parent;
    return y;
}
Nodo* abr_pred(Nodo* x){
    Nodo* y=NULL;
    if(x->left != NULL)
        return abr_max(x->left);
    y = x->parent;
    while(y != NULL && x == y->left)
        x = y;
    y = y->parent;
    return y;
}
Nodo* delete_node(Nodo* root, Nodo* nodo){
    Nodo* target=NULL,* x=NULL;

    if(nodo->left == NULL || nodo->right == NULL)
        target = nodo;
    else
        target = abr_succ(nodo);

    if(target->left != NULL)
        x = target->left;
    else
        x = target->right;

    if(x != NULL)
        x->parent = target->parent;

    if(target->parent == NULL)
        root = x;
    else if(target->parent->left == target)
        target->parent->left = x;
    else
        target->parent->right = x;

    if(target != nodo)
        nodo->key = target->key;

    free(target);
    return root;
}
void clearScreen(){
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}
