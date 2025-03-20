#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define USERSIZE 1000
#define DATA_COUNT 20 //space counting for 20 user

//Global Variables
int G_index = 0; //for user counting
int email_found = -1; //for checking email duplication (user input mail vs database email)
int space_array[20]; //space counting for 20 user
int email_valid = -1; //to check email format
int nrc_valid = -1; //to check nrc format
int two_charArray = -1; //to check user input NRC vs database NRC
int strong_pass_valid = -1; //to check strong password
int phone_valid = -1; //to check phone number
int eKey_valid = -1; //to check encryption key
int reKey_valid = -1; //to check recovery key
int phone_found = -1; //to find receiver phone from db
char int_to_charArray[15];

char month[3];
char day[2];
char year[4];
//End of Global Variables

//Function Declaration
int check_input(char input[2]); /* Main Menu and User Input */
void login(); /* Email Exist Checking and Char Counting */
void rEgister();
void email_exist_checking(char email[50]);
int char_counting(char my_char[50]);
void loading_from_file(); /* Loading from File */
void space_counter(); /* Space Counter */
void printing_all_data(); /* Printing All Data */
void email_validation(char to_check[50]); /* Email Validation */
void compare_two_charArray(char first[200],char second[200]); /* Compare Two Char Array */
void nrc_validation(char nrc[20]); /* NRC Valid and Strong Pass Valid */
void strong_pass_validation(char pass[50]);
void phone_validation(unsigned int phone); /* Phone Valid and Encryption Key */
void encryption_key_validation(char eKey[30]);
void recovery_key_validation(char reKey[30]); /* Registration Complete */
void copy_two_char_array(char receiver[200],char transmitter[200]);
void user_sector(); /* User Setting */
void transfer_money();
void phone_number_finding(unsigned int to_find_ph);
void money_transaction(int transmit,int receiver,unsigned int amount); /* Withdraw */
void printing_specific_data(int user);
void user_withdraw();
void recording_all_data_to_file(); /* Recording Data to File */
void get_time(); /* Get Time */
void transaction_record(int userDBindex,int uFound,char who,unsigned int amount); /* Transaction Record From to */
void integer_to_charArrayFun(unsigned int integer); /* Type Changing */
unsigned int char_to_integer_fun(char char_array[50]);
void time_class(int user_index); /* Last Record */
void time_class_last_record(int user_index);
void time_class_get_date(char last_record[]); /* Get Month and Day */

/* DB for Bank */
struct trans{
    char note[200]; //1 transaction record = 200 character ခွင့်ပြုမယ်
};

struct info{ 
    unsigned int id;    //u
    char name[50];
    char nrc[20];
    char email[50];
    char password[50];
    unsigned int phoneNumber;
    char encryption_key[30];    //at least 4 to 6
    char recovery_key[30];
    char account_status[10]; //$
    int account_type;   //$ //1 personal ,2 business, 3 others...
    int account_level; //$
    int minimum_opening_deposit; //$
    char currency[5];
    unsigned long long int current_amount;  //llu
    char loanStatus[1]; //$
    unsigned int monthly_income;
    unsigned int loan_amount; //$
    float loan_rate; //$
    char address[100];
    int trans_amount_limit_perday;
    
    struct trans tr[300]; //user တယောက်ချင်းစီအတွက် transaction record = 300 

    // %u%s%s%s%s%u%s%s%s%d%d%d%s%llu%s%u%u%f%s
};

struct info db[USERSIZE];

struct myTime{
    char current_time[24];
};

struct myTime getCTime[1];


/* Main Menu and User Input */
void main_menu()
{
    char input[2];
    printf("Welcome to Our OnlineBank-NCC!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit! >>: ");
    scanf(" %[^\n]",input);

    int option = check_input(input);
    if(option == 49){
        login();
    }else if(option == 50){
        rEgister();
    }else if(option == 51){
        printf("Good Bye!\n");
        recording_all_data_to_file();
        exit(2);
    }else{
        main_menu();
    }
}
//ascii value '0' = 49 , '9' = 57
int check_input(char input[2])
{
    if(input[0]>=49 && input[0]<=57 && input[1]=='\0'){
        return input[0];
    }else{
        return -1;
    }
}

