#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <string>

#include "Game/GameObject.h"

/* For criticalMessage, warningMessage and informationMessage */
#define MAX_MESSAGE_LENGTH 256

class GameWindow;
class GameParameters;
class Player;
class Die;

class GameEngine : public GameObject {
public:
   GameEngine(GameWindow * const gw = nullptr);
   ~GameEngine();

   void criticalMessage(char const * const message) const;
   void warningMessage(char const * const message) const;
   void informationMessage(char const * const message) const;

   void readUserFiles();
   bool login(Player const * const player,
              std::string const& plaintextPassword);
   void initialisePlayers(char const * const directory);

   virtual void checkValidity() const;

   Die * die;
   GameParameters * parameters;

private:
   GameWindow * window;
   std::vector<Player *> players;
};

#endif

