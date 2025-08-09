/* ==============================================================================================================
Title: Monte Carlo π Estimation & Vector Addition (C functions callable from Python)
Author: Yuhyun Kim
Date: 12.4.2024

Description:
  Provides two standalone C functions:
    - calc_pi(iterations, seed): estimates π by Monte Carlo sampling in the unit square (prints and returns π).
    - vector_add(x, y, result, n): elementwise vector addition.
  Designed to be invoked from Python (e.g., ctypes/cffi); no main() provided.

Inputs:
  - Function parameters (no external files):
      iterations (int), seed (int), and pointers/lengths for vector_add

Outputs:
  - Console: "PI: <value>" printed by calc_pi
  - result[] filled by vector_add

Key Skills Demonstrated:
  - Probabilistic estimation (Monte Carlo)
  - C ABI surface for Python interop
  - Safe pointer-based array operations

The Most Important Thing:
  - Clean, reusable C functions suitable for direct binding from Python.
============================================================================================================== */



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


