#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <time.h> 
#define MAX 50 

typedef struct Kopi {
    char nama[MAX]; 
    char beverage[MAX]; 
    int quantity; 
    struct Kopi *next; 
} Kopi; 

Kopi *hashTable[MAX] = {NULL}; 

int hashFunction(char *name){
    int sum = 0; 
    for ( int i = 0; i < strlen(name); i++ ){
        sum += name[i]; 
    }

    return sum % MAX; 
}

void menu_create(){
    Kopi *newKopi = (Kopi*)malloc(sizeof(Kopi)); 

    do {
        printf("Input your name[5 - 30 characters]: "); 
        scanf("%[^\n]", newKopi->nama); 
        getchar(); 
    } while(strlen(newKopi->nama) < 5 || strlen(newKopi->nama) > 30); 

    do {
        printf("Input your beverages[Americano | Cappucino | Cafe Latte]: "); 
        scanf("%[^\n]", newKopi->beverage); 
        getchar(); 
    } while(strcmp(newKopi->beverage, "Americano") != 0 && strcmp(newKopi->beverage, "Cappucino") != 0 && strcmp(newKopi->beverage, "Cafe Latte") != 0); 

    do { 
        printf("Input your quantity[ > 0 ]: "); 
        scanf("%d", &newKopi->quantity); 
        getchar(); 
    } while(newKopi->quantity < 1); 

    char confirm; 
    do {
        printf("Input your confirmation [y / n]: "); 
        scanf("%c", &confirm); 
        getchar(); 
    } while (confirm != 'Y' && confirm != 'N' && confirm != 'y' && confirm != 'n'); 

    if ( confirm == 'n' || confirm == 'N') return; 

    int index = hashFunction(newKopi->nama); 
    newKopi->next = hashTable[index]; 
    hashTable[index] = newKopi; 

    printf("Order added succesfully\n"); 
}

void menu_view(){
    int found = 1; 

    printf("+-----------------------------------------------------------------+\n"); 
    printf("|     NAMA      |           BEVERAGE          |       QUANTITY    |\n"); 
    printf("+-----------------------------------------------------------------+\n"); 
    
    for ( int i = 0; i < MAX; i++ ){
        Kopi *temp = hashTable[i]; 
        while (temp){
            printf("| %-13s | %27s | %17d |\n", temp->nama, temp->beverage, temp->quantity); 
            printf("+-----------------------------------------------------------------+\n"); 
            temp = temp->next; 
            found = 0; 
        }
    }

    if ( found ) printf("There is no orders....\n"); 
}

void menu_delete(){
    if ( !hashTable ) {
        printf("There are no order\n"); 
        return; 
    }

    char name[31];
    printf("Enter the name to remove order: ");
    scanf(" %[^\n]", name);
    getchar();

    int index = hashFunction(name); 
    Kopi *temp = hashTable[index], *prev = NULL;

    while ( temp){
        if ( strcmp(temp->nama, name) == 0 ){
            char confirm; 
            do {
                printf("Confirm removing order [Y/N]: ");
                scanf(" %c", &confirm);
                getchar();
                confirm = toupper(confirm);
            } while (confirm != 'Y' && confirm != 'N');

            if ( confirm == 'N') return; 

            if ( prev ) prev->next = temp->next; 
            else hashTable[index] = temp->next; 

            free(temp); 
            printf("Order from %s is successfully deleted.\n", name);
            return;
        }
        prev = temp; 
        temp = temp->next; 
    }

    printf("Order not found.\n");
}

int main(){
    while(1){
        int option; 
        do{
            printf("+------------------------------------+\n"); 
            puts("                SETARBAK                "); 
            printf("+------------------------------------+\n"); 
            puts("1. Add order"); 
            puts("2. View all orders"); 
            puts("3. Remove Orders"); 
            puts("4. Exit"); 
            printf("Input your choice[ 1 - 4 ]: "); 
            scanf("%d", &option); 
            getchar(); 
        } while ( option < 1 || option > 4 );
        
        if ( option == 1 ) menu_create(); 
        else if ( option == 2 ) menu_view(); 
        else if ( option == 3 ) menu_delete(); 
        else if ( option == 4 ){
            printf("Exiting the program...."); 
            return 0; 
        }

    }
}