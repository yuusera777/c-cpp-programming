/* ==============================================================================================================

Title: 2×2 Matrix Decryption via Adjugate/Determinant
Author: Yuhyun Kim
Date: 09.25.2024

Description:
  Loads a 2×2 encryption matrix from file, computes its inverse using adjugate and determinant,
  then reads pairs of encrypted integers and decodes them into ASCII characters to recover the message.

Inputs:
  - File: "Data3_encryption_matrix.txt"  (matrix size followed by matrix entries)
  - File: "Data3.txt"                     (pairs of encrypted integers)

Outputs:
  - Console:
      - Inverse matrix (for debugging)
      - Determinant
      - "Decrypted Message: <text>"

Key Skills Demonstrated:
  - 2×2 determinant and inverse (adjugate / det)
  - Mixed C/C++ I/O and containers (cstdio + vector<string>)
  - Bounds check on ASCII range (32–126) when reconstructing characters
  - Basic error handling for file access and singular matrices

The Most Important Thing:
  - Correctly handling det=0 (non-invertible) and mapping decrypted integers back to readable text.
*/ ==============================================================================================================


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

// Function to calculate the determinant of a 2x2 matrix
int determinant2x2(const vector<vector<int> > &matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

//Function to calculate the inverse of a given 2x2 matrix
void invert2x2Matrix(const vector<vector<int> > &matrix, vector<vector<int> > &inverse, int &det) {
    det = determinant2x2(matrix);  // Calculate the determinant
    if (det == 0) {
        printf("The determinant of the matrix is 0. The matrix is not invertible!\n");
        exit(1);  // If the determinant is 0, exit the program as the matrix is not invertible
    }
    
    // Calculate the inverse matrix
    inverse[0][0] = matrix[1][1];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];
    inverse[1][1] = matrix[0][0];
}

// Function to read a 2x2 matrix from a file (using C-style I/O)
void readMatrix(FILE *file, vector<vector<int> > &matrix, int size) {
    matrix.resize(size, vector<int>(size));  // Set the matrix size to 2x2
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {  // Read matrix elements from the file
                printf("Error reading matrix element.\n");
                exit(1);
            }
        }
    }
}

// Function to decrypt the message using the inverse matrix
string decryptMessage(const vector<vector<int> > &inverseMatrix, FILE *dataFile, int det) {
    string message;  // String to store the decrypted message
    int num1, num2;
    while (fscanf(dataFile, "%d %d", &num1, &num2) == 2) {  // Read two encrypted numbers at a time

        // Use the inverse matrix and determinant to calculate the decrypted values
        int decrypted1 = (inverseMatrix[0][0] * num1 + inverseMatrix[0][1] * num2) / det;
        int decrypted2 = (inverseMatrix[1][0] * num1 + inverseMatrix[1][1] * num2) / det;

        // If the decrypted values are within the valid ASCII range (32~126), convert them to characters
        if (decrypted1 >= 32 && decrypted1 <= 126) {
            message.push_back(static_cast<char>(decrypted1));  // Add the first decrypted character to the message
        }
        if (decrypted2 >= 32 && decrypted2 <= 126) {
            message.push_back(static_cast<char>(decrypted2));  // Add the second decrypted character to the message
        }
    }
    return message;  // Return the final decrypted message
}

int main() {
    // Open the matrix file and data file (using C-style I/O)
    FILE *matrixFile = fopen("Data3_encryption_matrix.txt", "r");  // Open the encryption matrix file
    FILE *dataFile = fopen("Data3.txt", "r");  // Open the encrypted message file

    if (matrixFile == NULL || dataFile == NULL) {  // If files cannot be opened, print an error and exit
        printf("Error opening files!\n");
        return 1;
    }

    int size;
    if (fscanf(matrixFile, "%d", &size) != 1) {  // Read the size of the matrix
        printf("Error reading matrix size.\n");
        return 1;
    }

    // Initialize the matrices with the correct size
    vector<vector<int> > encryptionMatrix(size, vector<int>(size));  // Vector to store the encryption matrix
    vector<vector<int> > inverseMatrix(size, vector<int>(size));     // Vector to store the inverse matrix
    int det;  // Variable to store the determinant

    // Read the encryption matrix from the file
    readMatrix(matrixFile, encryptionMatrix, size);

    // Calculate the inverse matrix
    invert2x2Matrix(encryptionMatrix, inverseMatrix, det);

    // Print the inverse matrix (for debugging)
    printf("Inverse Matrix: \n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", inverseMatrix[i][j]);
        }
        printf("\n");
    }

    // Print the determinant (for debugging)
    printf("Determinant: %d\n", det);

    // Decrypt the encrypted message
    string decryptedMessage = decryptMessage(inverseMatrix, dataFile, det);

    // Print the decrypted message
    printf("Decrypted Message: %s\n", decryptedMessage.c_str());

    // Close the files
    fclose(matrixFile);
    fclose(dataFile);

    return 0;
}