/* Email Exist Checking and Char Counting */
void login()
{
    char l_email[50];
    char l_pass[50];
    email_found = -1;
    two_charArray = -1;

    /* Error Fix for Registration*/
    while(email_found == -1 || two_charArray == -1){
        printf("This is Online Bank Login!\n");
        printf("[x]Enter your email to login! : ");
        scanf(" %[^\n]",l_email);
        printf("Enter your password to login! : ");
        scanf(" %[^\n]",l_pass);

        email_exist_checking(l_email); //for check email
        compare_two_charArray(db[email_found].password,l_pass);
        //for check password (email_found = gcc) in code line 301

        if(email_found == -1 || two_charArray == -1){ //bugs have
            email_found = -1; // reset to -1
            two_charArray = -1; // reset to -1
            printf("[-]Your Login credential incorrect!\n");
        }
    }
    user_sector(); /* Withdraw */  
}

void rEgister()
{
    char re_email[50];
    char re_name[50];
    char re_nrc[20];
    char re_pass[50];
    unsigned int re_phone = 0;
    char re_encrypt_key[30];
    char re_recovery_key[30];
    char re_currency[5];
    unsigned long long int re_current_amount = 0;
    unsigned int re_monthly_income = 0;
    char re_address[100];
    char re_note[200];
    printf("This is Online Bank Register!\n");

    /* Email Validatioin */
    email_valid = -1;
    while(email_valid == -1){
        printf("[x]Enter your email to register >>: ");
        scanf(" %[^\n]",re_email);

        email_validation(re_email);
        if(email_valid == -1){
            printf("[-]Your email format was not valid\n");
        }
    }
    printf("[+]Your email format was valid\n");

    /* Email Exist Checking*/
    email_found = -1;
    email_exist_checking(re_email);

    if(email_found != -1){
        printf("[-]Your email was already registered\n");
        rEgister();
    }else{
        printf("[+]Your email was saved\n");

        /* Compare Two Char Array */
        printf("[x]Enter your username : ");
        scanf(" %[^\n]",re_name);

        nrc_valid = -1;
        while(nrc_valid == -1){
            printf("[x]Enter your NRC information : ");
            scanf(" %[^\n]",re_nrc);

            /* NRC Valid and Strong Pass Valid */
            nrc_validation(re_nrc);

            if(nrc_valid == -1){
                printf("[-]Your NRC format was incorrect\n");
            }
        }
        printf("[+]Your NRC format was correct\n");

        /* Testing and Phone */
        strong_pass_valid = -1;
        while(strong_pass_valid == -1){
            printf("[x]Enter your password:");
            scanf(" %[^\n]",re_pass);

            strong_pass_validation(re_pass);

            if(strong_pass_valid == -1){
                printf("[-]Your password format too weak and Try Again!\n");
            }
        }
        printf("[+]Your password format was correct and was saved!\n");

        phone_valid = -1;
        while(phone_valid == -1){
            printf("[x]Enter your Phone Number : ");
            scanf("%u",&re_phone);

            /* Phone Valid and Encryption Key */
            phone_validation(re_phone);

            if(phone_valid == -1){
                printf("[-]Your phone number is already registered\n");
            }
        }
        printf("[+]Your phone is correct and saved!\n");

        while(eKey_valid == -1){
            printf("[x]Enter your encryption key (from 4 to 6 char) : ");
            scanf(" %[^\n]",re_encrypt_key);

            encryption_key_validation(re_encrypt_key);

            if(eKey_valid == -1){
                printf("[-]Your Encryption Key do not correspond with our pattern\n");
            }
        }
        printf("[+]Your Encryption Key was valid and saved!\n");

        /* Registration Complete */
        while(reKey_valid == -1){
            printf("[x]Enter your recovery key carefully : ");
            scanf(" %[^\n]",re_recovery_key);

            recovery_key_validation(re_recovery_key);

            if(reKey_valid == -1){
                printf("[-]Your recovery key do not correspond with our pattern\n");
            }
        }
        printf("[+]Your recovery key was saved!\n");

        printf("[x]Enter your currency to use : ");
        scanf(" %[^\n]",re_currency);
        printf("[x]Enter your amount : ");
        scanf("%llu",&re_current_amount);
        printf("[x]Enter your monthly income : ");
        scanf("%u",&re_monthly_income);
        printf("[x]Enter your address : ");
        scanf(" %[^\n]",re_address);
        printf("[x]Enter your opening note : ");
        scanf(" %[^\n]",re_note);

        /* Adding Data to Database */
        db[G_index].id = G_index + 1;
        copy_two_char_array(db[G_index].name,re_name);
        copy_two_char_array(db[G_index].nrc,re_nrc);
        copy_two_char_array(db[G_index].email,re_email); 
        copy_two_char_array(db[G_index].password,re_pass);
        db[G_index].phoneNumber = re_phone;
        copy_two_char_array(db[G_index].encryption_key,re_encrypt_key);
        copy_two_char_array(db[G_index].recovery_key,re_recovery_key);
        copy_two_char_array(db[G_index].account_status,db[2].account_status);
        db[G_index].account_type = db[2].account_type;
        db[G_index].account_level = db[2].account_level;
        db[G_index].minimum_opening_deposit = db[2].minimum_opening_deposit;
        copy_two_char_array(db[G_index].currency,re_currency);
        db[G_index].current_amount = re_current_amount;
        copy_two_char_array(db[G_index].loanStatus,db[2].loanStatus);
        db[G_index].monthly_income = re_monthly_income;
        db[G_index].loan_amount = db[2].loan_amount;
        db[G_index].loan_rate = db[2].loan_rate;
        copy_two_char_array(db[G_index].address,re_address);
        db[G_index].trans_amount_limit_perday = db[2].trans_amount_limit_perday;
        copy_two_char_array(db[G_index].tr[0].note,re_note);

        space_array[G_index] = 20;
        G_index++; //user အသစ်တယောက်တိုးလာပြီဆိုတဲ့ အဓိပ္ပာယ်

        printing_all_data();
        printf("[x]Registration Success: Mr/s: %s\n",re_name);
        main_menu();
    }
}

