#include <stdio.h>
#include <string.h>
#define MAX 500

//Global Variable
int B_index = 0;
int bookFound = -1;
int delBook = -1;

//function declaration
void main_menu();
int check_input(char input[2]);
void addBook();
void displayBook();
int searchBook(char srchTitle[30]);
int deleteBook(int delID);

struct info{
    int id;
    char title[30];
    char author[30];
};

struct info db[MAX];

int main()
{
    main_menu();
    return 0;
}

/* Main Menu and User Input */
void main_menu()
{
    char input[2];
    printf("\nBook Management System\n");
    printf("1. Add Book\n2. Delete Book\n3. Search Books\n4. Display All Books\n5. Exit\n");
    printf("Enter your choice: ");
    scanf(" %[^\n]",input);

    int option = check_input(input);
    if(option == 49){
        addBook();
        main_menu();

    }else if(option == 50){
        int ID = 0;
        printf("Enter book ID to delete: ");
        scanf("%d", &ID);
        deleteBook(ID);
        main_menu();

    }else if(option == 51){
        char srchtitle[30];
        printf("Enter Book Title to search: ");
        scanf(" %[^\n]",srchtitle);

        int bookFound = searchBook(srchtitle);
        if(bookFound != -1){
            printf("Book found:\n");
            printf("ID: %d\n",db[bookFound].id);
            printf("Title: %s\n",db[bookFound].title);
            printf("Author: %s\n",db[bookFound].author);
        }else{
            printf("Error: Book with title '%s' not found.\n",srchtitle);
        }
        main_menu();

    }else if(option == 52){
        displayBook();
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

void addBook()
{
    int add_id = 0;
    char add_title[30];
    char add_author[30];

    printf("Enter Book ID: ");
    scanf("%d",&add_id);
    printf("Enter Book Title: ");
    scanf(" %[^\n]",add_title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]",add_author);

    db[B_index].id = add_id;
    strcpy(db[B_index].title, add_title);
    strcpy(db[B_index].author, add_author);
    B_index++;

    printf("Book added successfully\n");
}

void displayBook()
{
    if(B_index == 0){
        printf("No Books in the system.\n");
    }

    for(int count = 0 ; count < B_index ; count++){
        printf("ID: %d, Title: %s, Author: %s\n",db[count].id,db[count].title,db[count].author);
    }
}

int searchBook(char srchTitle[30])
{
    for(int i = 0 ; i < B_index ; i++){
        if(strcmp(db[i].title,srchTitle) == 0){
            return i;
        }
    }
    return -1;
}

int deleteBook(int delID)
{
    for (int i = 0 ; i < B_index ; i++) {
        if (db[i].id == delID) {
            delBook = 1;
            // Shift all books after the deleted book
            for (int j = i; j < (B_index - 1); j++) {
                db[j] = db[j + 1];
            }
            B_index--; // Decrease the book count
            printf("Book with ID %d deleted successfully.\n", delID);
            break;
        }
    }

    if (delBook == -1) {
        printf("Book with ID %d not found.\n", delID);
    }
}
