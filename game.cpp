#include "game.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "config.hpp"
#include "gridtile.h"
#include "random"
#include <cstddef>
#include <string>

void Game::run() {
  SDL_Event e; // Event reprezinta o tasta apasata
  int b = 0;

  while (isQuit == false) { // se verifica daca s-a apasat butonul Quit
    if (SDL_WaitEvent(&e)) {
      getUserInput(&e, &isQuit);
    }
    if (reinit) {
      reinitGrid();
      reinit = false;
    }
    redraw(); // redeseneaza, adica o ia de la capat;
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit(); // deinitializeaza
}
void Game::init() {
  // Create window
  window = SDL_CreateWindow(
      "Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_SHOWN); 
                         
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  pen.setRenderer(renderer); /*pen - ul deseneaza cu ajutorul renderer - ului,
                             facand referinta la acesta*/
  initScene();
  isQuit = false;       // se verifica daca s-a apasat butonul "QUIT"; in caz contrar jocul incepe
  sm = GameSM::STARTED; // in caz contrar jocul incepe
  initGrid();
  executionTime = 0;
  reinit = false;
}

void Game::initScene() {
  SDL_SetRenderDrawColor(renderer, SCENE_BACKGROUND_COLOR.r,
                         SCENE_BACKGROUND_COLOR.g, SCENE_BACKGROUND_COLOR.b,
                         SCENE_BACKGROUND_COLOR.a); // se alege culoarea
  SDL_RenderClear(renderer); //sterge fereastra cu culoarea respectiva

  score = 0;
}

void Game::generateRandomGrid() {}

void Game::redraw() {
  // Reseteaza suprafata de desenare
  SDL_SetRenderDrawColor(renderer, SCENE_BACKGROUND_COLOR.r,
                         SCENE_BACKGROUND_COLOR.g, SCENE_BACKGROUND_COLOR.b,
                         SCENE_BACKGROUND_COLOR.a);
  SDL_RenderClear(renderer);

  // Deseneaza interiorul gridului
  pen.drawTiles(gridTiles);
  // Deseneaza conturul submatricilor
  pen.drawSubgrids();
  // Deseneaza conturul gridului
  pen.drawGridOutline();
  // Deseneaza textul pentru timpul de executie
  // Masurat in microsecunde
  pen.drawText("Timp de executie: " + std::to_string(executionTime) + "us",
               TEXT_COLOR, {10, 10}, {232, 38});

  SDL_RenderPresent(renderer);
}

void Game::getUserInput(SDL_Event *e, bool *quit) {
  switch (e->type) {
  // Muta pozitia in jos
  case SDL_KEYDOWN: {
    switch (e->key.keysym.sym) {
    case SDL_KeyCode::SDLK_DOWN: {
      // Executa atat timp cat nu depaseste marginile matricii
      if (selected.row + 1 < GRID_TILES_NR) {
        if (gridTiles[selected.row][selected.column].getIsLocked()) {
          // Daca a fost casuta completata de la inceput reseteaza la culoarea
          // default
          gridTiles[selected.row][selected.column].setColor(TILES_FILL_COLOR);
        } else {
          // Daca a fost casuta obligatorie de completat reseteaza la culoarea
          // default
          gridTiles[selected.row][selected.column].setColor(TILES_EMPTY_COLOR);
        }
        // Incrementeaza pentru urmatoarea pozitie
        selected.row++;
        // Schimba cu culoarea pentru casuta selectata
        gridTiles[selected.row][selected.column].setColor(TILES_SELECTED_COLOR);
      }
      break;
    }
    // Muta pozitia in sus
    case SDL_KeyCode::SDLK_UP: {
      if (selected.row > 0) {
        if (gridTiles[selected.row][selected.column].getIsLocked()) {
          gridTiles[selected.row][selected.column].setColor(TILES_FILL_COLOR);
        } else {
          gridTiles[selected.row][selected.column].setColor(TILES_EMPTY_COLOR);
        }
        selected.row -= 1;
        gridTiles[selected.row][selected.column].setColor(TILES_SELECTED_COLOR);
      }
      break;
    }
    // Muta pozitia la dreapta
    case SDL_KeyCode::SDLK_RIGHT: {
      if (selected.column + 1 < GRID_TILES_NR) {
        if (gridTiles[selected.row][selected.column].getIsLocked()) {
          gridTiles[selected.row][selected.column].setColor(TILES_FILL_COLOR);
        } else {
          gridTiles[selected.row][selected.column].setColor(TILES_EMPTY_COLOR);
        }
        selected.column++;
        gridTiles[selected.row][selected.column].setColor(TILES_SELECTED_COLOR);
      }
      break;
    }
    // Muta pozitia la stanga
    case SDL_KeyCode::SDLK_LEFT: {
      if (selected.column > 0) {
        if (gridTiles[selected.row][selected.column].getIsLocked()) {
          gridTiles[selected.row][selected.column].setColor(TILES_FILL_COLOR);
        } else {
          gridTiles[selected.row][selected.column].setColor(TILES_EMPTY_COLOR);
        }
        selected.column -= 1;
        gridTiles[selected.row][selected.column].setColor(TILES_SELECTED_COLOR);
      }
      break;
    }

    case SDL_KeyCode::SDLK_BACKSPACE: {
      // Sterge numarul ales anterior pentru casuta selectata
      if (!gridTiles[selected.row][selected.column].getIsLocked()) {
        gridTiles[selected.row][selected.column].setNumber(0);
      }
      break;
    }

    case SDL_KeyCode::SDLK_SPACE: {
      //Incepe timpul de masurat
      auto start = std::chrono::high_resolution_clock::now();
      //Executa algoritmul de sudoku
      if(!solver.solveSudoku()) {
        //Nu exista solutie
      }
      //Se opreste timpul de masurat
      auto stop = std::chrono::high_resolution_clock::now();
      //Calculeaza durata in microsecunde
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      executionTime = duration.count();
      break;
    }

    case SDL_KeyCode::SDLK_r: {
      //Re-initializeaza gridul cu un puzzle nou
      if (gridTiles != nullptr) {
        reinit = true;
      }
      break;
    }
    default: {
        if (!gridTiles[selected.row][selected.column].getIsLocked()) {
            // Converteste de la codul tastaturii la numarul corespunzator
            int number = getNumberFromKeyCode(e->key.keysym.sym);
            // Aloca numar pentru casuta
            gridTiles[selected.row][selected.column].setNumber(number);
        }
        break;
    }
    }
    break;
  }

  case SDL_QUIT: {
    //Opreste program
    *quit = true;
    break;
  }
  default:
    break;
  }
}

void Game::initTiles(const int puzzle[][GRID_TILES_NR]) {
  //Aloca numerele dintr-un puzzle predefinit din configuratie ales random
  for (int row = 0; row < GRID_TILES_NR; row++) {
    for (int column = 0; column < GRID_TILES_NR; column++) {
      gridTiles[row][column].setNumber(puzzle[row][column]);
    }
  }
}

void Game::selectPuzzle() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 3);

  int x = dist6(rng);

  //Alege random un puzzle din configuratie
  switch (x) {
  case 1:
    initTiles(SUDOKU_PUZZLE_1);
    break;

  case 2:
    initTiles(SUDOKU_PUZZLE_2);
    break;

  case 3:
    initTiles(SUDOKU_PUZZLE_3);
    break;

  default:
    break;
  }
}

