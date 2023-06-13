#pragma once

#include <SDL.h>
#undef main
#include <string>
#include <set>

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 800;

constexpr int REDRAW_TIMEOUT = 100;

constexpr int GRID_SUDOKU_NR = 3;
constexpr int GRID_TILES_NR = 9;

constexpr int GRID_WH = 612;
constexpr int GRID_OUTLINE_WH = 612 + 10;
constexpr int SUBGRID_WH = 204;
constexpr int GRID_TILE_SIZE = 68;

constexpr int SCENE_X_START = (WINDOW_WIDTH - GRID_WH) / 2;
constexpr int SCENE_Y_START = (WINDOW_HEIGHT - GRID_WH) / 2;
constexpr int GRID_X_START = SCENE_X_START - 5;
constexpr int GRID_Y_START = SCENE_Y_START - 5;


constexpr auto FONT_PATH = "C:\\Users\\maria\\OneDrive\\Desktop\\SSSUDOKU\\roboto.ttf";
constexpr int TEXT_FONT_NORMAL = 21;
constexpr int TEXT_FONT_BIG = 32;

constexpr int FPS_CAP = 1000 / 60;

constexpr SDL_Color SCENE_BACKGROUND_COLOR = { 0xDD, 0xDD, 0xDD, 0xFF };
constexpr SDL_Color SCORE_TEXT_COLOR = { 0xFF, 0xFF, 0xFF, 0xFF };
constexpr SDL_Color TEXT_COLOR = { 0x00, 0x00, 0x00, 0xFF };
constexpr SDL_Color GRID_OUTLINE_COLOR = { 0x00, 0x00, 0x00, 0xFF };
constexpr SDL_Color SUBGRID_OUTLINE_COLOR = { 0xFF, 0x00, 0x00, 0xFF };
constexpr SDL_Color TILES_FILL_COLOR = { 0xFF, 0xFF, 0xFF, 0xFF };
constexpr SDL_Color TILES_VALID_COLOR = { 0x00, 0xFF, 0x00, 0xFF };
constexpr SDL_Color TILES_WRONG_COLOR = { 0xFF, 0x00, 0x00, 0xFF };
constexpr SDL_Color TILES_OUTLINE_COLOR = { 0x00, 0x00, 0x00, 0xFF };
constexpr SDL_Color TILES_SELECTED_COLOR = { 0x87, 0xC1, 0xFF, 0xFF };
constexpr SDL_Color TILES_EMPTY_COLOR = { 0xCB, 0xF3, 0xF9, 0xFF };

constexpr int START_TEXT_X = 530;
constexpr int START_TEXT_Y = 400;
constexpr int START_TEXT_W = 140;

constexpr int SUDOKU_PUZZLE_1[9][9] = {
	{8,2,7,1,5,4,3,9,6},
	{9,6,5,3,2,7,1,4,8},
	{3,4,1,6,8,9,7,5,2},
	{5,9,3,4,6,8,2,7,1},
	{4,7,2,5,1,3,6,8,9},
	{6,1,8,9,7,2,4,3,5},
	{7,8,6,2,3,5,9,1,4},
	{1,5,4,7,9,6,8,2,3},
	{2,3,9,8,4,1,5,6,7},
};

constexpr int SUDOKU_PUZZLE_2[9][9] = {
	{2,9,3,1,6,5,7,4,8,},
	{5,7,6,8,4,3,2,9,1},
	{1,8,4,7,9,2,3,6,5},
	{3,5,8,9,1,7,4,2,6},
	{9,6,2,4,5,8,1,3,7},
	{7,4,1,2,3,6,8,5,9},
	{8,3,7,6,2,9,5,1,4},
	{6,1,5,3,8,4,9,7,2},
	{4,2,9,5,7,1,6,8,3},
};

constexpr int SUDOKU_PUZZLE_3[9][9] = {
	{4,2,5,1,3,9,7,8,6},
	{9,3,8,4,6,7,2,1,5},
	{6,1,7,8,5,2,9,4,3},
	{7,8,1,6,9,3,5,2,4},
	{3,5,9,7,2,4,1,6,8},
	{2,4,6,5,8,1,3,9,7},
	{5,9,4,2,7,6,8,3,1},
	{1,7,3,9,4,8,6,5,2},
	{8,6,2,3,1,5,4,7,9},
};
