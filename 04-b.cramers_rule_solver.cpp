// Yuhyun Kim
// CDS 251
// Assignment 4b
// 10.3.2024
// This file is for calculating matrix multiplication by cramer's rule.

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Function to calculate the determinant of a 2x2 or 3x3 matrix
float calculate_determinant(vector<vector<float>> matrix, int n) {
    float det = 0;

    if (n == 2) {
        // Determinant for 2x2 matrix
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else if (n == 3) {
        // Determinant for 3x3 matrix
        det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
            + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }

    return det;
}

// Function to replace a column in a matrix with a vector and return a new matrix
vector<vector<float>> replace_column(vector<vector<float>> matrix, vector<float> vec, int col, int n) {
    vector<vector<float>> new_matrix = matrix;
    for (int i = 0; i < n; i++) {
        new_matrix[i][col] = vec[i];
    }
    return new_matrix;
}

// Function to apply Cramer's Rule to solve the system of equations
vector<float> cramer(vector<vector<float>> matrix, vector<float> b, int n) {
    vector<float> solution(n);
    float detA = calculate_determinant(matrix, n);
    if (detA == 0) {
        cout << "The system has no unique solution (determinant = 0)." << endl;
        return solution;
    }

    // Replace each column and calculate the determinant for each solution
    for (int i = 0; i < n; i++) {
        vector<vector<float>> modified_matrix = replace_column(matrix, b, i, n);
        solution[i] = calculate_determinant(modified_matrix, n) / detA;
    }

    return solution;
}

// Function to read data file and solve using Cramer's Rule
void solve_equations(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    int n;
    file >> n;

    vector<vector<float>> matrix(n, vector<float>(n));
    vector<float> b(n);

    // Read coefficients and right-hand side values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> matrix[i][j];
        }
        file >> b[i];
    }

    file.close();

    // Solve using Cramer's Rule
    vector<float> solution = cramer(matrix, b, n);

    // Output the solution
    cout << "Solution for " << filename << ": ";
    for (int i = 0; i < n; i++) {
        cout << solution[i] << " ";
    }
    cout << endl;
}

int main() {
    // Process each data file
    solve_equations("Data2_1.txt");
    solve_equations("Data2_2.txt");
    solve_equations("Data2_3.txt");
    solve_equations("Data2_4.txt");
    solve_equations("Data2_5.txt");
    solve_equations("Data2_6.txt");

    return 0;
}
