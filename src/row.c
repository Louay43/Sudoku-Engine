#include "sudoku.h"

int checkRows(Square *** sudoku, Box ** boxes) {
    int i, j, k;
    int sum [9];
    int place[9];

    for(i = 0; i < SIZE_ROWS; i++) {
        for (j = 0; j < 9; j++) {
            place[j] = 0; // Reset the place array for each row
            sum[j] = 0; // Reset the sum for each row
        }
        for (j = 0; j < SIZE_COLUMNS; j++) {
            if(sudoku[i][j]->number != 0) {
                continue;
            } 
            for(k = 0; k < 9; k++) {
                if(sudoku[i][j]->possible[k] == 0) {
                    sum[k]++;
                    place[k] = j; // Store the column index where this number can be placed
                }
            }
        }

        for(k = 0; k < 9; k++) {
            if(sum[k] == 1) { 
                sudoku[i][place[k]]->number = k + 1; 
                sudoku[i][place[k]]->solvable = 0; // Mark the square as solved
                UNSOLVED--; // Decrease the count of unsolved squares

                updateSudoku(sudoku, i, place[k]); // Update the Sudoku grid
                updateBoxes(sudoku, i, place[k]); // Update the boxes
                return 1; // Return success, a complete row was found
            }
        }

    }

    return 0; // No complete row found
}