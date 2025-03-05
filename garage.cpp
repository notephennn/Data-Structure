#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <time.h> 
#include <ctype.h> 
#define MAX 50

typedef struct Vehicle {
    char nama[55]; 
    char type[55]; 
    int duration; 
    struct Vehicle *next; 
} Vehicle; 

Vehicle *hashTable[MAX]; 

int hashFunction(char *nama){
    int sum = 0; 
    for ( int i = 0; nama[i] != '\0'; i++ ){
        sum += nama[i]; 
    }

    return sum % MAX; 
}

int isUniqueName(char *nama){
    int index = hashFunction(nama); 
    Vehicle *temp = hashTable[index]; 
    while ( temp ){
        if ( strcmp(temp->nama, nama) == 0 ) {
            return 0;  
        }
        temp = temp->next;
    }
    return 1; 
}

int isValidName(char *nama){
    int valid = 0; 
    for ( int i = 0; nama[i] != '\0'; i++ ){
        if ( nama[i] == ' ') valid++; 
    }

    if ( valid == 1) return 1; 
    return 0; 
}

void menu_create(){
    char tempnama[55]; 
    Vehicle *newVehicle = (Vehicle*)malloc(sizeof(Vehicle)); 
    newVehicle->next = NULL; 

    do {
        printf("Input your name[2 words and Unique]: "); 
        scanf("%[^\n]", tempnama); 
        getchar(); 
    } while(!(isUniqueName(tempnama) && isValidName(tempnama))); 
    strcpy(newVehicle->nama, tempnama); 

    do {
        printf("Input your type[SUV || Sedan || Hatchback]: "); 
        scanf("%[^\n]", newVehicle->type); 
        getchar(); 
    } while ( strcmp(newVehicle->type, "SUV") != 0 && strcmp(newVehicle->type, "Sedan") != 0 && strcmp(newVehicle->type, "Hatchback") != 0 ); 

    do {
        printf("Input your storage duration: "); 
        scanf("%d", &newVehicle->duration); 
        getchar(); 
    } while ( newVehicle->duration <=0 ); 

    char confirm; 
    do {
        printf("Input your confirm[y / n]: "); 
        scanf("%c", &confirm); 
        getchar(); 
    } while ( confirm != 'n' && confirm != 'N' && confirm != 'y' && confirm != 'Y'); 

    if ( confirm == 'n' || confirm == 'N') return; 

    int index = hashFunction(newVehicle->nama); 

    if ( hashTable[index] == NULL ) hashTable[index] = newVehicle; 
    else {
        Vehicle *temp = hashTable[index]; 
        while ( temp->next){
            temp = temp->next; 
        }
        temp->next = newVehicle; 
    }

    printf("Vehicle added succesfully\n"); 
}

void menu_view(){
    int found = 1; 

    for ( int i = 0; i < MAX; i++ ){
        Vehicle *temp = hashTable[i]; 
        while ( temp ){
            printf("Nama: %s\n Type: %s\n Duration: %d\n", temp->nama, temp->type, temp->duration); 
            temp = temp->next; 
            found = 0; 
        }
    }

    if ( found ) printf("There is no vehicle in garage\n"); 
}

void menu_update(){
    int valid = 0; 
    for ( int i = 0; i < MAX; i++ ){
        if ( hashTable[i] != NULL ){
            valid = 1; 
            break; 
        }
    }

    if ( !valid ) {
        printf("There is no vehicle in garage\n"); 
        return; 
    }

    menu_view(); 

    char updateName[55]; 
    printf("Input your name[2 words and Unique]: "); 
    scanf("%[^\n]", updateName); 
    getchar(); 

    int index = hashFunction(updateName); 
    Vehicle *temp = hashTable[index]; 

    int found = 0; 

    while ( temp != NULL ){
        if ( strcmp(temp->nama, updateName) == 0 ) {
            found = 1; 
            break; 
        }
        temp = temp->next; 
    }

    if ( !found ) {
        printf("There is no name in hashTable\n"); 
        return; 
    }

    int newDuration;
    do {
        printf("Input new storage duration [must be positive]: ");
        scanf("%d", &newDuration);
        getchar();
    } while (newDuration <= 0);

    temp->duration = newDuration;
    printf("Storage duration updated successfully!\n");
    
}

int main(){
    while(1){
        int option; 
        do{
            puts("----------Nelson's garage-----------"); 
            printf("1. Insert new vehicle\n"); 
            printf("2. View all vehicle\n"); 
            printf("3. Update storage duration\n"); 
            printf("4. Exit\n"); 
            printf("Input your choice[1-4]: "); 
            scanf("%d", &option); 
            getchar(); 
        } while ( option < 1 || option > 4 );
        
        if ( option == 1 ) menu_create(); 
        else if ( option == 2 ) menu_view(); 
        else if ( option == 3 ) menu_update(); 
        else if ( option == 4 ){
            printf("Exiting this program..."); 
            return 0; 
        }
    }
}