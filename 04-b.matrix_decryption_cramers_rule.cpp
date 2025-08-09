// Yuhyun Kim
// CDS 251
// Assignment 4a
// 09.25.2024
// This assignment is for practice to decrypt the message in data file using encryptionmatrix.


// This helps with readability and understanding what the program does.
// After your name etc, there should be a basic description of
// what the program does.

// this line is necessary for Visual Studio to 
// compile the source code without issuing an
// error message


#include <stdlib.h>
#include <stdio.h>


int** allocate_MxN_array(int nrow, int ncol);
int calculate_determinant(int** A, int n);
int** copy_matrix(int** A, int n, int col);
int* cramer(int** A, int* b, int n);
int** column_insert(int** A, int* b, int n, int col);
FILE* open_file(char* fname, char* mode);
void close_file(FILE* fptr);
void free_array(int** array, int nrows);

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// The methods that you MUST implement for your Homework
// will be added to the following 3 functions
//      calculate_determinant
//      column_insert
//      cramer
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// function to calculate the determinant of a 2x2 or 3x3 matrix
// Copy this from your Lab assignment
// function to calculate the determinant of a 2x2 or 3x3 matrix
// function to calculate the determinant of a 2x2 or 3x3 matrix

// Function to calculate the determinant of a 2x2 or 3x3 matrix
int calculate_determinant(int ** M, int n)
{
    int det = 0;

    // Calculate the determinant for a 2x2 matrix
    if (n == 2) {
        det = M[0][0] * M[1][1] - M[0][1] * M[1][0];
    } 
             // Calculate the determinant for a 3x3 matrix
    else if (n == 3) {
        det = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
               - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
               + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
    }

    return det;
}

// Utility function to copy the contents of one matrix to another
int** copy_matrix(int** array, int nrows, int ncols)
{
    int** duplicate_array = allocate_MxN_array(nrows, ncols);
    for (int i = 0; i < nrows; i++)
    {
        
        for (int j = 0; j < ncols; j++)
        {
            duplicate_array[i][j] = array[i][j];
        }
    }
    return duplicate_array;
}

// Function to replace a column with a vector
int** column_insert(int** A, int* b, int n, int col)
{
    int** new_matrix = copy_matrix(A, n, n);      //Copy the original matrix

    for (int i = 0; i < n; i++) {
        new_matrix[i][col] = b[i];
    }

    return new_matrix;
}

// Cramer's rule
int* cramer(int** A, int* b, int n)
{
        // Allocate memory to store the result vector
    int* solution = new int[n];
    
        // Calculate the determinant of the original matrix
    int det_A = calculate_determinant(A, n);
    
        // Print
    printf("Determinant of A: %d\n", det_A);

        // If the determinant is 0, there is no solution
    if (det_A == 0) {
        printf("Matrix A is singular (determinant = 0), no unique solution.\n");
        return NULL;
    }

    // Replace each column with vector b and calculate the determinant
    for (int i = 0; i < n; i++) {
      
        int** working_matrix = column_insert(A, b, n, i);

            // Calculate the determinant of the updated matrix
        int det_substituted = calculate_determinant(working_matrix, n);

            // Cramer's rule to calculate the solution
        solution[i] = det_substituted / det_A;

            // Free memory
        for (int j = 0; j < n; j++) {
            delete[] working_matrix[j];
        }
        delete[] working_matrix;
    }

    return solution;
}



