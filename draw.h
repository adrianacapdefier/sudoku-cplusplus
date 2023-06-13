#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "point2d.h"
#include "config.hpp"
#include <iostream>
#include "point2d.h"
#include "size.h"
#include "gridtile.h"

 class Draw {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    TTF_Font* font = nullptr;

public:
    Draw() {
        if (TTF_Init() == -1) {
            std::cout << TTF_GetError() << '\n';
        }
        font = TTF_OpenFont(FONT_PATH, 164);
        if (font == nullptr) {
            std::cout << "Could not load font\n";
        }
    }
    void setRenderer(SDL_Renderer* renderer);
    void drawStartView();
    void drawText(const std::string& text, SDL_Color color, Point2D position, Size size);
    void drawGridOutline();
    void drawSubgrids();
    void drawTiles(GridTile** tiles);

 private:
     void drawRectangle();
     void drawNumbers();
};


