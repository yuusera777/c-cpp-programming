// Yuhyun Kim
// ykim213@gmu.edu, katriyh777@gmail.com
// CDS 251
// Assignment 1 
// 09.04.2024

// This program is for Assignment 1.
// To make sure the program used in the class operating well 
// in my computer and practice puuting important elements 
// such as name, email address, course name, and date in programming

#include <stdio.h>

int main()
{// Declare a character array
    char myname[] = "Yuhyun Kim";
    char email_address[] = "ykim213@gmu.edu, katriyh777@gmail.com";
    char course_number[] = "CDS 251";
    char assignment_number[] = "Assignment 1";
    char duedate[] = "09. 04. 2024";

    // print my name, email address, course number, assignment number and Due date
    // to the console
    printf("%s \n", myname);  // display one variable in one line
    printf("%s \n", email_address);
    printf("%s \n", course_number);
    printf("%s \n", assignment_number);  
    printf("%s \n", duedate); // add a newline character for nicer console formatting

    return 0;
}
