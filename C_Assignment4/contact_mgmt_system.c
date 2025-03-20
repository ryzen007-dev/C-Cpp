#include <stdio.h>
#include <string.h>
#define MAX 500

//Global Variation
int C_index = 0;
int found = -1;

//function declaration
void main_menu();
int check_input(char input[2]);
void addContact();
void saveContacts();
void displayContacts();
void searchContact();
void deleteContact();
void loadContact();

struct info{
    char name[30];
    char phNumber[15];
};

struct info contact[MAX];

int main()
{
    loadContact();
    main_menu();
    return 0;
}

/* Main Menu and User Input */
void main_menu()
{
    char input[2];
    printf("\nContact Management System\n");
    printf("1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display All Contacts\n5. Exit\n");
    printf("Enter your choice: ");
    scanf(" %[^\n]",input);

    int option = check_input(input);
    if(option == 49){
        addContact();
        main_menu();

    }else if(option == 50){
        searchContact();
        main_menu();

    }else if(option == 51){
        deleteContact();
        main_menu();

    }else if(option == 52){
        displayContacts();
        main_menu();

    }else if(option == 53){
        printf("Exiting program.\n");

    }else{
        main_menu();
    }
}

//ascii value '1' = 49 , '9' = 57
int check_input(char input[2])
{
    if(input[0]>=49 && input[0]<=57 && input[1]=='\0'){
        return input[0];
    }else{
        return -1;
    }
}

void addContact()
{
    FILE *fptr;
    fptr = fopen("contacts.txt","w");
    if(fptr == NULL){
        printf("Contact can't create!");
    }else{
        printf("Enter Name: ");
        scanf(" %[^\n]",contact[C_index].name);
        printf("Enter Phone Number: ");
        scanf(" %[^\n]",contact[C_index].phNumber);

        printf("Contact added successfully\n");
        C_index++;
        saveContacts();
    }

    fclose(fptr);
}

void saveContacts()
{
    FILE *fptr = fopen("contacts.txt", "w");
    if (!fptr) {
        printf("Error saving contacts!\n");
        return;
    }

    for (int i = 0; i < C_index ; i++) {
        fprintf(fptr, "%s%c%s\n", contact[i].name, ',', contact[i].phNumber);
    }

    fclose(fptr);
}

void displayContacts()
{
    FILE *fptr;
    fptr = fopen("contacts.txt","r");

    if(fptr == NULL){
        printf("Error: Could not open file.\n");
    }else{
        printf("Contacts List:\n");
        printf("---------------------------\n");
        for(int i = 0 ; i < C_index ; i++){
            printf("Name: %s\nPhone: %s\n", contact[i].name, contact[i].phNumber);
        }
        printf("---------------------------\n");
    }
    fclose(fptr);
}

void searchContact()
{
    char searchName[50];
    printf("Enter name to search: ");
    scanf(" %[^\n]",searchName);

    for (int i = 0; i < C_index ; i++) {
        if (strcmp(contact[i].name, searchName) == 0) {
            printf("Contact found:\nName: %s\nPhone: %s\n", contact[i].name, contact[i].phNumber);
            return;
        }
    }
    printf("Contact not found!\n");
}

void deleteContact()
{
    char deleteName[30];
    printf("Enter name to delete: ");
    scanf(" %[^\n]",deleteName);

    for (int i = 0; i < C_index ; i++) {
        if (strcmp(contact[i].name, deleteName) == 0) {
            found = 1;
            for (int j = i; j < C_index - 1; j++) {
                contact[j] = contact[j + 1];
            }
            C_index--;
            printf("Contact deleted successfully!\n");
            saveContacts();
        }
    }
    if(found == -1){
        printf("Contact not found.\n");
    }
}

void loadContact()
{
    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL) {
        return; // No file found, start with empty contact list
    }

    while (fscanf(fptr, "%29[^,],%14[^\n]\n", contact[C_index].name, contact[C_index].phNumber) == 2) {
        C_index++;
    }

    fclose(fptr);
}


