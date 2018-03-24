#include <sstream>
#include <string>

#include "Game/Weapon.h"
#include "Game/GameEngine.h"
#include "Game/SquadMember.h"
#include "Game/StatBoost.h"
#include "Global.h"

Weapon::Weapon(GameObject * const o,
               GameEngine * const e)
      : GameObject(WEAPON), owner(o), engine(e), boost(nullptr), name("") { }

Weapon::~Weapon() {
   boost->deallocate();
}

/* Expecting a single word string to represent the name of the weapon.
   Then we go through all the preinitialised weapons in the GameEngine array of
   available weapons and check whether this is in that array. */
bool Weapon::init(char const * const weaponString) {
   this->name = std::string(weaponString);
   if (Global::wordCount(weaponString) != 1) {
      return false;
   }
   for (Weapon * w : engine->allWeapons()) {
      if (w->name == this->name) {
         this->boost = new StatBoost(w->boost);
         return true;
      }
   }
   return false; /* no match? invalid */
}

/* Expecting a 3-word string in the format:
      1) Weapon name,      e.g. "HealthPotion"
      2) Modifier,       e.g. "+50"
      3) Stat to modify, e.g. "Health"
   and then apply that modifier to a StatBoost object
   This is only called from GameEngine when populating the list of all available
   weapons.
*/
bool Weapon::initFromEngine(char const * const weaponString) {
   if (Global::wordCount(weaponString) != 3) {
      return false;
   }
   std::stringstream ss(weaponString);
   std::string modifier, modifiedStat;
   ss >> this->name >> modifier >> modifiedStat;

   this->boost = new StatBoost(engine, this);
   bool const boostIsValid = boost->init(modifiedStat, modifier);
   if (!boostIsValid) {
      boost->deallocate();
      return false;
   } else {
      return true;
   }
}

StatBoost * Weapon::getBoost() const {
   return this->boost;
}

void Weapon::setOwner(GameObject * const object) {
   this->owner = object;
}

void Weapon::ensureValidity() const {
   ENSURE(type() == WEAPON, engine);
   ENSURE(name.length() > 0, engine);
}

void Weapon::print() const {
   GameObject::print();
   printf("Weapon:\n");
   printf("   name   = '%s'\n", name.c_str());
   printf("   engine = %p, ID = %zu\n", engine, engine->ID());
   printf("   owner  = %p, ID = %zu\n", owner, owner->ID());
   printf("   boost  = %p, ID = %zu\n", boost, boost->ID());
}