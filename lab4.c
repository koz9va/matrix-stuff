//
// Created by Серафим Гончаров on 3/2/20.
//
#include <stdio.h>

#include "matrixFunc.h"

FILE *input;


int main() {
    struct matrix_ matrix;
    struct matrix_ matrixT;
    int *addRow, addColl;
    int i, j;
    char c;
    int *quadRow;
    int *quadColl;
    int *quadRowPos;
    int *quadCollPos;
    int arr[] = {3, 2, 1, 6, 8, 4};
    int arr1[] = {0, 1, 2, 4, 5, 6};

    matrix.colls = 0;
    matrix.rows = 0;

    input = fopen("l4v05.txt", "r");
    if (input == NULL) {
        printf("There is an error in opening the file");
        return 1;
    }
    i = 0;
    while (i < 1e5) {
        i++;
        c = getc(input);
        if (c == 32 && matrix.rows == 0) {
            matrix.colls++;
            continue;
        }
        if (c == 10) {
            matrix.rows++;
            continue;
        }
        if (c == EOF)break;
    }
    if (i == 1e5) {
        printf("It seems like a strange activity");
        return 1;
    }

    fseek(input, 0L, SEEK_SET);

    matrix.mat = allocMatrix(matrix.colls, matrix.rows);
    matrixT.rows = matrix.colls;
    matrixT.colls = matrix.rows;
    quadRow = malloc(sizeof(int) * matrix.rows);
    quadRowPos = malloc(sizeof(int) * matrix.rows);
    if (quadRow == NULL) return 2;
    memset(quadRow, 0, matrix.rows);

    quadColl = malloc(sizeof(int) * matrix.colls);
    quadCollPos = malloc(sizeof(int) * matrix.colls);
    if (quadColl == NULL) return 2;
    memset(quadColl, 0, matrix.colls);

    for (i = 0; i < matrix.rows; i++) {
        quadRowPos[i] = i;
        for (j = 0; j < matrix.colls; j++) {
            quadCollPos[j] = j;
            fscanf(input, "%d", (*(matrix.mat + i) + j));
        }
    }

    for (i = 0; i < matrix.rows; i++) {
        for (j = 0; j < matrix.colls; j++) {
            quadRow[i] += (*(*(matrix.mat + i) + j)) * (*(*(matrix.mat + i) + j));

            quadColl[j] += matrix.mat[i][j] * matrix.mat[i][j];

        }

    }
    printf("source matrix:\n");
    printMatrix(&matrix);
    printf("\n");
    bubble(quadRow, quadRowPos, matrix.rows);
    bubble(quadColl, quadCollPos, matrix.colls);
    for (i = 0; i < matrix.rows; i++) {
        printf("%d  %d\n", quadRowPos[i], quadRow[i]);

    }
    printf("\n");
    for (i = 0; i < matrix.colls; i++) {
        printf("%d ", quadColl[i]);
    }

    swap(matrix.mat[1], matrix.mat[0], matrix.rows);

    for (i = 0; i < matrix.rows; i++) {
        swap(matrix.mat[quadRowPos[i]], matrix.mat[i], matrix.rows);
    }
    printf("\n\n");


    printf("----------------\n");


    printMatrix(&matrix);

    printf("\n----------\n");

    extswap(matrix.mat, matrix.rows, 0, 1);
    printMatrix(&matrix);

    printf("\n----------\n");

    matrixT.mat = transposeMatrix(matrix.mat, matrixT.rows, matrixT.colls);
    printMatrix(&matrixT);

    printf("\n----------\n");

    cutByRows(&matrixT);
    printMatrix(&matrixT);

    printf("\n----------\n");

    swapQuadrants(2, 4, &matrixT);
    printMatrix(&matrixT);


    for (i = 0; i < matrix.rows; i++) {
        free(matrix.mat[i]);
    }
    for (i = 0; i < matrixT.rows; i++) {
        free(matrixT.mat[i]);
    }
    free(matrix.mat);
    free(matrixT.mat);
    free(quadColl);
    free(quadCollPos);
    free(quadRow);
    free(quadRowPos);
    return 0;
}
