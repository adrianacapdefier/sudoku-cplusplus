#include "draw.h"

void Draw::setRenderer(SDL_Renderer *renderer) { this->renderer = renderer; }

void Draw::drawStartView() {}

void Draw::drawText(const std::string &text, SDL_Color color, Point2D position,
                    Size size) {
  //Asigneaza suprafata de desenare pentru text
  SDL_Surface *surfaceText = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture *textureText =
      SDL_CreateTextureFromSurface(renderer, surfaceText);
  SDL_Rect rectangle;
  rectangle.x = position.x;
  rectangle.y = position.y;
  rectangle.w = size.width;
  rectangle.h = size.height;

  SDL_RenderCopy(renderer, textureText, NULL, &rectangle);

  SDL_FreeSurface(surfaceText);
  SDL_DestroyTexture(textureText);
}

void Draw::drawNumbers() {}

void Draw::drawGridOutline() {
  //Deseneaza conturul gridului din 5 patrate
  SDL_Rect rect = {GRID_X_START, GRID_Y_START, GRID_OUTLINE_WH,
                   GRID_OUTLINE_WH};
  SDL_SetRenderDrawColor(renderer, GRID_OUTLINE_COLOR.r, GRID_OUTLINE_COLOR.g,
                         GRID_OUTLINE_COLOR.b, GRID_OUTLINE_COLOR.a);
  SDL_RenderDrawRect(renderer, &rect);

  rect = {GRID_X_START + 1, GRID_Y_START + 1, GRID_OUTLINE_WH - 2,
          GRID_OUTLINE_WH - 2};
  SDL_SetRenderDrawColor(renderer, GRID_OUTLINE_COLOR.r, GRID_OUTLINE_COLOR.g,
                         GRID_OUTLINE_COLOR.b, GRID_OUTLINE_COLOR.a);
  SDL_RenderDrawRect(renderer, &rect);

  rect = {GRID_X_START + 2, GRID_Y_START + 2, GRID_OUTLINE_WH - 4,
          GRID_OUTLINE_WH - 4};
  SDL_SetRenderDrawColor(renderer, GRID_OUTLINE_COLOR.r, GRID_OUTLINE_COLOR.g,
                         GRID_OUTLINE_COLOR.b, GRID_OUTLINE_COLOR.a);
  SDL_RenderDrawRect(renderer, &rect);

  rect = {GRID_X_START + 3, GRID_Y_START + 3, GRID_OUTLINE_WH - 6,
          GRID_OUTLINE_WH - 6};
  SDL_SetRenderDrawColor(renderer, GRID_OUTLINE_COLOR.r, GRID_OUTLINE_COLOR.g,
                         GRID_OUTLINE_COLOR.b, GRID_OUTLINE_COLOR.a);
  SDL_RenderDrawRect(renderer, &rect);

  rect = {GRID_X_START + 4, GRID_Y_START + 4, GRID_OUTLINE_WH - 8,
          GRID_OUTLINE_WH - 8};
  SDL_SetRenderDrawColor(renderer, GRID_OUTLINE_COLOR.r, GRID_OUTLINE_COLOR.g,
                         GRID_OUTLINE_COLOR.b, GRID_OUTLINE_COLOR.a);
  SDL_RenderDrawRect(renderer, &rect);
}

void Draw::drawSubgrids() {
  Point2D subgridsPos[GRID_SUDOKU_NR][GRID_SUDOKU_NR];
  int offset_x = SCENE_X_START;
  int offset_y = SCENE_Y_START;

  //Asigneaza pozitii pentru submatrici
  for (int row = 0; row < GRID_SUDOKU_NR; row++) {
    for (int column = 0; column < GRID_SUDOKU_NR; column++) {
      subgridsPos[row][column].x = offset_x;
      subgridsPos[row][column].y = offset_y;
      offset_x += SUBGRID_WH;
    }

    offset_x = SCENE_X_START;
    offset_y += SUBGRID_WH;
  }

  //Pregateste submatricile pentru desenat
  for (int row = 0; row < GRID_SUDOKU_NR; row++) {
    for (int column = 0; column < GRID_SUDOKU_NR; column++) {
      //Submatricea are un contur de grosime 2px desenat print doua rectangles
      SDL_Rect rect = {subgridsPos[row][column].x, subgridsPos[row][column].y,
                       SUBGRID_WH, SUBGRID_WH};
      SDL_SetRenderDrawColor(renderer, SUBGRID_OUTLINE_COLOR.r,
                             SUBGRID_OUTLINE_COLOR.g, SUBGRID_OUTLINE_COLOR.b,
                             SUBGRID_OUTLINE_COLOR.a);
      SDL_RenderDrawRect(renderer, &rect);

      rect = {subgridsPos[row][column].x + 1, subgridsPos[row][column].y + 1,
              SUBGRID_WH - 2, SUBGRID_WH - 2};
      SDL_SetRenderDrawColor(renderer, SUBGRID_OUTLINE_COLOR.r,
                             SUBGRID_OUTLINE_COLOR.g, SUBGRID_OUTLINE_COLOR.b,
                             SUBGRID_OUTLINE_COLOR.a);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}

void Draw::drawTiles(GridTile **tiles) {
  int offset_x = SCENE_X_START;
  int offset_y = SCENE_Y_START;

  //Asigneaza pozitii pentru fiecare casuta
  for (int row = 0; row < GRID_TILES_NR; row++) {
    for (int column = 0; column < GRID_TILES_NR; column++) {
      tiles[row][column].setPosition({offset_x, offset_y});
      //Muta pozitia pe axa Ox cu un offset egal cu latimea casutei
      offset_x += GRID_TILE_SIZE;
    }
    //Reseteaza pozitia de start pe axa Ox
    offset_x = SCENE_X_START;
    //Muta pozitia pe axa Oy cu un offset egal cu lungimea casutei
    offset_y += GRID_TILE_SIZE;
  }

  for (int row = 0; row < GRID_TILES_NR; row++) {
    for (int column = 0; column < GRID_TILES_NR; column++) {
      Point2D pos = tiles[row][column].getPosition();
      SDL_Color color = tiles[row][column].getColor();
      //Pregateste casuta pentru desenare (fill)
      SDL_Rect rect = {pos.x, pos.y, GRID_TILE_SIZE, GRID_TILE_SIZE};
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(renderer, &rect);
      //Pregateste conturul casutei pentru desenare
      SDL_Rect rectOutline = {pos.x, pos.y, GRID_TILE_SIZE, GRID_TILE_SIZE};
      SDL_SetRenderDrawColor(renderer, TILES_OUTLINE_COLOR.r,
                             TILES_OUTLINE_COLOR.g, TILES_OUTLINE_COLOR.b,
                             TILES_OUTLINE_COLOR.a);
      SDL_RenderDrawRect(renderer, &rectOutline);

      //Afiseaza text doar pentru casutele care au alocat un numar intre 1-9
      // 0 = casuta empty
      if (tiles[row][column].getNumber() != 0) {
        Point2D textPos = pos;
        //Centreaza pozitia textului cu un offset
        textPos.x += 20;
        textPos.y += 8;
        drawText(std::to_string(tiles[row][column].getNumber()), TEXT_COLOR,
                 textPos, {28, 48});
      }
    }
  }
}
