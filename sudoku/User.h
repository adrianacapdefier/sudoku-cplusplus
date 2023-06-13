#pragma once
#include "grid.h"
#include <iostream>
#include <vector>s

class User {
private:
	int N = 9;
public:
	void displayGrid(int grid[N][N]);
	bool canPlaceNumber(int grid[N][N], int row, int col, int num);
	bool solveSudoku(int grid[N][N]);
	void acceptUserInput(vector<vector<int>>& grid);



};

