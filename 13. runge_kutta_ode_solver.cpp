// Yuhyun Kim
// CDS 251
// Assignment 13 extra
// 12.4.2024
// This program solves the same nonlinear ODE using the Backward Euler method with Newton–Raphson iteration, 
// generating output files for different initial conditions.

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


double MyFunc(double t, double y) {
    return y * y - (y * y * y / 5.0) - t;
}

// Newton-Raphson Method to solve for y_{n+1}
double solveBackwardEuler(double tNext, double yPrev, double h) {
    double yNext = yPrev; // Initial value as yPrev
    double tolerance = 1e-6; // Set tolerance
    int maxIter = 100; // Maximum iterations 

    for (int i = 0; i < maxIter; ++i) {
        // Backward Euler
        double g = yNext - yPrev - h * MyFunc(tNext, yNext);
        double gpri = 1 - h * (2 * yNext - (3 * yNext * yNext / 5.0));  // g'(y)

        // Update Newton-Raphson 
        double yNew = yNext - g / gpri;

        // Check convergence
        if (fabs(yNew - yNext) < tolerance) {
            return yNew;
        }

        yNext = yNew;
    }

    cerr << "Warning: Newton-Raphson did not converge" << endl;  
    return yNext;    // Retern value after maximum iterations
}
// Backward Euler Method
void BackwardEuler(double y0, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    double t = 0.0, h = 0.05, tEnd = 5.0, y = y0;  // Set and define the variables 

    // Header
    outFile << "x\ty\n";  // // Indicate x and y

    // calculate Backward Euler and save to the file
    while (t <= tEnd) {
        outFile << fixed << setprecision(5) << t << "\t" << y << "\n";

        // Calculate Backward Euler
        double tNext = t + h;
        y = solveBackwardEuler(tNext, y, h);

        t = tNext; // Update time
    }

    outFile.close();
    cout << "Data saved to " << filename << endl;
}

int main() {
    // Initial conditions
    vector<double> initialConditions = {0.0, 0.4, 0.8, 1.0, 1.2, 1.6, 2.0};

    // Save results 
    for (size_t i = 0; i < initialConditions.size(); ++i) {
        string filename = "output_backward" + to_string(i + 1) + ".txt";
        BackwardEuler(initialConditions[i], filename);
    }

    return 0;
}
