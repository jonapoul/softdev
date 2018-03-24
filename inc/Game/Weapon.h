#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

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

private:
   GameObject * owner;
   GameEngine * engine;
   StatBoost * boost;
   std::string name;
};

#endif
