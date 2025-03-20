#include <stdio.h>
#include <string.h>
#define MAX 1000

//Global Variable
int D_index = 0;
int found = -1;

//Function Declaration
void main_menu();
int check_input(char input[2]);
void addWord();
void saveWord();
void displayWord();
void loadingFile();
void searchWord();
void deleteWord();

struct info{
    char word[20];
    char defination[300];
};

struct info dictionary[MAX];

int main()
{
    loadingFile();
    main_menu();
    return 0;
}

void main_menu()
{
    char input[2];
    printf("\nDictionary Application\n");
    printf("1. Add Word\n2. Display Word\n3. Search Word\n4. Delete Word\n5. Update Defination\n6. Exit\n");
    printf("Enter your choice: ");
    scanf(" %[^\n]",input);

    int option = check_input(input);
    if(option == 49){
        addWord();
        main_menu();

    }else if(option == 50){
        displayWord();
        main_menu();

    }else if(option == 51){
        searchWord();
        main_menu();

    }else if(option == 52){
        deleteWord();
        main_menu();

    }else if(option == 53){
        //updateDefination();
        main_menu();

    }else if(option == 54){
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

void addWord()
{
    FILE *fptr;
    fptr = fopen("dictionary.txt","w");
    if(fptr != NULL){
        printf("Enter Word: ");
        scanf(" %[^\n]",dictionary[D_index].word);
        printf("Enter defination: ");
        scanf(" %[^\n]",dictionary[D_index].defination);

        printf("Word added successfully\n");
        D_index++;
        saveWord();
    }
    fclose(fptr);
}

void saveWord()
{
    FILE *fptr = fopen("dictionary.txt", "w");
    if (!fptr) {
        printf("Error saving word!\n");
        return;
    }

    for (int i = 0; i < D_index ; i++) {
        fprintf(fptr, "%s%c%s\n", dictionary[i].word, '|', dictionary[i].defination);
    }

    fclose(fptr);
}

void displayWord()
{
    FILE *fptr;
    fptr = fopen("dictionary.txt","r");

    if(fptr == NULL){
        printf("Error: Could not open file.\n");
    }else{
        printf("Word\t\t\tDefination\n");
        printf("----------------------------------------------------\n");
        for(int i = 0 ; i < D_index ; i++){
            printf("%s\t\t\t%s\n", dictionary[i].word, dictionary[i].defination);
        }
    }
    fclose(fptr);
}

void loadingFile()
{
    FILE *fptr = fopen("dictionary.txt", "r");
    if (fptr == NULL) {
        printf("No existing dictionary file found. Starting fresh.\n");
    }

    while (fscanf(fptr, "%19[^|]|%299[^\n]\n", dictionary[D_index].word, dictionary[D_index].defination) == 2) {
        D_index++;
    }

    fclose(fptr);
}

void searchWord()
{
    char searchWord[20];
    printf("Enter word to search: ");
    scanf(" %[^\n]",searchWord);

    for (int i = 0; i < D_index ; i++) {
        if (strcmp(dictionary[i].word, searchWord) == 0) {
            printf("Defination of %s: %s\n", dictionary[i].word, dictionary[i].defination);
            return;
        }
    }
    printf("Word not found!\n");
}

void deleteWord()
{
    char deleteWord[20];
    printf("Enter word to delete: ");
    scanf(" %[^\n]",deleteWord);

    for (int i = 0; i < D_index ; i++) {
        if (stricmp(dictionary[i].word, deleteWord) == 0) {
            found = 1;
            for (int j = i; j < D_index - 1; j++) {
                dictionary[j] = dictionary[j + 1];
            }
            D_index--;
            printf("Word '%s' deleted successfully\n",deleteWord);
            saveWord();
        }
    }
    if(found == -1){
        printf("Word not found.\n");
    }
}