int main(int argc, char* argv[])
{
    // Read the encryption matrix
    char fnameMatrix[] = "Data3_encryption_matrix.txt";
    FILE* fptr = open_file(fnameMatrix, const_cast<char *>("r"));
    if (fptr == NULL) {
        printf("Could not open file: %s\n", fnameMatrix);
        return 1;
    }

    int ndim = 2;       // 2x2 matrix
    int** A = allocate_MxN_array(ndim, ndim);

    // Read the encryption matrix
    for (int i = 0; i < ndim; i++) {
        for (int j = 0; j < ndim; j++) {
            fscanf(fptr, "%d", &A[i][j]);
        }
    }
    close_file(fptr);

    // Calculate the determinant of the matrix
    int detA = calculate_determinant(A, ndim);
    if (detA == 0) {
        printf("Encryption matrix has no unique solution (determinant is zero).\n");
        free_array(A, ndim);
        return 1;
    }

    // Read the encrypted message 
    char fnameMessage[] = "Data3.txt";
    fptr = open_file(fnameMessage, const_cast<char *>("r"));
    if (fptr == NULL) {
        printf("Could not open file: %s\n", fnameMessage);
        free_array(A, ndim);
        return 1;
    }

    // Allocate memory
    int* b = (int*)malloc(ndim * sizeof(int));
    if (b == NULL) {
        printf("Memory allocation failed for b\n");
        free_array(A, ndim);
        return 1;
    }

    // Read two numbers and decrypt
    while (fscanf(fptr, "%d %d", &b[0], &b[1]) == 2) {
            int* solution = cramer(A, b, ndim);  // Call the modified function
        
        if (solution != NULL) {
            printf("Decrypted message: ");
            for (int i = 0; i < ndim; ++i) {
                int decrypted_value = solution[i] % 256;
                if (decrypted_value < 0) {
                    decrypted_value += 256;     // Convert negative values to positive
                }
                printf("%c", decrypted_value);  // Convert the decrypted value to a character
            }
            printf("\n");
            free(solution);     // Use free instead of delete
        }
    }

    // Free memory and close the file
    free_array(A, ndim);
    free(b);  
    close_file(fptr);

    return 0;
}






///////////////////////////////////////////////////////
// Utility methods for commonly used functions       //
// These functions should not be changed or modified //
///////////////////////////////////////////////////////

// utility method to open files
FILE* open_file(char* fname, char* mode)
{
    FILE* fptr = fopen(fname, mode); // using fopen to open a file for writing

    // if the file was not opened, the returned pointer will be NULL
    // check for NULL after opening the file to ensure it was opened
    if (fptr == NULL)
    {
        printf("Unable to open file: %s \n", fname);
        return NULL;
    }

    return fptr;
}

// utility method to close file
void close_file(FILE* fptr)
{
    if (fptr != NULL)
    {
        fclose(fptr);
        fptr = NULL;
    }
}

// utility method to read a data file containing a 
// a linear equations
// Example of a set of linear equations:
// 2
// 1.0 15.0 5.0
// 8.7 9.0 2.0
// this function can load any series of linear equations
void read_equation_file(FILE* fptr, int* ndim, int*** A, int*** b)
{
    // read the number of dimensions/lines in the file
    int n = 0;
    fscanf(fptr, "%d\n", &n);
    printf("Matrix Dimension: %d x %d \n", n, n);

    // allocate memory for our array
    int ** A_ = allocate_MxN_array(n, n);
    int ** b_ = allocate_MxN_array(n, 1);

    // read the number of data lines
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (j < n)
                fscanf(fptr, "%d", &A_[i][j]);
            else
                fscanf(fptr, "%d", &b_[i][0]);
        }
        fscanf(fptr, "\n");
    }

    // now assign "n" to the ndim so it can be accessed in the calling functions
    *ndim = n;
    *A = A_;
    *b = b_;
}

// utility method to print NxN array/matrix to the console
void print_matrix(int** array, int nrow, int ncol)
{
    // ensure it is not a NULL pointer
    if (array == NULL)
    {
        printf("Array is NULL, nothing to display!!\n");
        return;
    }

    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            printf("%d \t", array[i][j]);
        }
        printf("\n");
    }
}

// utility function to free the memory used by a multi-dimensional array/matrix
void free_array(int** array, int nrows)
{
    if (array != NULL)
    {
        for (int i = 0; i < nrows; i++)
        {
            if (array[i] != NULL)
            {
                free(array[i]);
                array[i] = NULL;
            }
        }
        free(array);
        array = NULL;
    }
}

// utility method to allocate memory for a multi-dimensional array/matrix
int** allocate_MxN_array(int nrow, int ncol)
{
    // allocate memory for our array
    int** array = (int**)calloc(nrow, sizeof(int*));
    for (int i = 0; i < nrow; i++)
    {
        array[i] = (int*)calloc(ncol, sizeof(int));
    }

    return array;
}

