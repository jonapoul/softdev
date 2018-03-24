#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

class Item : public GameObject {
public:
   Item(GameObject * const o,
        GameEngine * const e);
   ~Item();

   bool init(char const * const itemString);
   bool initFromEngine(char const * const itemString);

   StatBoost * getBoost() const;
   void setOwner(GameObject * const object);
   virtual void ensureValidity() const;
   virtual void print() const;

private:
   GameObject * owner; /* either Squad or Player or GameEngine */
   GameEngine * engine;
   StatBoost * boost;
   std::string name;
};

#endif
