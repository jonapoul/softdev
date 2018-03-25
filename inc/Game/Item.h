#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

/* This and Weapon should probably have been inherited from the same base class,
   but I only realised that not long before submission. One more checkbox for
   future development! */

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
   GameObject * owner; /* Squad or SpecialisedSquadMember or GameEngine */
   GameEngine * engine;
   StatBoost * boost;
   std::string name;
};

#endif