void email_exist_checking(char email[50])
{
    int counter = char_counting(email); //checking char number from user input email

    /* DB for Bank */
    int same_counting = 0;
    for(register int gcc=0 ; gcc < G_index ; gcc++){ //checking char number from database email
        int db_email_count = char_counting(db[gcc].email);

        if(counter == db_email_count){
            for(register int a=0 ; a < counter ; a++){
                if(email[a] != db[gcc].email[a]){
                    break;
                }
                same_counting++;
            }
        }
        if(counter == same_counting){
            email_found = gcc;
            break;
        }
    }
}

int char_counting(char my_char[50])
{
    int count = 0;
    for(register int a=0 ; a<50 ; a++){
        if(my_char[a] == '\0'){
            break;
        }
        count++;
    }
    return count;
}

/* Loading from File */
void loading_from_file()
{
    FILE *fptr = fopen("encrypted_data.txt","r");

    if(fptr != NULL){
        for(register int user=0 ; user < USERSIZE ; user++){
            fscanf(fptr , "%u%s%s%s%s%u%s%s%s%d%d%d%s%llu%s%u%u%f%s%d" , &db[user].id, db[user].name, db[user].nrc, db[user].email, db[user].password, &db[user].phoneNumber, db[user].encryption_key, db[user].recovery_key, db[user].account_status, &db[user].account_type, &db[user].account_level, &db[user].minimum_opening_deposit, db[user].currency, &db[user].current_amount, db[user].loanStatus, &db[user].monthly_income, &db[user].loan_amount, &db[user].loan_rate, db[user].address, &db[user].trans_amount_limit_perday);
            
            /* Loading for Transaction Record Data */                 
            for(register int trc=0 ; trc <= space_array[user]-20 ; trc++){ 
                fscanf(fptr , "%s" , db[user].tr[trc].note);               
            }
            // int space_array[20] = {100,20,15,50,0,0,0,0,0};
            // user = 0;
            // space_array[user] - 19 = 81;
            // db[0].tr[0].note = "onlineBankAdmin";
            // db[0].tr[1].note = "winhtuttoaungaung3000time";

            if(db[user].id == 0){
                break;
            }
            G_index++; //reading how many user have in database
        }
    }else{
        printf("File opening error at loading from file function!\n");
    }
    fclose(fptr);
}

