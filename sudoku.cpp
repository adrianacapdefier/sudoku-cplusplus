#include "sudoku.h"

void Sudoku::setTiles(GridTile **tiles) { this->tiles = tiles; }

void Sudoku::eraseTiles() {
  std::set<int> s;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 8);

  // Alege random un numar de casute pentru a fi sterse
  for (int row = 0; row < GRID_TILES_NR; row++) {
    s.clear();
    for (int i = 0; i < 5; i++) {
      int x;
      while (true) {
        // Alege random indexul pentru coloana
        x = dist6(rng);

        // Daca indexul a fost deja ales se continua pana se gaseste un index
        // nou
        if (s.find(x) == s.end()) {
          // Salveaza indexul gasit pentru a evita duplicates
          s.insert(x);
          // Marcheaza casuta EMPTY
          tiles[row][x].setNumber(0);
          //Marcheaza casuta ca disponibila pentru a fi modificata
          tiles[row][x].setIsLocked(false);
          tiles[row][x].setColor(TILES_EMPTY_COLOR);
          break;
        }
      }
    }
  }
}

bool Sudoku::verifyColumn(int column, int number) {
  for (int row = 0; row < GRID_TILES_NR; row++)
    if (tiles[row][column].getNumber() == number)
      return true;
  return false;
}

bool Sudoku::verifyRow(int row, int number) {
  for (int column = 0; column < GRID_TILES_NR; column++)
    if (tiles[row][column].getNumber() == number)
      return true;
  return false;
}

bool Sudoku::verifySubgrid(int startRow, int endRow, int number) {
  for (int row = 0; row < 3; row++)
    for (int column = 0; column < 3; column++)
      if (tiles[row + startRow][column + endRow].getNumber() == number)
        return true;
  return false;
}

bool Sudoku::searchEmptyLocation(int &row, int &column) {
  for (row = 0; row < 9; row++) {
    for (column = 0; column < 9; column++) {
      if (this->tiles[row][column].getNumber() == 0) {
        return true;
      }
    }
  }
  return false;
}

bool Sudoku::solveSudoku() {
  int row, column;

  //Daca nu mai sunt casute goale => gridul a fost completat
  if (!searchEmptyLocation(row, column))
    return true;

  for (int number = 1; number <= 9; number++) {
    
    //Daca numarul nu exista atunci va fi salvat
    if (!verifyColumn(column, number) && !verifyRow(row, number) &&
        !verifySubgrid(row - row % 3, column - column % 3, number)) {

      tiles[row][column].setNumber(number);

      //Solutie gasita
      if (solveSudoku())
        return true;

      //Verificarea a picat => se continua cu o noua valoarea pentru posbila solutie
      tiles[row][column].setNumber(0);
    }
  }
  
  return false;
}