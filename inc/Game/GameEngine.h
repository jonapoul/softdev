#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <string>

class GameWindow;
class GameParameters;
class Player;
class Die;

class GameEngine {
public:
   GameEngine(GameWindow * const gw = nullptr);
   ~GameEngine();

   void criticalMessage(char const * const message);
   void warningMessage(char const * const message);
   void informationMessage(char const * const message);

   void readUserFiles();
   bool login(Player const * const player,
              std::string const& plaintextPassword);
   void initialisePlayers();

private:
   GameWindow * window;
   Die * die;
   GameParameters * parameters;
   std::vector<Player *> players;
};

#endif

