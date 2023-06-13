#include "subgrid.h"

void Subgrid::setTiles(GridTile** tiles){
	this->tiles = tiles;
}

GridTile** Subgrid::getTiles(){
	return tiles;
}
