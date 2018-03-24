#include <sstream>
#include <string>

#include "Game/Item.h"
#include "Game/GameEngine.h"
#include "Game/SquadMember.h"
#include "Game/StatBoost.h"
#include "Global.h"

Item::Item(GameObject * const o,
           GameEngine * const e)
      : GameObject(ITEM), owner(o), engine(e), boost(nullptr), name("") { }

Item::~Item() {
   boost->deallocate();
}

/* Expecting a single word string to represent the name of the item.
   Then we go through all the preinitialised items in the GameEngine array of
   available items and check whether this is in that array. */
bool Item::init(char const * const itemString) {
   this->name = std::string(itemString);
   if (Global::wordCount(itemString) != 1) {
      return false;
   }
   for (Item * item : engine->allItems()) {
      if (item->name == this->name) {
         this->boost = new StatBoost(item->boost);
         return true;
      }
   }
   return false; /* no match? invalid */
}

/* Expecting a 3-word string in the format:
      1) Item name,      e.g. "HealthPotion"
      2) Modifier,       e.g. "+50"
      3) Stat to modify, e.g. "Health"
   and then apply that modifier to a StatBoost object
   This is only called from GameEngine when populating the list of all available
   items.
*/
bool Item::initFromEngine(char const * const itemString) {
   if (Global::wordCount(itemString) != 3) {
      return false;
   }
   std::stringstream ss(itemString);
   std::string modifier, modifiedStat;
   ss >> this->name >> modifier >> modifiedStat;

   this->boost = new StatBoost(engine);
   bool const boostIsValid = boost->init(modifiedStat, modifier);
   if (!boostIsValid) {
      boost->deallocate();
      return false;
   } else {
      return true;
   }
}

StatBoost * Item::getBoost() const {
   return this->boost;
}

void Item::setOwner(GameObject * const object) {
   this->owner = object;
}

void Item::ensureValidity() const {
   ENSURE(type() == ITEM,    engine);
   ENSURE(name.length() > 0, engine);
}