#pragma once
#include "point2d.h"

class Grid
{
	Point2D position;
	Grid** subgrids;

public:
	void setPosition(Point2D position);
	Point2D getPosition();

	void setSubgrids(Grid** subgrids);
	Grid** getSubgrids();
};


