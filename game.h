#pragma once
#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include "draw.h"
#include "gridtile.h"
#include "sudoku.h"

enum GameSM {
	STARTED,
	RUNNING,
	STOPPED,
};

struct GridIndex {
	int row;
	int column;
};

class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Draw pen;
	int score;
	bool isQuit;
	SDL_KeyCode keyPressed = SDL_KeyCode::SDLK_UNKNOWN;
	GridTile** gridTiles;
	GameSM sm;
	Sudoku solver;
	GridIndex selected {0, 0};
	bool reinit;
	long long executionTime;
	std::string displayText;

public:
	void run();
	void init();
	void initScene();
	~Game() { deleteGrid(); }
private:
	void generateRandomGrid();
	void redraw();
	void getUserInput(SDL_Event* e, bool* quit);
	void initTiles(const int puzzle[][GRID_TILES_NR]);
	void selectPuzzle();
	int getNumberFromKeyCode(SDL_Keycode key);
	void deleteGrid();
	void initGrid();
	void reinitGrid();
};

