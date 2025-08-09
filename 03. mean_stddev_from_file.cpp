// Yuhyun Kim
// CDS 251
// Assignment 3
// 09.18.2024
// This program is for calculating mean and standard deviation by opening and reading txt file including numbers list, then allocating memory for an array 
// using formulas.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {
    FILE *file_ptr = fopen("Numbers1.txt", "r");  // Open the file Numbers1.txt

    if (file_ptr == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    //Read the first integer from the file
    int num = 0;
    fscanf(file_ptr, "%d\n", &num);

    //Allocate memory for an array
    int *Numbers1 = (int *)malloc(num * sizeof(int));

    //Initialize variables for mean and Q (standard deviation)
    float mean = 0.0;
    float Q = 0.0;
    float diff = 0.0;

    //Read one number at a time from the file and update the mean and Q
    for (int i = 0; i < num; i++) {
        fscanf(file_ptr, "%f\n", &Numbers1[i]);  //Read number
                                     
        //Update formulas for mean and Q (for standard deviation)
        diff = Numbers1[i] - mean;
        mean = mean + diff / (i + 1);
        Q = Q + diff * (Numbers1[i] - mean);
    }

    //Calculate variance and standard deviation (using sqrt() only after the loop)
    float var = Q / num;
    float sd = sqrt(var);

    //Print the mean and standard deviation
    printf("Mean: %f\n", mean);
    printf("Standard Deviation: %f\n", sd);

    //Deallocate memory for the array by f function and close the file
    free(Numbers1);
    fclose(file_ptr);

    //Print 'Done!' to the screen
    printf("Done!\n");

    return 0;
}
