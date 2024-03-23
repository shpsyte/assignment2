
#include <stdio.h>

#define MAX_SIZE 100

// Function to calculate the cross product of two vectors
int crossProduct(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

// Function to check if a point (x, y) is inside the triangle formed by (x1, y1), (x2, y2), and (x3, y3)
int isInsideTriangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
    int cross1 = crossProduct(x - x1, y - y1, x2 - x1, y2 - y1);
    int cross2 = crossProduct(x - x2, y - y2, x3 - x2, y3 - y2);
    int cross3 = crossProduct(x - x3, y - y3, x1 - x3, y1 - y3);

    // If the cross products have the same sign, the point is inside the triangle
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

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
            }
        }
        prev_x = x;
        prev_y = y;
    }

    // Close input file
    fclose(inputFile);

    // Fill in the spaces within the shape for triangles
    int x1, y1, x2, y2, x3, y3;
    int minX, maxXTriangle, minY, maxYTriangle;
    for (i = 0; i < maxY; i++) {
        for (j = 0; j < maxX; j++) {
            if (grid[i][j] != '*') {
                // Check if the point is inside any of the triangles
                for (int k = 0; k < maxY; k++) {
                    if (grid[k][j] == '*' && grid[k][j + 1] == '*' && grid[k + 1][j] == '*') {
                        // Found a triangle
                        x1 = j; y1 = k;
                        x2 = j + 1; y2 = k;
                        x3 = j; y3 = k + 1;

                        minX = (x1 < x2) ? x1 : x2;
                        minX = (minX < x3) ? minX : x3;
                        maxXTriangle = (x1 > x2) ? x1 : x2;
                        maxXTriangle = (maxXTriangle > x3) ? maxXTriangle : x3;

                        minY = (y1 < y2) ? y1 : y2;
                        minY = (minY < y3) ? minY : y3;
                        maxYTriangle = (y1 > y2) ? y1 : y2;
                        maxYTriangle = (maxYTriangle > y3) ? maxYTriangle : y3;

                        if (isInsideTriangle(j, i, x1, y1, x2, y2, x3, y3) && i >= minY && i <= maxYTriangle && j >= minX && j <= maxXTriangle)
                            grid[i][j] = '*';
                    }
                }
            }
        }
    }

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
