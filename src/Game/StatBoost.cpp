#include <string>

#include "Game/StatBoost.h"
#include "Game/GameEngine.h"
#include "Global.h"

StatBoost::StatBoost(GameEngine * const e,
                     std::string const& stat,
                     std::string const& modifier,
                     bool * const isValid)
      : GameObject(STATBOOST), engine(e) {
   int sign;
   std::string valueStr;
   if (!isdigit(modifier[0])) {
      sign     = (modifier[0] == '-') ? -1 : 1;
      valueStr = modifier.substr(1);
   } else {
      sign     = 1;
      valueStr = modifier;
   }

   if      (stat == "Cost")     this->multiplyCost =        std::stof(valueStr);
   else if (stat == "Movement") this->addMovement  = sign * std::stof(valueStr);
   else if (stat == "Shooting") this->addShooting  = sign * std::stoi(valueStr);
   else if (stat == "Strength") this->addShooting  = sign * std::stoi(valueStr);
   else if (stat == "Armour")   this->addArmour    = sign * std::stoi(valueStr);
   else if (stat == "Morale")   this->addMorale    = sign * std::stoi(valueStr);
   else if (stat == "Health")   this->addHealth    = sign * std::stoi(valueStr);
   else                         *isValid = false;
}

StatBoost::StatBoost(StatBoost const * const that)
      : GameObject(that->type()) {
   this->engine       = that->engine;
   this->addMovement  = that->addMovement;
   this->addShooting  = that->addShooting;
   this->addStrength  = that->addStrength;
   this->addArmour    = that->addArmour;
   this->addMorale    = that->addMorale;
   this->addHealth    = that->addHealth;
   this->multiplyCost = that->multiplyCost;
}

StatBoost::~StatBoost() {

}

void StatBoost::checkValidity() const {
   /* blank? */
}