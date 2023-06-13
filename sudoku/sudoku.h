#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
class Sudoku
{
public:
	void displayGrid(SDL_Renderer* renderer, const int grid[N][N]);
	void acceptUserInput(int grid[N][N]);
	bool canPlaceNumber(const int grid[N][N], int row, int col, int num);
	bool solveSudoku(int grid[N][N]);

};

