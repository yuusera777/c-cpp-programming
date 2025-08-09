============================================================================================================== /*
Title: Linear and Exponential Regression without Arrays
Author: Yuhyun Kim
Date: 10.29.2024

Description:
  Computes linear and exponential regression parameters without using arrays or retaining past variables.
  Reads input (x, y) pairs, updates values progressively, and prints the best-fit equations.

Inputs:
  - File: "RegressionData.txt"
      Each line: x y

Outputs:
  - Console: regression equations and coefficients

Key Skills Demonstrated:
  - Regression model derivation (linear & exponential)
  - Progressive calculation without storing datasets
  - Avoidance of old variable storage

The Most Important Thing:
  - Memory-efficient regression analysis suitable for large datasets.
*/ ============================================================================================================== 




#include <cstdio>
#include <cmath>

FILE* open_file(const char* fname, const char* mode) {
    FILE* fptr = fopen(fname, mode);
    if (fptr == NULL) {
        printf("Unable to open file: %s \n", fname);
        return NULL;
    }
    return fptr;
}

void close_file(FILE* fptr) {
    if (fptr != NULL) {
        fclose(fptr);
        fptr = NULL;
    }
}

// Program A
void program_A() {
    char filename[] = "/Users/klieeu777/Desktop/cds251/week7/Edata.txt";
    FILE* fptr = open_file(filename, "r");
    if (fptr == NULL) return;

    // Variables for the means and sum of squares of x deviations
    float x, y;
    float Sxx =  0.0f;
    float Sxy =  0.0f;
    float xMean = 0.0f, yMean = 0.0f;
    float M = 0.0f, b = 0.0f;

    FILE* OutputA = fopen("OutputA.txt", "w");
    if (OutputA == NULL) {
        printf("Unable to open output file for Program A.\n");
        close_file(fptr);
        return;
    }


    
   for (int i = 1; i <= 200; i++) {
            
        fscanf(fptr, "%f %f", &x, &y);  // Read number and allocae to x and y

        // Update cumulative means of x and y
        xMean = xMean + (x - xMean) / i;
        yMean = yMean + (y - yMean) / i;

        // Update sum of squares of x deviations and sum of the product of x and y deviations
        Sxx = Sxx + ((i - 1) / (float)i) * (x - xMean) * (x - xMean);
        Sxy = Sxy + ((i - 1) / (float)i) * (x - xMean) * (y - yMean);
    

        // Compute Slope M and Constant b
        M = Sxy / Sxx ;
        b = yMean  - M * xMean ;
   }

    fprintf(OutputA, "Slope M = %f\n", M);
    fprintf(OutputA, "Constant b = %f\n", b);

    // Output
    printf("Slope M = %f\n", M);
    printf("Constant b = %f\n", b);

    fclose(fptr);
    fclose(OutputA);
}

// Program B
void program_B() {
    char filename[] = "/Users/klieeu777/Desktop/cds251/week7/Edata.txt";
    FILE* fptr = open_file(filename, "r");  
    if (fptr == NULL) return;
    
    float x, y;
    float xMean = 0.0f, lnyMean = 0.0f;
    float Sxx = 0.0f, lnSxy = 0.0f;
    float a = 0.0f, b = 0.0f;

    FILE* OutputB = fopen("OutputB.txt", "w");
    if (OutputB == NULL) {
        printf("Unable to open output file for Program B.\n");
        close_file(fptr);
        return;
    }

    
    
    for (int i = 1; i <= 200; i++) {
            
        fscanf(fptr, "%f %f", &x, &y);  // Read number and allocae to x and y

        float lny = log(y);  // Compute log(y)
        

        // Update cumulative meanss of x and y
        xMean = xMean + (x - xMean) / i;
        lnyMean = lnyMean + (lny - lnyMean) / i;

        // Update sum of squares of x deviations and sum of the product of x deviations and log(y) deviations
        Sxx = Sxx + (x - xMean) * (x - xMean);
        lnSxy = lnSxy + (x - xMean) * (lny - lnyMean);
    

        // Compute Exponent a and Coefficient b 
        a = lnSxy / Sxx ;
        b = exp(lnyMean - a * xMean);

    }

    fprintf(OutputB, "Exponent a = %f\n", a);
    fprintf(OutputB, "Coefficient b = %f\n", b);

    // Output
    printf("Exponent a = %f\n", a);
    printf("Coefficient b = %f\n", b);

    fclose(fptr);
    fclose(OutputB);
}

int main() {
    int choice;   // Choose one of the two programs to view its output
    printf("Choose Program 1 or 2: ");
    scanf("%d", &choice);

    if (choice == 1) {
        program_A();
    } else if (choice == 2) {
        program_B();
    } 

    return 0;
}

