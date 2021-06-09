//operations.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <ctype.h>

/* Andy Fleischer - CS201 - Program #4 - 5/30/2021
 * -----------------------------------------------
 * This program takes in up to 15 command line
 * arguments, and performs an operation based on
 * the menu item selected by the user.
 * Functionalities for add, subtract, multiply,
 * divide, modulo, and reverse. */

struct menu //menu struct, holds number of choices and array of strings of choices
{
    int num_choices;
    char* choices[7];
};

void
print_menu(struct menu to_print) //prints out the choices of the menu, numbered
{
    printf("\n");
    for (int i = 0; i < to_print.num_choices; i++)
        printf("%d. %s\n", i, to_print.choices[i]);
    printf("\n");
}

int
base_of(char* check) //returns whether a string is base 10 or base 16
{
    int start = (check[0] == '-' ? 1 : 0); //checks for negative
    return (check[start] == '0' && (toupper(check[start+1]) == 'X')) ? 16 : 10;
}

void
quit(int length, char* nums[]) //exit the program
{
    exit(EXIT_SUCCESS);
}

void
add(int length, char* nums[]) //add all the items in the nums array
{
    char* end;
    int num = strtol(nums[1], &end, base_of(nums[1])); //get first one for printing
    int sum = num;

    printf("%d ", num); 
    for (int i = 2; i < length; i++) //loop through the rest of the array
    {
        num = strtol(nums[i], &end, base_of(nums[i])); //convert, add, and print
        sum += num;
        printf("+ %d ", num);
    }
    printf("= %d\n", sum);
}

void
subtract(int length, char* nums[]) //subtract all the items in the nums array, left to right
{
    char* end;
    int num = strtol(nums[1], &end, base_of(nums[1])); //get first one for printing
    int sum = num;

    printf("%d ", num); 
    for (int i = 2; i < length; i++) //loop through rest of array
    {
        num = strtol(nums[i], &end, base_of(nums[i])); //convert, subtract, and print
        sum -= num;
        printf("- %d ", num);
    }
    printf("= %d\n", sum);
}

void
multiply(int length, char* nums[]) //multiply all items in the array
{
    char* end;
    int num = strtol(nums[1], &end, base_of(nums[1])); //get first one for printing
    int sum = num;

    printf("%d ", num); 
    for (int i = 2; i < length; i++) //loop through rest of array
    {
        num = strtol(nums[i], &end, base_of(nums[i])); //convert, multiply, and print
        sum *= num;
        printf("* %d ", num);
    }
    printf("= %d\n", sum);
}

void
divide(int length, char* nums[]) //divide the first number in the array by the second number
{
    char* end;
    int num1 = strtol(nums[1], &end, base_of(nums[1])); //get the numbers and their quotient
    int num2 = strtol(nums[2], &end, base_of(nums[2]));
    float quotient = (float)num1 / (float)num2;
    
    printf("%d / %d = %f\n", num1, num2, quotient); //print out results
}

void
modulo(int length, char* nums[]) //modulo the first number in the array by the second
{
    char* end;
    int num1 = strtol(nums[1], &end, base_of(nums[1])); //get the numbers and result
    int num2 = strtol(nums[2], &end, base_of(nums[2]));
    int answer = num1 % num2;
    
    printf("%d mod %d = %d\n", num1, num2, answer); //print out results
}

void
reverse(int length, char* inputs[]) //reverse the arguments and characters within them
{
    for (int i = length - 1; i >= 1; i--) //loop through arguments backwards
    {
        for (int j = strlen(inputs[i]) - 1; j >= 0; j--) //loop through words backwards
            printf("%c", inputs[i][j]); //print character
        printf(" ");
    }
    printf("\n");
}

//function dispatch table for above functions
void (*operations[])(int length, char* nums[]) = {
    quit,
    add,
    subtract,
    multiply,
    divide,
    modulo,
    reverse,
};

int
main(int argc, char* argv[]) //main method
{
    if (argc > 16 || argc < 3) //check number of args
    {
        printf("Invalid number of arguments. Must supply between 2 and 15 arguments.\n");
        exit(EXIT_FAILURE);
    }
    struct menu my_menu; //set up menu
    my_menu.num_choices = 7;
    my_menu.choices[0] = "Exit";
    my_menu.choices[1] = "Addition";
    my_menu.choices[2] = "Subtraction";
    my_menu.choices[3] = "Multiplication";
    my_menu.choices[4] = "Division";
    my_menu.choices[5] = "Modulo";
    my_menu.choices[6] = "Reverse Input";

    int choice = -1;
    while (choice != 0) //main program loop
    {
        print_menu(my_menu);
        printf("Menu item: ");

        char* end; //take in input for menu item choice
        char buf[10];
        fgets(buf, sizeof buf, stdin);
        buf[strlen(buf) - 1] = 0;
        int choice = strtol(buf, &end, 10);

        if (choice > 6 || choice < 0) //check if the choice is valid
            printf("Invalid menu selection. Please give a number between 0 and 6.\n");
        else
            operations[choice](argc, argv); //if valid, call proper function from FDT
    }

    exit(EXIT_SUCCESS);
}
