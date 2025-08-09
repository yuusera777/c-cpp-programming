/* 
Title: Console Print – Personal & Course Info
Author: Yuhyun Kim
Email: ykim213@gmu.edu, katriyh777@gmail.com
Date: 09.04.2024

Description:
  Prints personal and course information (name, email, course, assignment number, due date)
  to the console. Introductory exercise to verify toolchain and practice formatted output.

Inputs:
  - None (all values are defined as string literals in the code)

Outputs:
  - Console lines:
      name
      email_address
      course_number
      assignment_number
      due_date

Key Skills:
  - Basic C I/O with printf
  - String literals and character arrays
  - Simple program structure and console formatting

The Most Important Thing:
  - Clear console output that verifies the environment and I/O basics.
*/



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
