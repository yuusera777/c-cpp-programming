// Yuhyun Kim
// CDS 251
// Assignment 6
// 10.20.2024
// This assignment is for quick sort using indexing.

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



int partition(float A[], int index[], int lo, int hi) {
    int Pivot = index[hi]; 
    int P = lo;

    for (int i = lo; i < hi - 1; i++) 
    {
        if (A[index[i]] < A[Pivot]) {
            
            int temp = index[P];
            index[P] = index[i];
            index[i] = temp;
            P = P + 1;
        }
    }
    
    
    int temp = index[P];
    index[P] = index[hi];
    index[hi] = temp;

    return P;
}


// Quick sort using indexing
void quick_sort(float A[], int index[], int lo, int hi) {
    if (lo < hi) {
        int P = partition(A, index, lo, hi);
        quick_sort(A, index, lo, P - 1);
        quick_sort(A, index, P + 1, hi);
    }
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
    int * index = NULL;
    int num_data;  // the number of data

    prompt_user_for_fname(fname);

    FILE * infile = open_file(fname, "r");

    read_file(infile, &data, &num_data);
    close_file(infile);  

    
    index = (int *)malloc(num_data * sizeof(int));
    for (int i = 0; i < num_data; i++) {
        index[i] = i;   // Set the initial index
    }

    // Run the quick sort using index 
    quick_sort(data, index, 0, num_data - 1);


    // Open the output file
    FILE * outfile = open_file((char *)"HW6Out.txt", "w");

    // Output the data
    write_file(outfile, data, num_data, index);
    close_file(outfile); 

    // Free data
    free(data);

    printf("Done!\n"); // Print "Done!"

    return 0;
}

