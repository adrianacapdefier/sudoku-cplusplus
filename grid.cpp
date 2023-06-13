#include "grid.h"

void Grid::setPosition(Point2D position){
	this->position = position;
}

Point2D Grid::getPosition() {
	return position;

}

void Grid::setSubgrids(Grid** subgrids) {
	this->subgrids = subgrids;
}

Grid** Grid::getSubgrids() {
	return subgrids;
}
