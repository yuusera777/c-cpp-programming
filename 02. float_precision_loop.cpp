// Yuhyun Kim
// CDS 251
// Assignment 2
// 09.11.2024
// This program is for programming C using float type and iterate addition using for loop.


#include <stdio.h>

int main()
{// Declare variables with float type
    float var1 = 1.0f;  // Make sure they are float by putting "f" after float numbers
    float var2 = 2.0f;
    

    //Add 1.e-7 10 million times by using for loop
    for (int i = 0; i < 10000000; ++i) { // Set the initial value of i with 0 when for loop is interated only at first
                                        // Condition of iterating for loop, just shen 1 is smaller than 10 million
                                        // Result of i at the end of each iteration of for loop
    var1 = var1 + 1.e-7f;      //Add 1.e-7 to both var1 and var2
    var2 = var2 + 1.e-7f; 
    
        }

    printf("var1: %f\n", var1);  // Print final  values of var1 and var2
    printf("var2: %f\n", var2);  


    return 0;
}
