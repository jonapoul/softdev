#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

typedef enum {
   InitialiseItem,
   MatchItem,
   nItemConstructors
} ItemConstructor;

class Item : public GameObject {
public:
   Item(GameObject * const o,
        GameEngine * const e,
        char const * const itemString,
        bool * const isValid,
        ItemConstructor const test = MatchItem);
   ~Item();

   StatBoost * getBoost() const;
   void setOwner(GameObject * const object);
   virtual void checkValidity() const;

private:
   GameObject * owner;
   GameEngine * engine;
   StatBoost * boost;
   std::string name;
};

#endif
