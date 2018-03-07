#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;
class StatBoost;

typedef enum {
   InitialiseWeapon,
   MatchWeapon,
   nWeaponConstructors
} WeaponConstructor;

class Weapon : public GameObject {
public:
   Weapon(GameObject * const o,
          GameEngine * const e,
          char const * const weaponString,
          bool * const isValid,
          WeaponConstructor const test = MatchWeapon);
   ~Weapon();

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
