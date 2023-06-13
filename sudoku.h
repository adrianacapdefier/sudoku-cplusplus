#include "gridtile.h"
#include "config.hpp"
#include <random>
#include <set>

class Sudoku
{
	GridTile** tiles;

public:
	void setTiles(GridTile** tiles);
	void eraseTiles();
	bool solveSudoku();
private:
	bool verifyColumn(int column, int number);
	bool verifyRow(int row, int number);
	bool verifySubgrid(int startRow, int endRow, int number);
	bool searchEmptyLocation(int& row, int& column);
};

