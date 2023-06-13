#include "game.h"

int main() {
  Game gameScene;

  gameScene.init(); // initializeaza scena jocului
  gameScene
      .run(); // pentru aincepe jocul si a-l mentine in executie pana cand
              // jucatorul decide sa il opreasca sau pana cand jocul se termina.

  return 0;
}