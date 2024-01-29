#include <stdio.h>

#define ROWS 2
#define COLUMNS 2

void addMatrices(int a[ROWS][COLUMNS], int b[ROWS][COLUMNS], int result[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) { //iterate over each element in the matrix and add, store in result matrix
        for (int j = 0; j < COLUMNS; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrices(int a[ROWS][COLUMNS], int b[ROWS][COLUMNS], int result[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) { //iterate over each element in the matrix and multiply
        for (int j = 0; j < COLUMNS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLUMNS; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void printMatrix(int matrix[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) { //function to print matrix by iterating over each element
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix1[ROWS][COLUMNS] = {{1, 2}, {3, 4}}; //test vals
    int matrix2[ROWS][COLUMNS] = {{5, 6}, {7, 8}};

    int sum[ROWS][COLUMNS];
    int product[ROWS][COLUMNS];

    addMatrices(matrix1, matrix2, sum); 
    multiplyMatrices(matrix1, matrix2, product);

    printf("Matrix Addition:\n");
    printMatrix(sum);
    printf("Matrix Multiplication:\n");
    printMatrix(product);

    return 0;
}
