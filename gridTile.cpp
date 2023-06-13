#include "gridtile.h"

void GridTile::setPosition(Point2D position) { this->position = position; }

Point2D GridTile::getPosition() { return position; }

void GridTile::setNumber(int number) { this->number = number; }

int GridTile::getNumber() { return number; }

void GridTile::setColor(const SDL_Color &color) { this->color = color; }

SDL_Color GridTile::getColor() { return color; }

void GridTile::setIsLocked(bool isLocked) { this->isLocked = isLocked; }

bool GridTile::getIsLocked() { return isLocked; }