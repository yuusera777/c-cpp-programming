// Yuhyun Kim
// CDS 251
// Assignment 7
// 10.29.2024
// This program is for reading matrix data and calculating the running averages and variances using equations.

#include <cstdio>
#include <cmath>



FILE* open_file(const char* fname, const char* mode) {
    FILE* fptr = fopen(fname, mode);
    if (fptr == NULL) {
        printf("Unable to open file: %s\n", fname);
        return NULL;
    }
    return fptr;
}

void close_file(FILE* fptr) {
    if (fptr != NULL) {
        fclose(fptr);
    }
}





int main() {
    const char* filename = "/Users/klieeu777/Desktop/cds251/week7/QuadData.txt";
    FILE* fptr = open_file(filename, "r");
    if (fptr == NULL) return 1;

    // Initial set of running mean and variables
    float xMean = 0.0f, x2Mean = 0.0f, yMean = 0.0f;
    float Sxx = 0.0f, Sxy = 0.0f, Sxx2 = 0.0f, Sx2x2 = 0.0f, Sx2y = 0.0f;
    float x, y;
    float a = 0.0f, b = 0.0f, c = 0.0f;


    FILE* Outputex = fopen("Outputex.txt", "w");
    if (Outputex == NULL) {
        printf("Unable to open output file for Program B.\n");
        close_file(fptr);
        return 0;
    }
    
   


    // Read one number at a time from the file and update the mean and Sum
    for (int i = 1; i <= 200; i++) {
            
        fscanf(fptr, "%f %f", &x, &y);  // Read number and allocae to x and y

        xMean = xMean + (x - xMean) / i;
        yMean = yMean + (y - yMean) / i;
        x2Mean = x2Mean + (x*x - x2Mean) / i;
        
        // Using float i to prevent the float number of i from being integer when calculating
        Sxx2 = Sxx2 + ((i - 1) / (float)i) * (x - xMean) * ((x * x) - x2Mean);     
        Sx2x2 = Sx2x2 + ((i - 1) / (float)i) * ((x * x) - x2Mean) * ((x * x) - x2Mean);
        Sx2y = Sx2y + ((i - 1) / (float)i) * (y - yMean) * ((x * x) - x2Mean);

        Sxx = Sxx + ((i - 1) / (float)i) * (x - xMean) * (x - xMean);
        Sxy = Sxy + ((i - 1) / (float)i) * (x - xMean) * (y - yMean);
    

        a = (Sx2y * Sxx - Sxy * Sxx2) / (Sxx * Sx2x2 - Sxx2 * Sxx2);
        b = (Sxy * Sx2x2 - Sx2y * Sxx2) / (Sxx * Sx2x2 - Sxx2 * Sxx2);
        c = yMean - b * xMean - a * x2Mean;

}

    fprintf(Outputex, "Exponent a = %f\n", a);
    fprintf(Outputex, "Coefficient b = %f\n", b);

    // Output
    printf("x^2 coefficient a = %lf\n", a);
    printf("x coefficient b = %lf\n", b);
    printf("Constant c = %lf\n", c);


    fclose(fptr);
    fclose(Outputex);

    return 0;
}


