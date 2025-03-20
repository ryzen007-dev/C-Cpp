#include <stdio.h>
float add(float a,char z,float b);
float sub(float a,char c,float b);
float mul(float a,char c,float b);
float div(float a,char c,float b);

int main(){
    float x=0, y=0;
    char c;
    printf("Welcome to the Basic Arithmetic Calculator!\nEnter an operation in the format : number1 operator number2\nSupported operators : + (add), - (subtract), * (multiply), / (divide)\n");
    printf("\nEnter your calculation : ");
    scanf("%f %c %f",&x,&c,&y);
    if(c == '+'){
        printf("Result : %.2f\n",add(x,c,y));
    }else if(c == '-'){
        printf("Result : %.2f\n",sub(x,c,y));
    }else if(c == '*'){
        printf("Result : %.2f\n",mul(x,c,y));
    }else if(c == '/'){
        if (y == 0){
            printf("Error : Division by zero is not allowed\n");
        }else{
            printf("Result : %.2f\n",div(x,c,y));
        }
    }else{
        printf("Error: Unsupported operator ''. Please use +, -, *, or /\n");
    }
    return 0;
}

float add(float a,char c,float b){
    return a + b;
}

float sub(float a,char c,float b){
    return a - b;
}

float mul(float a,char c,float b){
    return a * b;
}

float div(float a,char c,float b){
    return a / b;
}
