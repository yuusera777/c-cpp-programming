/* ==============================================================================================================
Title: Histogram from File (Fixed Range & Bins)
Author: Yuhyun Kim
Date: 11.15.2024

Description:
  Reads floating-point values from "Bumps.txt", bins them into a histogram with
  start=10.0, end=30.0, bins=100, and counts out-of-range values. Opens "BumpsHist.txt"
  for writing (current code computes counts but does not yet write them to the file).

Inputs:
  - File: "Bumps.txt" (path currently hard-coded in source)

Outputs:
  - File: "BumpsHist.txt" (opened; bin counts writing to be added)
  - (In-memory) int Hist[100] and BadCount

Key Skills Demonstrated:
  - Streaming file read with scanf/fscanf
  - Histogram index computation and boundary checks
  - Basic error handling for file I/O

The Most Important Thing:
  - Converts raw samples into frequency bins; add a write loop to persist counts.
============================================================================================================== */



#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdio>


int main() {
    const char *input_file = "/Users/klieeu777/Desktop/cds251/week10/Bumps.txt";
    const char *output_file = "BumpsHist.txt";
    const double Histstart = 10.0;  // Starting value of histogram
    const double Histend = 30.0;   // End value of histogram
    const double HistRange = Histend - Histstart;  // Range of histogram
    const int Nboxes = 100;        // The numbers of boxes
    const double BoxWidth = HistRange / Nboxes;  // width of boxes

    int Hist[Nboxes] = {0};  // Initializes of histogram array
    int BadCount = 0;  // Initializes of counter if a value is out of the range 

    
    FILE *infile = fopen(input_file, "r");
    if (infile == NULL) {
        printf("Error: Unable to open file %s\n", input_file);
        return 1;
    }

    double Num;
    while (fscanf(infile, "%lf", &Num) == 1) {
        // Calculate box index
        int iHist = (int)((Num - Histstart) * Nboxes / HistRange);

        // Update the histogram by its range
        if (iHist >= 0 && iHist < Nboxes) {
            Hist[iHist] = Hist[iHist] + 1;
        } else {
            BadCount = BadCount + 1;  // Count the values out of the range
        }
    }

    fclose(infile);

    // Store the histogram to "BumpsHist.txt"
    FILE *outfile = fopen(output_file, "w");
    if (outfile == NULL) {
        printf("Error: Unable to open file %s\n", output_file);
        return 1;
    }

    fclose(outfile);

    return 0;
}



