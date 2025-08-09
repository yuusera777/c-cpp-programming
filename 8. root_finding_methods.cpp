// Yuhyun Kim
// CDS 251
// Assignment 8
// 11.04.2024
// This assignment is for finding roots of a non linear equation by Newton's Method, Bisection Method and Secant Method.

#include <iostream>
#include <cmath>
#include <cstdio>

const double Tolerance = 1.0e-14;    //Settinf tolerance

// Function to find roots
double MyFunc(double x) {
    return sin(x) - 0.15 * x + 1.5;
}

// Derivative function for Newton's method
double Myfunc_derivative(double x) {
    return cos(x) - 0.15;
}

// Newton's Method

double newton_method(double x0, int& attempts) {
    const int max_attempts = 50;
    double x = x0;
    for (attempts = 0; attempts < max_attempts; ++attempts) {
        double fx = MyFunc(x);
        double dfx = Myfunc_derivative(x);
        if (fabs(dfx) < Tolerance) break;

        double x_next = x - fx / dfx;

        if (fabs(x_next - x) < Tolerance) return x_next;

        x = x_next;
    }
    return x;
}

// Bisection Method

double bisection_method(double a, double b, int& attempts) {
    const int max_attempts = 1000;
    double m; //mid point
    attempts = 0;

    while (attempts < max_attempts) {
        m = (a + b) / 2.0;
        double fm = MyFunc(m);
        
        if (fabs(fm) < Tolerance) return m;
        
        if (MyFunc(a) * fm < 0) {
            b = m;
        } else {
            a = m;
        }
        
        ++attempts;
    }
    return m;
}

// Secant Method
double secant_method(double x1, double x2, int& attempts) {
    const int max_attempts = 1000;
    double x3;
    attempts = 0;

    while (attempts < max_attempts) {
        double fx1 = MyFunc(x1);
        double fx2 = MyFunc(x2);
        
        if (fabs(fx1 - fx2) < Tolerance) break;

        x3 = x1 - fx1 * (x1 - x2) / (fx1 - fx2);

        if (fabs(x3 - x1) < Tolerance) return x3;

        x2 = x1;
        x1 = x3;

        ++attempts;
    }
    return x1;
}

// Creating a table using printf function 
void table(const char* method, double root, double x0, double x1, double f_root, int iterations) {
    printf("%-10s %15.15f %15.15f %15.15f %15.15f %10d\n", method, root, x0, x1, f_root, iterations);
}

int main() {
    printf("%-10s %15s %15s %15s %15s %10s\n", "Method", "Root", "Starting x0", "Starting x1(except Newton's method)", "f(Root)", "Iterations");
    printf("----------------------------------------------------------------------------------------------------------\n");

    // Setting an initial point for Newton's Method 
    double newton_starting_points[] = { 3.0, 6.5, 10.0, 12.5, 16.0 };  
    for (int i = 0; i < sizeof(newton_starting_points) / sizeof(newton_starting_points[0]); ++i) {
        int iterations;
        double root = newton_method(newton_starting_points[i], iterations);
        table("Newton", root, newton_starting_points[i], 0.0, MyFunc(root), iterations);
    }

    // Setting two startnig points for Bisection Method
    double bisection_intervals[][2] = { {4.0, 5.0}, {5.0, 6.0}, {9.0, 10.0}, {12.0, 14.0}, {14.0, 15.0} };
    for (int i = 0; i < sizeof(bisection_intervals) / sizeof(bisection_intervals[0]); ++i) {
        double a = bisection_intervals[i][0];
        double b = bisection_intervals[i][1];

        // Check sign
        if (MyFunc(a) * MyFunc(b) > 0) {
            printf("Error: f(a) and f(b) don't have opposite signs in interval [%.15f, %.15f].", a, b);
            continue;
        }

        int iterations;
        double root = bisection_method(a, b, iterations);
        table("Bisection", root, a, b, MyFunc(root), iterations);
    }

    // Setting two startnig points for Secant Method
    double secant_starting_2points[][2] = { {4.0, 5.0}, {5.0, 6.0}, {9.0, 10.0}, {12.0, 14.0}, {14.0, 15.0} };
    for (int i = 0; i < sizeof(secant_starting_2points) / sizeof(secant_starting_2points[0]); ++i) {
        int iterations;
        double root = secant_method(secant_starting_2points[i][0], secant_starting_2points[i][1], iterations);
        table("Secant", root, secant_starting_2points[i][0], secant_starting_2points[i][1], MyFunc(root), iterations);
    }

    return 0;
}

