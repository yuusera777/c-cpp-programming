/* ==============================================================================================================
Title: Runge–Kutta (RK4) ODE Solver for Multiple Initial Conditions
Author: Yuhyun Kim
Date: 12.4.2024

Description:
  Despite the filename, this program implements the classical 4th-order Runge–Kutta method
  for y' = y^2 - (y^3)/5 - t. For each initial condition y(0) in a preset list, it integrates
  from t=0 to 5 with h=0.05 and writes (t, y) pairs to a separate file. The program also prints
  a confirmation message to the console after each file is saved.

Inputs:
  - None (initial conditions and step size are hard-coded)

Outputs:
  - Files: "output1.txt", "output2.txt", ...
      Each file contains:
        - First line: column headers "x    y" (tab-separated)
        - Following lines: t and y values with fixed precision (5 decimal places), tab-separated
  - Console output:
      "Data saved to <filename>" after each run

Key Skills Demonstrated:
  - RK4 integrator implementation
  - Batch runs over multiple initial conditions
  - Stream output with fixed precision
  - File I/O with <fstream> and console feedback via <iostream>

The Most Important Thing:
  - Accurate explicit integration with clear, per-IC output artifacts and user feedback.
============================================================================================================== */



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



