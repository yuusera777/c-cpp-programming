// Yuhyun Kim
// CDS 251
// Assignment 11
// 11.20.2024
// This program implements piecewise linear and quadratic polynomial interpolation (using Cramer's Rule) 
// on data from a file, compares results with the exact sine function, and calculates absolute and relative errors.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1003
#define DATA_TYPE double

// Function to read data from a file
void read_data(const char* filename, int* n, DATA_TYPE x[], DATA_TYPE y[]) {
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }

    // Read the number of data points
    fscanf(fptr, "%d", n);

    // Read x and y values
    for (int i = 0; i < *n; i++) {
        fscanf(fptr, "%lf %lf", &x[i], &y[i]);
    }

    fclose(fptr);
}

// Function to perform piecewise linear interpolation
DATA_TYPE linear_interpolation(DATA_TYPE x[], DATA_TYPE y[], int n, DATA_TYPE target_x) {
    for (int i = 0; i < n - 1; i++) {
        if (x[i] <= target_x && target_x <= x[i + 1]) {
            return y[i] + (target_x - x[i]) * (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
        }
    }
    printf("Error: Target x is out of bounds.\n");
    exit(1);
}

// Function to calculate coefficients for quadratic interpolation using Cramer's Rule
void calculate_coefficients(DATA_TYPE x[], DATA_TYPE y[], DATA_TYPE coeffs[]) {
    DATA_TYPE matrix[3][3] = {
        {x[0] * x[0], x[0], 1.0},
        {x[1] * x[1], x[1], 1.0},
        {x[2] * x[2], x[2], 1.0}
    };

    DATA_TYPE det_matrix = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
                         - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
                         + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    for (int i = 0; i < 3; i++) {
        DATA_TYPE temp_matrix[3][3];
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                temp_matrix[row][col] = matrix[row][col];
            }
        }
        for (int row = 0; row < 3; row++) {
            temp_matrix[row][i] = y[row];
        }

        DATA_TYPE det_temp = temp_matrix[0][0] * (temp_matrix[1][1] * temp_matrix[2][2] - temp_matrix[1][2] * temp_matrix[2][1])
                           - temp_matrix[0][1] * (temp_matrix[1][0] * temp_matrix[2][2] - temp_matrix[1][2] * temp_matrix[2][0])
                           + temp_matrix[0][2] * (temp_matrix[1][0] * temp_matrix[2][1] - temp_matrix[1][1] * temp_matrix[2][0]);

        coeffs[i] = det_temp / det_matrix;
    }
}

// Function to calculate the quadratic interpolation value
DATA_TYPE quadratic_interpolation(DATA_TYPE coeffs[], DATA_TYPE x) {
    return coeffs[0] * x * x + coeffs[1] * x + coeffs[2];
}

// Function to calculate errors
void calculate_errors(DATA_TYPE x, DATA_TYPE interpolated_y, DATA_TYPE* actual_y, DATA_TYPE* abs_error, DATA_TYPE* rel_error) {
    *actual_y = sin(x); // Exact value
    *abs_error = fabs(interpolated_y - *actual_y); // Absolute error
    *rel_error = (*abs_error) / fabs(*actual_y); // Relative error
}


void print_table_header() {
    printf("%-10s%-20s%-30s%-20s%-20s%-30s%-20s%-20s%-30s\n", 
           "X", "Actual Y", "Linear Interpolated Y", "Abs Error", "Rel Error", "Quadratic Interpolated Y","Abs Error", "Rel Error", "(Linear-Quadratic)/Actual");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void print_table_row(DATA_TYPE x, DATA_TYPE actual_y, 
                     DATA_TYPE linear_y, DATA_TYPE abs_error_linear, DATA_TYPE rel_error_linear,
                     DATA_TYPE quad_y, DATA_TYPE abs_error_quad, DATA_TYPE rel_error_quad,
                     DATA_TYPE difference_ratio) {
    printf("%-10.4f%-20.4f%-30.4f%-20.4f%-20.4f%-30.4f%-20.4f%-20.4f%-30.4f\n", 
           x, actual_y, 
           linear_y, abs_error_linear, rel_error_linear, 
           quad_y, abs_error_quad, rel_error_quad, 
           difference_ratio);
}



int main() {
    // Declare variables for data
    DATA_TYPE x[MAX_POINTS], y[MAX_POINTS];
    int n; // Number of data points

    // Read data from the file
    const char* filename = "interpolation-data.txt";
    read_data(filename, &n, x, y); 

    // Generate 50 random x values between the range of data
    DATA_TYPE random_x[50];
    DATA_TYPE step = (x[n - 1] - x[0]) / 50.0;
    for (int i = 0; i < 50; i++) {
        random_x[i] = x[0] + step * i;
    }

    // Print the table header
    print_table_header();

    // Perform interpolations and calculate errors for each random x value
    for (int i = 0; i < 50; i++) {
        DATA_TYPE target_x = random_x[i];

        // Actual value
        DATA_TYPE actual_y = sin(target_x);

        // Perform linear interpolation
        DATA_TYPE linear_y = linear_interpolation(x, y, n, target_x);

        // Perform quadratic interpolation
        int j = 0; // Find the correct interval for piecewise quadratic interpolation
        while (j < n - 2 && !(x[j] <= target_x && target_x <= x[j + 2])) {
            j++;
        }
        DATA_TYPE coeffs[3];
        calculate_coefficients(&x[j], &y[j], coeffs);
        DATA_TYPE quad_y = quadratic_interpolation(coeffs, target_x);

        // Calculate absolute and relative errors
        DATA_TYPE abs_error_linear = fabs(linear_y - actual_y);
        DATA_TYPE rel_error_linear = abs_error_linear / fabs(actual_y);

        DATA_TYPE abs_error_quad = fabs(quad_y - actual_y);
        DATA_TYPE rel_error_quad = abs_error_quad / fabs(actual_y);

        // Calculate the difference ratio
        DATA_TYPE difference_ratio = (linear_y - quad_y) / actual_y;

        // Print tables
        print_table_row(target_x, actual_y, linear_y, abs_error_linear, rel_error_linear, quad_y, abs_error_quad, rel_error_quad, difference_ratio);
    }

    return 0;
}