/* Space Counter */
void space_counter()
{
    FILE *fptr = fopen("encrypted_data.txt","r");

    if(fptr != NULL){
        char c = fgetc(fptr);
        int index = 0; //If you declare as Global var, it equals to G_index

        while(!feof(fptr)){
            if(c != '\n'){
                if(c == ' '){
                    space_array[index] += 1; //space_array[20] = {20,20,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                }
                c = fgetc(fptr);
            }else{
                index++;
                c = fgetc(fptr);
            }
        }
    }else{
        printf("File opening error at space_counter function!\n");
    }

    for(int i=0; i < DATA_COUNT ; i++){
        printf(" %d",space_array[i]); // 20 20 19 19 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    }
    printf("\n");
}

/* Printing all data */
void printing_all_data()
{
    for(int user=0 ; user < G_index ; user++){
        printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s-%d" , db[user].id, db[user].name, db[user].nrc, db[user].email, db[user].password, db[user].phoneNumber, db[user].encryption_key, db[user].recovery_key, db[user].account_status, db[user].account_type, db[user].account_level, db[user].minimum_opening_deposit, db[user].currency, db[user].current_amount, db[user].loanStatus, db[user].monthly_income, db[user].loan_amount, db[user].loan_rate, db[user].address, db[user].trans_amount_limit_perday);

        for(int gcc=0 ; gcc <= space_array[user]-20 ; gcc++){
            printf("-%s",db[user].tr[gcc].note);
        }
        printf("\n");
    }
}

/* Email Validatioin */
void email_validation(char to_check[50])
{
    int space = 1;
    int format = 1;
    char valid_form[10] = {'@','g','m','a','i','l','.','c','o','m'};

    int check_counter = char_counting(to_check); //e.g., winhtut@gmail.com

    int front_counter = check_counter - 10; //to check username "winhtut" (not allow space)
    for(int i=0 ; i < front_counter ; i++){
        if(to_check[i] == ' '){
            space = -1;
            break;
        }
    }

    for(int f=0 ; f<10 ; f++){ //to check domain name "@gmail.com"
        if(to_check[front_counter + f] != valid_form[f]){
            format = -1;
            break;
        }
        //front_counter++;
    }
    if(space == 1 && format == 1){
        email_valid = 1;
    }
}

/* Compare Two Char Array */
void nrc_validation(char nrc[20])
{
    int nrc_counter = char_counting(nrc);
    for(int i=0 ; i<3 ; i++){   // 3 - accept registration with admin1 or admin2 or admin3 nrc format

        /* NRC Valid and Strong Pass Valid */
        two_charArray = -1;
        compare_two_charArray(nrc,db[i].nrc);

        if(two_charArray == 1){
            nrc_valid = 1;
            break;
        }
    }
}

void compare_two_charArray(char first[200],char second[200])
{
    int first_counter = char_counting(first);
    int second_counter = char_counting(second);

    int same_counter = 0;

    if(first_counter == second_counter){ //to compare user input nrc no: & db nrc no:
        for(register int i=0 ; i<first_counter ; i++){
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }
        if(first_counter == same_counter){
            two_charArray = 1;
        }
    }
}

/* NRC valid and strong pass valid */
void strong_pass_validation(char pass[50])
{
    int i = 0;
    int special = 0;
    int number = 0;
    int smallChar = 0;
    int capChar = 0;

    int pass_counter = char_counting(pass);

    if(pass_counter >= 6){
        while (strong_pass_valid == -1){
            if(i == pass_counter){ 
                strong_pass_valid = -1;
                break;
            }

            if(pass[i] >= 33 && pass[i] <= 42){
                special++;
            }else if(pass[i] >= 48 && pass[i] <= 57){
                number++;
            }else if(pass[i] >= 97 && pass[i] <= 122){
                smallChar++;
            }else if(pass[i] >= 65 && pass[i] <= 90){
                capChar++;
            }
            i++;

            if(special>0 && number>0 && smallChar>0 && capChar>0){
                strong_pass_valid = 1;
            }
        }
    }else{
        printf("[-]we need at least 6 characters!\n");
        strong_pass_valid = -1;
    }
}

/* Phone Valid and Encryption Key */
void phone_validation(unsigned int phone)
{
    int phone_counter = 0;
    for(int i=0 ; i < G_index ; i++){
        if(phone != db[i].phoneNumber){
            phone_counter++;
        }else{
            phone_valid = -1;
            break;
        }
    }
    if(phone_counter == G_index){
        phone_valid = 1;
    }
}

void encryption_key_validation(char eKey[30])
{
    int eKey_counter = char_counting(eKey);

    if(eKey_counter >= 4 && eKey_counter <= 6){
        eKey_valid = 1;
    }
}

/* Registration Complete */
void recovery_key_validation(char reKey[30])
{
    int reKey_counter = char_counting(reKey);

    if(reKey_counter >= 6 && reKey_counter <= 10){
        reKey_valid = 1;
    }
}

void copy_two_char_array(char receiver[200],char transmitter[200])
{ //admin3 မှ "$" data အချက်အလက်တွေကို newUser registration လုပ်တဲ့အခါ တိုက်ရိုက် copy ကူးမယ်

    int transmit_counter = char_counting(transmitter);

    for(int i=0 ; i < transmit_counter ; i++){
        receiver[i] = transmitter[i];
    }
}

/* User Setting */
void user_sector()
{
    printf("Welcome Mr /s : %s\n",db[email_found].name);
    printf("Your current amount : %llu\n",db[email_found].current_amount);

    char user_option[2];

    printf("Press 1 To Transfer Money\nPress 2 to Withdraw\n");
    printf("Press 3 To Cash In\nPress 4 to get your Transaction Record\n");
    printf("Press 5 To Loan\nPress 6 to get Main Menu\n");
    printf("Press 7 To Exit\nEnter your option >>: ");
    scanf(" %[^\n]",user_option);

    int option = check_input(user_option);

    if(option == 49){
        transfer_money();
    }else if(option == 50){
        user_withdraw();
    }else if(option == 55){
        recording_all_data_to_file();
    }
}

void transfer_money()
{
    unsigned int amount_toTrans = 0;
    unsigned int receiver_phone = 0;
    char trans_pass[50];
    phone_found = -1;

    while(phone_found == -1){
        printf("[x]Enter receiver phone number >>: ");
        scanf("%u",&receiver_phone);

        phone_number_finding(receiver_phone);

        if(phone_found == -1){
            printf("This phone number is not found in our bank\n");
        }
    }

    while(1){
        printf("Enter amount to send for %s : %s >>: ",db[phone_found].name,db[phone_found].email);
        scanf("%u",&amount_toTrans);

        if(amount_toTrans < db[email_found].current_amount - 1000){
            break;
        }
    }

    two_charArray = -1;
    int wrong_counter = 0;
    while(two_charArray == -1){
        printf("Your current amount %llu\nTransfer amount %u\n",db[email_found].current_amount,amount_toTrans);
        printf("Enter your password to comfirm for transaction >>: ");
        scanf(" %[^\n]",trans_pass);

        compare_two_charArray(db[email_found].password,trans_pass);

        if(two_charArray == -1){
            wrong_counter++;
            if(wrong_counter == 3){ // 3 ခါမှားခွင့်ပေးမယ်
                transfer_money();
                break;
            }
        }
    }
    money_transaction(email_found,phone_found,amount_toTrans);
}

void phone_number_finding(unsigned int to_find_ph)
{
    for(int i=0 ; i < G_index ; i++){
        if(to_find_ph == db[i].phoneNumber){
            phone_found = i;
            break;
        }
    }
}

/* Withdraw */
void money_transaction(int transmit,int receiver,unsigned int amount)
{
    db[transmit].current_amount = db[transmit].current_amount - amount;
    db[receiver].current_amount = db[receiver].current_amount + amount;
    printf("Transaction complete\n");
    printf("Your current amount: %s : %llu\n",db[transmit].name,db[transmit].current_amount);
    transaction_record(transmit,receiver,'t',amount);
    transaction_record(transmit,receiver,'r',amount);
    printing_specific_data(transmit);
    printf("\n\n\n");
    printing_all_data();
    user_sector();
}

void printing_specific_data(int user)
{
    printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s-%d" , db[user].id, db[user].name, db[user].nrc, db[user].email, db[user].password, db[user].phoneNumber, db[user].encryption_key, db[user].recovery_key, db[user].account_status, db[user].account_type, db[user].account_level, db[user].minimum_opening_deposit, db[user].currency, db[user].current_amount, db[user].loanStatus, db[user].monthly_income, db[user].loan_amount, db[user].loan_rate, db[user].address, db[user].trans_amount_limit_perday);
    for(int gcc=0 ; gcc <= space_array[user]-20 ; gcc++){
        printf("-%s",db[user].tr[gcc].note);
    }
    printf("\n");
}

void user_withdraw()
{
    char with_pass[50];
    unsigned int withdraw_amount = 0;
    printf("Your current amount: %s : %llu\n",db[email_found].name,db[email_found].current_amount);
    printf("Enter amount to withdraw >>: ");
    scanf("%u",&withdraw_amount);

    if(withdraw_amount < db[email_found].current_amount - 1000){
        printf("Enter your password to proceed withdraw >>: ");
        scanf(" %[^\n]",with_pass);

        two_charArray = -1;
        compare_two_charArray(db[email_found].password,with_pass);

        if(two_charArray == 1){
            printf("Get your withdraw amount: %u\n",withdraw_amount);
            printf("Your current amount: %llu\n",db[email_found].current_amount - withdraw_amount);
            user_sector();
        }else{
            printf("[-]Wrong credential:\n");
            user_withdraw();
        }

    }else{
        printf("Insufficient Balance!\n");
        user_withdraw();
    }
}

/* Recording data to file */
void recording_all_data_to_file()
{
    FILE *fptr = fopen("encrypted_data.txt","w");
    if(fptr == NULL){
        printf("[-]File opening error at recording to file function():\n");
    }else{
        for(int user=0 ; user < G_index ; user++){
            fprintf(fptr , "%u%c%s%c%s%c%s%c%s%c%u%c%s%c%s%c%s%c%d%c%d%c%d%c%s%c%llu%c%s%c%u%c%u%c%f%c%s%c%d" , db[user].id, ' ', db[user].name, ' ', db[user].nrc, ' ', db[user].email, ' ', db[user].password, ' ', db[user].phoneNumber, ' ', db[user].encryption_key, ' ', db[user].recovery_key, ' ', db[user].account_status, ' ', db[user].account_type, ' ', db[user].account_level, ' ', db[user].minimum_opening_deposit, ' ', db[user].currency, ' ', db[user].current_amount, ' ', db[user].loanStatus, ' ', db[user].monthly_income, ' ', db[user].loan_amount, ' ', db[user].loan_rate, ' ', db[user].address, ' ', db[user].trans_amount_limit_perday);
            for(register int trc=0 ; trc <= space_array[user]-20 ; trc++){
                fprintf(fptr,"%c%s", ' ', db[user].tr[trc].note);
            }
            fprintf(fptr,"%c",'\n'); // တကြောင်းပြီးလျှင် တကြောင်းဆင်း
        }
    }
    printf("Recording complete to 'encrypted_data.txt!'\n");
}

/* Get Time */
void get_time()
{
    time_t tm;
    time(&tm);
    int time_space_counter = 0;

    printf("Current Date/Time = %s\n",ctime(&tm));

    FILE *fptr = fopen("mytime.txt","w");
    fprintf(fptr,"%s",ctime(&tm));
    fclose(fptr);

    int index = 0;
    getCTime[0].current_time[index] = '-';

    FILE *fptr2 = fopen("mytime.txt","r");
    char c = fgetc(fptr2);
    while(!feof(fptr2)){
        if(c == ' '){
            time_space_counter++;

            if(time_space_counter == 1){ 
                getCTime[0].current_time[index] = '!'; //Sun!Mar--2-03:12:54@2025
                c = fgetc(fptr2);
                index++;
            }else if(time_space_counter == 5){ 
                getCTime[0].current_time[index] = '@'; //Sun!Mar--2-03:12:54@2025
                c = fgetc(fptr2);
                index++;
            }else{
                getCTime[0].current_time[index] = '-'; //Sun!Mar--2-03:12:54@2025
                c = fgetc(fptr2);
                index++;
            }

        }else{
            getCTime[0].current_time[index] = c;
            c = fgetc(fptr2);
            index++;
        }
    }
    fclose(fptr2);
    printf("\nremoved space : %s",getCTime[0].current_time);

}

/* Transaction Record From to */
void transaction_record(int userDBindex,int uFound,char who,unsigned int amount) //who = transmit or receive
{
    integer_to_charArrayFun(amount);
    int money_quant_counter = char_counting(int_to_charArray);
    int transfer = char_counting(db[userDBindex].name); //userDBindex = transmitter
    int accept = char_counting(db[uFound].name);    //uFound = receiver

    if(who == 't'){
        char toInsert1[5] = {'F','r','o','m',':'};
        char toInsert2[4] = {':','t','o',':'};

        int indexPoint = 0; // From:
        for(int x = indexPoint ; x < 5 ; x++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[x] = toInsert1[x];
            indexPoint++; //5
        }

        /* Insertion Name */
        int nameIndex = 0;
        int endPoint = indexPoint + transfer; // From:TransmitterName
        for(int x = indexPoint ; x < endPoint ; x++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[indexPoint] = db[userDBindex].name[nameIndex];
            nameIndex++;
            indexPoint++; // 5 + transmitterName
        }

        nameIndex = 0;
        endPoint = indexPoint + 4; // From:TransmitterName:to:
        for(int x = indexPoint ; x < endPoint ; x++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[indexPoint] = toInsert2[nameIndex];
            nameIndex++;
            indexPoint++; // 5 + transmitterName + 4
        }

        nameIndex = 0;
        endPoint = indexPoint + accept; // From:TransmitterName:to:ReceiverName
        for(int x = indexPoint ; x < endPoint ; x++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[indexPoint] = db[uFound].name[nameIndex];
            nameIndex++;
            indexPoint++; // 5 + transmitterName + 4 + receiverName
        }

        /* Adding Time to Transaction Record */
        nameIndex = 0;
        get_time();
        db[userDBindex].tr[space_array[userDBindex] - 19].note[endPoint] = ':';
        endPoint++;

        for(int win = endPoint ; win < 24 + endPoint ; win++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[win] = getCTime[0].current_time[nameIndex];
            nameIndex++;
        }
        
        /* Insert Amount to Transaction Record */
        endPoint = endPoint + 24;
        db[userDBindex].tr[space_array[userDBindex] - 19].note[endPoint] = '$';
        endPoint++;
        
        nameIndex = 0;
        for(int wa=endPoint ; wa < endPoint + money_quant_counter ; wa++){
            db[userDBindex].tr[space_array[userDBindex] - 19].note[wa] = int_to_charArray[nameIndex];
            nameIndex++;
        }

        db[userDBindex].tr[space_array[userDBindex] - 19].note[endPoint + money_quant_counter] = '-'; 
        space_array[userDBindex] = space_array[userDBindex] + 1;
    
    /* Receiver Transaction Record */    
    }else{
        char receiveFrom[14] = {'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};
        int indexPoint = 0;
        int endpoint = 0;
        int reIndex = 0;

        for(int i=0 ; i < accept ; i++){
            db[uFound].tr[space_array[uFound] - 19].note[i] = db[uFound].name[i];
            indexPoint++;
        }

        endpoint = accept + 14; // ReceiverName-Receiver-From-
        for(int i=indexPoint ; i < endpoint ; i++){
            db[uFound].tr[space_array[uFound] - 19].note[i] = receiveFrom[reIndex];
            reIndex++;
        }

        reIndex = 0;
        int toendpoint = endpoint + transfer; // ReceiverName-Receiver-From-TransmitterName
        for(int a = endpoint ; a < toendpoint ; a++){
            db[uFound].tr[space_array[uFound] - 19].note[a] = db[userDBindex].name[reIndex];
            reIndex++;
        }

        reIndex = 0;
        get_time();
        for(int win = toendpoint ; win < 24 + toendpoint ; win++){
            db[uFound].tr[space_array[uFound] - 19].note[win] = getCTime[0].current_time[reIndex];
            reIndex++;
        }

        /* Insert Amount to Transaction Record */
        toendpoint = 24 + toendpoint;
        db[uFound].tr[space_array[uFound]-19].note[toendpoint] = '$';
        toendpoint++;

        for(int gcc=0 ; gcc < money_quant_counter ; gcc++){
            db[uFound].tr[space_array[uFound]-19].note[toendpoint] = int_to_charArray[gcc];
            toendpoint++;

        }
        db[uFound].tr[space_array[uFound]-19].note[toendpoint] = '-'; 
        space_array[uFound] = space_array[uFound] + 1; 
    }
}

/* Type Changing */
void integer_to_charArrayFun(unsigned int integer)
{
    int index = 0;
    FILE *fptr = fopen("whw.txt","w");

    if(fptr == NULL){
        printf("[-]Error at integer_to_charArrayFun\n");
    }else{
        fprintf(fptr,"%d",integer);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("whw.txt","r");
    char c = fgetc(fptr2);

    while(!feof(fptr2)){
        int_to_charArray[index] = c;
        c = fgetc(fptr2);
        index++;
    }
    fclose(fptr2);
}

unsigned int char_to_integer_fun(char char_array[50])
{
    unsigned int char_to_int_data = 0;
    FILE *fptr = fopen("whw.txt","w");

    if(fptr == NULL){
        printf("[-]Error\n");
    }else{
        fprintf(fptr,"%s",char_array);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("whw.txt","r");

    if(fptr2 == NULL){
        printf("[-]Error at char_to_integer_fun\n");
    }else{
        fscanf(fptr2,"%d",&char_to_int_data);
    }
    return char_to_int_data;
}

/* Last Record */
void time_class(int user_index)
{
    time_class_last_record(user_index);
}

void time_class_last_record(int user_index) //to take user last record
{
    int last = 0;
    int records = space_array[user_index] - 20;
    for(int i=0 ; i <= records ; i++){
        last = i;
    }
    printf("\nUser Last Record : %s\n",db[user_index].tr[last].note);
    time_class_get_date(db[user_index].tr[last].note);
}

/* Get Month and Day */
void time_class_get_date(char last_record[])
{
    int last_record_counter = char_counting(last_record);

    int i = 0;
    for(i=0 ; i < last_record_counter ; i++){
        if(last_record[i] == '!'){
            break;
        }
    }
    i++;

    for(int a=0 ; a < 3 ; a++){ //for month
        month[a] = last_record[i];
        i++;
    }
    printf("get month : %s\n",month);

    day[0] = last_record[i+1]; //for day
    day[1] = last_record[i+2]; //for day
    unsigned int get_day = char_to_integer_fun(day);
    printf("get day : %d\n",get_day);

    int z = 0; 
    for(z=0 ; z < last_record_counter ; z++){ //for year
        if(last_record[z] == '@'){
            break;
        }
    }

    for(int x=0 ; x<4 ; x++){
        z++;
        year[x] = last_record[z];
    }
    unsigned int get_year = char_to_integer_fun(year);
    printf("year : %d\n",get_year); 
}