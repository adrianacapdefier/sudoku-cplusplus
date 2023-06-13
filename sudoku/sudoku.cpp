#include "sudoku.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

const int N = 9;
const int WindowWidth = 600;
const int WindowHeight = 600;
const int CellSize = WindowWidth / N;

// Function to display the Sudoku grid
void Sudoku::displayGrid(SDL_Renderer* renderer, const int grid[N][N]) {
    SDL_Color black = { 0, 0, 0, 255 };

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    TTF_Font* font = TTF_OpenFont("arial.ttf", 30);
    if (!font) {
        std::cout << "Error loading font file." << std::endl;
        return;
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int number = grid[row][col];

            if (number != 0) {
                SDL_Surface* numberSurface = TTF_RenderText_Solid(font, std::to_string(number).c_str(), black);
                SDL_Texture* numberTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);

                rect.x = col * CellSize + CellSize / 2 - numberSurface->w / 2;
                rect.y = row * CellSize + CellSize / 2 - numberSurface->h / 2;
                rect.w = numberSurface->w;
                rect.h = numberSurface->h;

                SDL_RenderCopy(renderer, numberTexture, NULL, &rect);

                SDL_DestroyTexture(numberTexture);
                SDL_FreeSurface(numberSurface);
            }
        }
    }

    TTF_CloseFont(font);
}

// Function to accept user input for initial Sudoku grid
void Sudoku::acceptUserInput(int grid[N][N]) {
    std::cout << "Enter the initial Sudoku grid (use 0 for empty cells):" << std::endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cin >> grid[row][col];
        }
    }
}

// Function to check if a number can be placed in a particular cell
bool Sudoku::canPlaceNumber(const int grid[N][N], int row, int col, int num) {
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
bool Sudoku::solveSudoku(int grid[N][N]) {
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

    // If no empty cell found, the Sudoku puzzle is solved
    if (!isEmptyCell) {
        return true;
    }

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (canPlaceNumber(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            // If the number placement leads to an incorrect solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Sudoku Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int grid[N][N];

    acceptUserInput(grid);

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        std::cout << "Solved Sudoku grid:" << std::endl;
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                std::cout << grid[row][col] << " ";
            }
            std::cout << std::endl;
        }

        bool isRunning = true;
        SDL_Event event;

        while (isRunning) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                }
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            displayGrid(renderer, grid);

            SDL_RenderPresent(renderer);
        }
    }
    else {
        std::cout << "No solution exists for the Sudoku grid." << std::endl;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


