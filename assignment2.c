
#include <stdio.h>

#define MAX_SIZE 100

void drawLine(char inputFileName[], char outputFileName[]) {
    FILE *inputFile, *outputFile;
    int x, y, prev_x = -1, prev_y = -1, maxX = 0, maxY = 0, i, j;
    char grid[MAX_SIZE][MAX_SIZE] = {{' '}};

    // Open input file
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Read input coordinates
    while (fscanf(inputFile, "%d,%d", &x, &y) == 2) {
        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (prev_x != -1 && prev_y != -1) {
            // Draw line from previous point to current point
            if (prev_x == x) {
                // Vertical line
                int start = (prev_y < y) ? prev_y : y;
                int end = (prev_y < y) ? y : prev_y;
                for (i = start; i <= end; i++)
                    grid[i][x] = '*';
            } else if (prev_y == y) {
                // Horizontal line
                int start = (prev_x < x) ? prev_x : x;
                int end = (prev_x < x) ? x : prev_x;
                for (j = start; j <= end; j++)
                    grid[y][j] = '*';
            } else {
                // Diagonal line (triangle)
                double slope = (double)(y - prev_y) / (x - prev_x);
                int start_x = (prev_x < x) ? prev_x : x;
                int end_x = (prev_x < x) ? x : prev_x;
                for (i = start_x; i <= end_x; i++) {
                    int j = prev_y + (int)(slope * (i - prev_x));
                    grid[j][i] = '*';
                }
            }
        }
        prev_x = x;
        prev_y = y;
    }

    // Close input file
    fclose(inputFile);

    // Open output file
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    // Draw grid
    for (i = 0; i <= maxY; i++) {
        for (j = 0; j <= maxX; j++) {
            fprintf(outputFile, "%c", grid[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    // Close output file
    fclose(outputFile);
}

int main() {
    drawLine("input.txt", "output.txt");
    return 0;
}
