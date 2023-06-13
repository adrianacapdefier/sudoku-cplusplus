#pragma once
#include "grid.h"
#include "gridTile.h"

class Subgrid : public Grid
{
	GridTile** tiles;

public:
	void setTiles(GridTile** tiles);
	GridTile** getTiles();
};

