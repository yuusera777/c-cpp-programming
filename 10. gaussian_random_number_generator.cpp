// Yuhyun Kim
// CDS 251
// Assignment 10-1
// 11.15.2024
// This assignment is for generating random numbers by Gaussian Random Generator and write to the new file.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Gaussian Random Generator function
void gaussian_random_generator(double *rNum1, double *rNum2) {
    double x1, x2, w;
    do {
        // Infinite do loop until no rejection
        // Generate 2 numbers between -1 and 1
        x1 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        x2 = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        w = x1 * x1 + x2 * x2;
        if (w < 1.0) break; // Valid numbers
    } while (1);
    w = sqrt((-2.0 * log(w)) / w);
    *rNum1 = x1 * w;
    *rNum2 = x2 * w;
}


// Function to genrate random muners and store to the file 
void generate_numbers(const char *filename, double mean1, double StDev1, int count1,   // count1: the numbers of random numbers for the first distribution
                      double mean2, double StDev2, int count2) {      // count2: the numbers of random numbers for the second distribution
    // Open file
    FILE *file = fopen(filename, "w");
    if (file == NULL) { 
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    double rNum1, rNum2;

    // Generate the randon numbers of the first distribution
    for (int i = 0; i < count1; i += 2) {
        gaussian_random_generator(&rNum1, &rNum2);  // Generate the random numners and allocate to rNum1 and rNum2
        fprintf(file, "%.10f\n", StDev1 * rNum1 + mean1); 
        if (i + 1 < count1) { // Write the second random numebrs after checking the range
            fprintf(file, "%.10f\n", StDev1 * rNum2 + mean1);
        }
    }

    // Generate the randon numbers of the second distribution
    for (int i = 0; i < count2; i += 2) {
        gaussian_random_generator(&rNum1, &rNum2); // Generate the random numners and allocate to rNum1 and rNum2
        fprintf(file, "%.10f\n", StDev2 * rNum1 + mean2); 
        if (i + 1 < count2) { // Write the second random numebrs after checking the range
            fprintf(file, "%.10f\n", StDev2 * rNum2 + mean2);
        }
    }

    fclose(file); 
}

int main() {
    int seed;
    // Input seed from users 
    printf("Enter an integer seed for the random numbers generator: ");
    scanf("%d", &seed);
    srand(seed);   // Initialize Random Number Generator

    // Generate the fandim numbers and store to "Bumps.txt" file
    generate_numbers("Bumps.txt", 22.0, 2.5, 13000, 15.5, 1.0, 7000);

    return 0; 
}
