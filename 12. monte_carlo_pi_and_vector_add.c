// Yuhyun Kim
// CDS 251
// Assignment 12
// 12.4.2024
// This program calculates pi using the Monte Carlo method and provides a vector addition function, 
// both callable from Python via C function bindings.


#include <stdlib.h>
#include <stdio.h>
// test function to demonstrate how to 
// call C functions from python
double calc_pi(int iterations, int seed) 
{
  int points_inside = 0;

  srand(seed);

for (int i = 0; i < iterations; i++) {
        // Generate random numners
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if the points are in the circle
        if (x * x + y * y <= 1.0) {
            points_inside++;
        }
    }
   // Calculate PI by Monte Carlo method
  double PI = 4.0 * points_inside / iterations;
  printf("PI: %.15f\n", PI);
  return PI;
}


void vector_add(double* x, double* y, double * result, int n) 
{
  double sum = 0;
  for (int i=0; i<n; i++) 
  {
    result[i] = x[i] + y[i];
  }
}


