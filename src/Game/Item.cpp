#include <sstream>
#include <string>

#include "Game/Item.h"
#include "Game/GameEngine.h"
#include "Game/SquadMember.h"
#include "Game/StatBoost.h"
#include "Global.h"

Item::Item(GameObject * const o,
           GameEngine * const e,
           char const * const itemString,
           bool * const isValid,
           ItemConstructor const test)
      : GameObject(ITEM), owner(o), engine(e), boost(nullptr), name("") {

   switch (test) {
      /* For GameEngine::initItems(), reading a 3-word string to find:
            1) Item name,      e.g. "HealthPotion"
            2) Modifier,       e.g. "+50"
            3) Stat to modify, e.g. "Health"
         and then apply that modifier to a StatBoost object */
      case InitialiseItem: {
         if (Global::wordCount(itemString) != 3) {
            *isValid = false;
            return;
         }
         std::stringstream ss(itemString);
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
         GameEngine::all_valid_items array to grab the relevant StatBoost. */
      case MatchItem:
         this->name = std::string(itemString);
         if (Global::wordCount(itemString) != 1) {
            *isValid = false;
            return;
         }
         for (Item * item : engine->allItems()) {
            if (item->name == this->name) {
               this->boost = new StatBoost(item->boost);
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

Item::~Item() {
   boost->deallocate();
}

StatBoost * Item::getBoost() const {
   return this->boost;
}

void Item::setOwner(GameObject * const object) {
   this->owner = object;
}

void Item::checkValidity() const {
   CHECK(type() == ITEM, engine);
   CHECK(name.length() > 0, engine);
}