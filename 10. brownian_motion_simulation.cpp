// Yuhyun Kim
// CDS 251
// Assignment 10-extra
// 11.15.2024
// This program simulates 2D Brownian motion with defined steps and seed by users, 
// outputting each position and final coordinates.


#include <stdio.h>
#include <stdlib.h>

// Function to simulate Brownian Motion
void simulate_brownian_motion(int steps, int seed) {
    // Initialize random number generator
    srand(seed);

    // Starting coordinates
    int x = 0, y = 0;

    // Print initial position
    printf("Step-by-step Brownian Motion:\n");
    printf("Step 0: (%d, %d)\n", x, y);

    // Simulate steps
    for (int i = 1; i <= steps; i++) {
        int direction = rand() % 4; // 0: Up, 1: Down, 2: Left, 3: Right

        // Update coordinates based on direction
        switch (direction) {
            case 0: y++; break; // Move up
            case 1: y--; break; // Move down
            case 2: x--; break; // Move left
            case 3: x++; break; // Move right
        }

        // Print current position
        printf("Step %d: (%d, %d)\n", i, x, y);
    }

    // Print final position
    printf("\nFinal position after %d steps: (%d, %d)\n", steps, x, y);
}

int main() {
    int steps, seed;

    // Ask user for input
    printf("Enter the number of steps: ");
    scanf("%d", &steps);

    printf("Enter a seed for the random number generator: ");
    scanf("%d", &seed);

    // Simulate Brownian Motion
    simulate_brownian_motion(steps, seed);

    return 0;
}
