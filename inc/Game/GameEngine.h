#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <string>

#include "config.h"
#include "Game/GameObject.h"

/* For criticalMessage, warningMessage and informationMessage */
#define MAX_MESSAGE_LENGTH 256

#ifdef ENABLE_QT_UI
class GameWindow;
#endif
class GameParameters;
class Player;
class Die;
class Item;
class Weapon;
class SkillTree;

class GameEngine : public GameObject {

   friend class TestSuite;

public:

#ifdef ENABLE_QT_UI
   GameEngine(GameWindow * const gw);
#else
   GameEngine();
#endif
   ~GameEngine();

   void init();

   std::vector<Item *> allItems() const;
   std::vector<Weapon *> allWeapons() const;
   std::vector<SkillTree *> allSkillTrees() const;

   void criticalMessage(char const * const message) const;
   void warningMessage(char const * const message) const;
   void informationMessage(char const * const message) const;

   bool login(Player const * const player,
              std::string const& plaintextPassword);

   virtual void ensureValidity() const;
   virtual void print() const;

   void readCaptainSkillTreeFile(char const * const filename);
   void readHierophantSkillTreeFile(char const * const filename);
   void initGameParameters(char const * const filename);
   void initDie();
   void initItems(char const * const filename);
   void initWeapons(char const * const filename);
   void initSkillTrees(char const * const directory);
   void initPlayers(char const * const directory);

#ifdef ENABLE_QT_UI
   GameWindow * window = nullptr;
#endif
   Die * die = nullptr;
   GameParameters * parameters = nullptr;
   std::vector<Player *> players;

   /* These three arrays store every possible item/weapon/skilltree. When a new
      squad/player/whatever is created, it references these three to make sure
      that it's being built properly. */
   std::vector<Item *> all_valid_items;
   std::vector<Weapon *> all_valid_weapons;
   std::vector<SkillTree *> all_valid_skilltrees;
};

#endif

