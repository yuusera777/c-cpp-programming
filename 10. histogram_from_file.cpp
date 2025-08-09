/* ==============================================================================================================
Title: Histogram from File (Fixed Range & Bins)
Author: Yuhyun Kim
Date: 11.15.2024

Description:
  Reads floating-point values from "Bumps.txt" and bins them into a histogram with
  start=10.0, end=30.0, bins=100. Counts out-of-range values as BadCount.
  Opens "BumpsHist.txt" for writing, but the current version does not yet write
  the histogram counts to the file (the output file is created empty).

Inputs:
  - File: "Bumps.txt" (absolute path hard-coded in source:
           /Users/klieeu777/Desktop/cds251/week10/Bumps.txt)

Outputs:
  - File: "BumpsHist.txt" (created; histogram counts not yet written)
  - In-memory: int Hist[100], int BadCount
  - Console: prints error messages only (no normal-run output)

Key Skills Demonstrated:
  - Streaming file read with scanf/fscanf
  - Histogram index computation (fixed range/bins) and boundary checks
  - Basic file I/O error handling

The Most Important Thing:
  - Converts raw samples into frequency bins in memory; add a write loop to persist counts.
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



