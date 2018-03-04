#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <string>

/* For criticalMessage, warningMessage and informationMessage */
#define MAX_MESSAGE_LENGTH 256

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
   void initialisePlayers(char const * const directory);

   Die * die;
   GameParameters * parameters;

private:
   GameWindow * window;
   std::vector<Player *> players;
};

#endif

