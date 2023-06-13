#include "User.h"
#include "grid.h"
#include <iostream>
using namespace std;

const int N = 9;

// Function to display the Sudoku grid
void User::displayGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a particular cell
bool User::canPlaceNumber(int grid[N][N], int row, int col, int num) {
    // Check if the number already exists in the same row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool User::solveSudoku(int grid[N][N]) {
    int row, col;

    // Check for an empty cell in the Sudoku grid
    bool isEmptyCell = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmptyCell = true;
                break;
            }
        }
        if (isEmptyCell) {
            break;
        }
    }

    // If no empty cell is found, the Sudoku is solved
    if (!isEmptyCell) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= N; num++) {
        if (canPlaceNumber(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the remaining Sudoku
            if (solveSudoku(grid)) {
                return true;
            }

            // If the current placement leads to an incorrect solution,
            // backtrack and try the next number
            grid[row][col] = 0;
        }
    }

    return false;
}

// Function to accept user input for initial Sudoku grid
void acceptUserInput(vector<vector<int>>& grid) {
    cout << "Enter the initial Sudoku grid (use 0 for empty cells):" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int num;
            cin >> num;

            // Validate the input number
            while (num < 0 || num > 9) {
                cout << "Invalid number! Please enter a number between 0 and 9: ";
                cin >> num;
            }

            grid[row][col] = num;
        }
    }
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    vector<vector<int>> grid(N, vector<int>(N));

    acceptUserInput(grid);

    cout << "Initial Sudoku grid:" << endl;
    displayGrid(grid);
    cout << endl;

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku grid:" << endl;
        displayGrid(grid);
    }
    else {
        cout << "No solution exists for the Sudoku grid." << endl;
    }

    return 0;
}

