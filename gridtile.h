#ifndef GRID_TILE_H
#define GRID_TILE_H

#include "point2d.h"
#include "config.hpp"
#include "SDL.h"

class GridTile
{
	Point2D position;
	SDL_Color color {TILES_FILL_COLOR};
	int number;
	bool isLocked {true};

public:
	void setPosition(Point2D position);
	Point2D getPosition();
	void setNumber(int number);
	int getNumber();
	void setColor(const SDL_Color& color);
	SDL_Color getColor();
	void setIsLocked(bool isLocked);
	bool getIsLocked();
};

#endif