int Game::getNumberFromKeyCode(SDL_Keycode key) {
  int retVal;

  //Converteste din cod tastatura in numarul corespunzator
  switch (key) {
  case SDL_KeyCode::SDLK_1: {
    retVal = 1;
    break;
  }
  case SDL_KeyCode::SDLK_2: {
    retVal = 2;
    break;
  }
  case SDL_KeyCode::SDLK_3: {
    retVal = 3;
    break;
  }
  case SDL_KeyCode::SDLK_4: {
    retVal = 4;
    break;
  }
  case SDL_KeyCode::SDLK_5: {
    retVal = 5;
    break;
  }
  case SDL_KeyCode::SDLK_6: {
    retVal = 6;
    break;
  }
  case SDL_KeyCode::SDLK_7: {
    retVal = 7;
    break;
  }
  case SDL_KeyCode::SDLK_8: {
    retVal = 8;
    break;
  }
  case SDL_KeyCode::SDLK_9: {
    retVal = 9;
    break;
  }

  default:
    break;
  }

  return retVal;
}

void Game::deleteGrid() {
  for (int i = 0; i < GRID_TILES_NR; i++) {
    delete gridTiles[i];
  }
  delete[] gridTiles;
  gridTiles = nullptr;
}

void Game::initGrid() {
  gridTiles = new GridTile *[GRID_TILES_NR];

  for (int i = 0; i < GRID_TILES_NR; i++) {
    gridTiles[i] = new GridTile[GRID_TILES_NR];
  }

  selectPuzzle();
  solver.setTiles(gridTiles);
  //Sterge random casute din puzzle-ul ales mai devreme
  solver.eraseTiles();

  gridTiles[0][0].setColor(TILES_SELECTED_COLOR);
}

void Game::reinitGrid() {
  //Re-initializeaza cu un puzzle nou
  deleteGrid();
  initGrid();
}