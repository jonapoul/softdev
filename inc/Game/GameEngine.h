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
class Item;
class Weapon;

class GameEngine : public GameObject {
public:
   GameEngine(GameWindow * const gw = nullptr);
   ~GameEngine();

   std::vector<Item *> allItems() const;
   std::vector<Weapon *> allWeapons() const;

   void criticalMessage(char const * const message) const;
   void warningMessage(char const * const message) const;
   void informationMessage(char const * const message) const;

   bool login(Player const * const player,
              std::string const& plaintextPassword);
   
   void initGameParameters(char const * const filename);
   void initDie();
   void initItems(char const * const filename);
   void initWeapons(char const * const filename);
   void initPlayers(char const * const directory);

   virtual void checkValidity() const;

   Die * die;
   GameParameters * parameters;

private:
   GameWindow * window;
   std::vector<Player *> players;
   std::vector<Item *> all_valid_items;
   std::vector<Weapon *> all_valid_weapons;
};

#endif

