#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

/* This and Item should probably have been inherited from the same base class,
   but I only realised that not long before submission. One more checkbox for
   future development! */

class Weapon : public GameObject {
public:
   Weapon(GameObject * const o,
          GameEngine * const e);
   ~Weapon();

   bool init(char const * const weaponString);
   bool initFromEngine(char const * const weaponString);

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
