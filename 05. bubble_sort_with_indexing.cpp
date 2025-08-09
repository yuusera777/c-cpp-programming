/* ==============================================================================================================
Title: Bubble Sort with Indexing and getline Input
Author: Yuhyun Kim
Date: 10.17.2024

Description:
  Implements the Bubble Sort algorithm using array indexing to compare and swap elements.
  Reads input data (integers) from a text file using the `getline` function for flexible line-based reading.
  Outputs the sorted sequence to the console.

Inputs:
  - File: "Numbers_BubbleSort.txt"
      First line: integer N (number of elements)
      Next N lines: one integer per line

Outputs:
  - Console: sorted sequence in ascending order

Key Skills Demonstrated:
  - Bubble Sort implementation
  - File reading with getline
  - Array indexing for sorting
  - Basic algorithm optimization

The Most Important Thing:
  - Demonstrates fundamental sorting logic with clear file I/O integration.
*/ ==============================================================================================================



#include <cstdio>     
#include <cstdlib>    
#include <ctime>    

FILE * open_file(char * fname, const char * mode) {
    FILE * fptr = fopen(fname, mode);
    if (fptr == NULL) {
        printf("Unable to open file: %s\n", fname);
        exit(1);
    }
    return fptr;
}

void close_file(FILE * fptr) {
    if (fptr != NULL) {
        fclose(fptr);
    }
}

void prompt_user_for_fname(char * fname) {
    printf("Enter file name to be loaded: ");
    scanf("%s", fname);
}

// read the file from the third line of data using getline function
void read_file(FILE *fptr, float **data, int *n) {
    // Read the first line of data
    char *line = NULL;  // buffer to store the line
    size_t len = 0;     // Size of buffer
    size_t read;

    // Read the first line (name) of data
    read = getline(&line, &len, fptr);
 
    // Read the number of data in the second line
    fscanf(fptr, "%d\n", n);

    *data = (float *)malloc(*n * sizeof(float));

    for (int i = 0; i < *n; i++) {
        fscanf(fptr, "%f\n", &(*data)[i]);
    }


}

void bubble_sort(float * data, int n, int*index) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (data[index[i]] > data[index[i + 1]]) {
                // Swap only index
                int temp = index[i];
                index[i] = index[i + 1];
                index[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}



void write_file(FILE * fptr, float * data, int n, int * index) {
    fprintf(fptr, "Sorted Data\n");
    fprintf(fptr, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fptr, "%.6f\n", data[index[i]]);  // Indexing
    }
}


int main() {
    char fname[100];  // Array for storing the file name
    float * data = NULL;  // Pointer for storing data
    int * index = NULL;   // Pointer for storing the index array
    int num_data;  // the number of data

    prompt_user_for_fname(fname);

    FILE * infile = open_file(fname, "r");

    read_file(infile, &data, &num_data);
    close_file(infile);  

    
    index = (int *)malloc(num_data * sizeof(int));
    for (int i = 0; i < num_data; i++) {
        index[i] = i;   // Set the initial index
    }

    // Rund the bubble sorting using index 
    bubble_sort(data, num_data, index);

    // Opoen the output file
    FILE * outfile = open_file((char *)"Output.txt", "w");

    // Output the data using indexing
    write_file(outfile, data, num_data, index);
    close_file(outfile); 

    // Free data
    free(data);
    free(index);

    printf("Done!\n"); // Print "Done!"

    return 0;
}



