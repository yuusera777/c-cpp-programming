/* ==============================================================================================================
Title: Numerical Integration (Midpoint & Simpson's Rule)
Author: Yuhyun Kim
Date: 11.13.2024

Description:
  Calculates definite integrals using both the Midpoint Rule and Simpson's Rule.
  Compares computed areas with exact integral values and reports absolute/relative errors.

Inputs:
  - User input: lower limit, upper limit
  - Step sizes: predefined array {1.0, 0.5, 0.25}

Outputs:
  - Console: exact area, computed area by each method, and error metrics

Key Skills Demonstrated:
  - Numerical integration techniques
  - Error analysis (absolute & relative)
  - Function pointer usage in integration routines

The Most Important Thing:
  - Shows practical differences between integration methods in terms of accuracy.
============================================================================================================== */



#include <stdio.h>
#include <math.h>

// Define the function to integral
void Myfunc(double x, double *result) {
    *result = exp(-x) * pow(sin(x), 2);  // pointer
}

// Function to calculate the exact integral value
void exactIntegral(double x, double *result) {
    *result = (exp(-x) / 10) * (cos(2 * x) - 2 * sin(2 * x) - 5);     // pointer
}


// Calculate integral by Midpoint Rule
void Midpoint(double a, double b, double h, double *area) {
    int n = (int)((b - a) / h);
    double sum = 0.0;
    double fx;

    for (int i = 1; i <= n; i++) {
        double xMiddle = a + (i - 1) * h + 0.5 * h;    // Calculate Mid point
        Myfunc(xMiddle, &fx);                          // Calculate value at the Mid point 
        sum += fx * h;                                 // Add the area of box to accumulated sum
    }
    *area = sum;                                       // pointer
}


// Calculate integral by Simpson's Rule
void Simpsons(double a, double b, double h, double *area) {
    int n = (int)((b - a) / h);
    double sum = 0.0;
    double fx_left, fx_middle, fx_right;

    for (int i = 1; i <= n; i++) {
        double x_left = a + (i - 1) * h;              // x Left point
        double x_middle = x_left + 0.5 * h;           // x Middle point
        double x_right = x_left + h;                  // x Right point

        Myfunc(x_left, &fx_left);                     // Function value at left
        Myfunc(x_middle, &fx_middle);                 // Function value at middle
        Myfunc(x_right, &fx_right);                   // Function value at right

        sum += (h / 6) * (fx_left + 4 * fx_middle + fx_right);  // Simpson's Rule formula
    }
    *area = sum;                                       // Pointer
}


int main() {
    double a, b, h, exactStart, exactEnd, exactValue;
    double step_sizes[] = {1.0, 0.5, 0.25};  // Increment
    double area_midpoint, area_simpson, absoluteError, relativeError;
   
    // Input limit
    printf ("What is the 1st limit of integration?");
    scanf("%lf", &a);
    printf ("What is the 2nd limit of integration?");
    scanf("%lf", &b);



    // Calculate the exact values
    exactIntegral(b, &exactEnd);
    exactIntegral(a, &exactStart);
    exactValue = exactEnd - exactStart;


    // Print Exact value of area
    printf("\nExact Value of the Area: %.10f\n\n", exactValue);

    // Table header
    printf("Method\t\tStep Size\tComputed Area\tAbsolute Error\tRelative Error\n");
    printf("----------------------------------------------------------------------------\n");
    

    // for Loop through step sizes and compute for each
    for (int i = 0; i < 3; i++) {
        double h = step_sizes[i];

        // Calculate Midpoint Rule
        Midpoint(a, b, h, &area_midpoint);
        absoluteError = fabs(exactValue - area_midpoint);
        relativeError = absoluteError / fabs(exactValue);
        printf("Midpoint Rule\t%.2f\t\t%.10f\t%.10f\t%.10f\n", h, area_midpoint, absoluteError, relativeError);

        // Calculate Simpson's Rule
        Simpsons(a, b, h, &area_simpson);
        absoluteError = fabs(exactValue - area_simpson);
        relativeError = absoluteError / fabs(exactValue);
        printf("Simpson's Rule\t%.2f\t\t%.10f\t%.10f\t%.10f\n", h, area_simpson, absoluteError, relativeError);
    }

    return 0;
}

  


