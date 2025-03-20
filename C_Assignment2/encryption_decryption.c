#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *input, *output;
    char ch, ptr1[40], ptr2[40];
    int key=0, choice=0;

    printf("Simple File Encryption/Decryption Program\n1. Encryption a file\n2. Decryption a file\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);

    if(choice == 1){
        printf("Enter the input file name : ");
        scanf(" %[^\n]",ptr1);
        input = fopen(ptr1,"r");
        if(input == NULL){
            puts("File read error");
            exit(3);
        }

        printf("Enter the output file name : ");
        scanf(" %[^\n]",ptr2);
        output = fopen(ptr2,"w");
        if(output == NULL){
            puts("File write error");
            exit(3);
        }

        printf("Enter the key (integer) : ");
        scanf("%d",&key);
        do{
            ch = fgetc(input);
            fputc(ch+key,output);
        }while(ch != EOF);
        printf("Encryption completed. Output saved to %s",ptr2);

    }else{
        printf("Enter the input file name : ");
        scanf(" %[^\n]",ptr1);
        input = fopen(ptr1,"r");
        if(input == NULL){
            puts("File read error");
            exit(3);
        }

        printf("Enter the output file name : ");
        scanf(" %[^\n]",ptr2);
        output = fopen(ptr2,"w");
        if(output == NULL){
            puts("File write error");
            exit(3);
        }

        printf("Enter the key (integer) : ");
        scanf("%d",&key);
        ch = fgetc(input);
        while(ch != EOF){
            fputc(ch-key,output);
            ch = fgetc(input);
        }
        printf("Decryption completed. Output saved to %s",ptr2);
    }
    fclose(input);
    fclose(output);
    return 0;
}

