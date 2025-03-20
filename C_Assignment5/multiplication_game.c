#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int num1, num2;
    int answer, userAnswer;
    time_t startTime, endTime;

    srand(time(NULL));  // Initialize random seed only once

    printf("Welcome to the Multiplication Game!\n");
    printf("You have 6 seconds to answer each question. Let's start!\n");

    while (1) {
        num1 = (rand() % 10) + 1;
        num2 = (rand() % 10) + 1;
        answer = num1 * num2;

        printf("What is %d x %d? ", num1, num2);
        startTime = time(NULL);
        scanf("%d", &userAnswer);
        endTime = time(NULL);

        if (endTime - startTime > 6) {
            printf("Time's up! You took too long.\n");
            break;
        }

        if (answer == userAnswer) {
            printf("Correct!\n");
        } else {
            printf("Wrong! The correct answer was %d\nThanks for playing!\n", answer);
            break;
        }
    }

    return 0;
}


