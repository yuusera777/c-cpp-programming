// Yuhyun Kim
// CDS 251
// Assignment 13
// 12.4.2024
// This assignment is for solving a derived function by Runge Kutta Method and plot for each given y(0) value.

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Define function 
double MyFunc(double t, double y) {
    return y * y - (y * y * y / 5.0) - t;
}

// Runge Kutta Method
void RungeKutta(double y0, const string& filename) {
    ofstream outFile(filename);   // Output file using "ofstream"
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    double t = 0.0, h = 0.05, tEnd = 5.0, y = y0;   // Set and define the variables 

    // Header
    outFile << "x\ty\n";  // Indicate x and y

    // Calculate Runge Kutta and save to file
    while (t <= tEnd) {
        outFile << fixed << setprecision(5) << t << "\t" << y << "\n";

        double k1 = h * MyFunc(t, y);
        double k2 = h * MyFunc(t + h / 2.0, y + k1 / 2.0);
        double k3 = h * MyFunc(t + h / 2.0, y + k2 / 2.0);
        double k4 = h * MyFunc(t + h, y + k3);

        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        t += h;
    }

    outFile.close();  // Close file
    cout << "Data saved to " << filename << endl;
}

int main() {
    vector<double> initialConditions = {0.0, 0.4, 0.8, 1.0, 1.2, 1.6, 2.0};   // Initial conditions y(0)

    // Save the results for each initial conditions
    for (size_t i = 0; i < initialConditions.size(); ++i) {
        string filename = "output" + to_string(i + 1) + ".txt";   // Combine elements of file name
        RungeKutta(initialConditions[i], filename); // Include the results as contents of each file
    }

    return 0;
}



