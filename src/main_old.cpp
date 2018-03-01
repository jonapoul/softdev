#include <iostream>
#include "functions.h"
#include "Game.h"

int main_old() {
   auto start = std::chrono::high_resolution_clock::now();

   Game* game = new Game();
   game->run();

   delete game;
   std::cout << "Runtime = " << time_since(start) << std::endl;
   return 1;
}