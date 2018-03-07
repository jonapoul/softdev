#include <sstream>
#include <string>

#include "Game/Weapon.h"
#include "Game/GameEngine.h"
#include "Game/SquadMember.h"
#include "Game/StatBoost.h"
#include "Global.h"

Weapon::Weapon(GameObject * const o,
               GameEngine * const e,
               char const * const weaponString,
               bool * const isValid,
               WeaponConstructor const test)
      : GameObject(WEAPON), owner(o), engine(e), boost(nullptr), name("") {

   switch (test) {
      /* For GameEngine::initWeapons(), reading a 3-word string to find:
            1) Weapon name,    e.g. "Battleaxe"
            2) Modifier,       e.g. "+3"
            3) Stat to modify, e.g. "Strength"
         and then apply that modifier to a StatBoost object */
      case InitialiseWeapon: {
         if (Global::wordCount(weaponString) != 3) {
            *isValid = false;
            return;
         }
         std::stringstream ss(weaponString);
         std::string modifier, modifiedStat;
         ss >> this->name >> modifier >> modifiedStat;

         bool boostIsValid = true;
         this->boost = new StatBoost(engine, modifiedStat, modifier, &boostIsValid);
         if (!boostIsValid) {
            boost->deallocate();
            *isValid = false;
            return;
         }
         return;
      }

      /* For all other instances. Reads a single word string and compares that to the
         GameEngine::all_valid_weapons array to grab the relevant StatBoost. */
      case MatchWeapon:
         this->name = std::string(weaponString);
         if (Global::wordCount(weaponString) != 1) {
            *isValid = false;
            return;
         }
         for (Weapon * weapon : engine->allWeapons()) {
            if (weapon->name == this->name) {
               this->boost = new StatBoost(weapon->boost);
               return;
            }
         }
         *isValid = false; /* no match? invalid */
         return;

      default:
         *isValid = false;
         return;
   } /* end switch */
}

Weapon::~Weapon() {
   boost->deallocate();
}

StatBoost * Weapon::getBoost() const {
   return this->boost;
}

void Weapon::setOwner(GameObject * const object) {
   this->owner = object;
}

void Weapon::checkValidity() const {
   CHECK(type() == WEAPON, engine);
   CHECK(name.length() > 0, engine);
}