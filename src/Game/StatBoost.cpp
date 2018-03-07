#include <string>

#include "Game/StatBoost.h"
#include "Game/GameEngine.h"
#include "Global.h"

StatBoost::StatBoost(GameEngine * const e) 
      : GameObject(STATBOOST), engine(e) {
   /* blank, all defaults */
}

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

/* Copying another */
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
   /* blank? */
}

void StatBoost::add(StatBoost const * const extraBoost) {
   this->addMovement  += extraBoost->addMovement;
   this->addShooting  += extraBoost->addShooting;
   this->addStrength  += extraBoost->addStrength;
   this->addArmour    += extraBoost->addArmour;
   this->addMorale    += extraBoost->addMorale;
   this->addHealth    += extraBoost->addHealth;
   this->multiplyCost *= extraBoost->multiplyCost;
}

bool StatBoost::add(std::string const& stat,
                    std::string const& modifier) {
   bool isValid = true;
   StatBoost * extraBoost = new StatBoost(engine, stat, modifier, &isValid);
   if (isValid) {
      this->add(extraBoost);
   }
   extraBoost->deallocate();
   return isValid;
}

void StatBoost::reset() {
   this->addMovement  = 0.0;
   this->addStrength  = 0;
   this->addShooting  = 0;
   this->addArmour    = 0;
   this->addMorale    = 0;
   this->addHealth    = 0;
   this->multiplyCost = 1.0;
}

void StatBoost::checkValidity() const {
   CHECK(type() == STATBOOST, engine);
   CHECK(multiplyCost >= 0.0, engine);
   CHECK(multiplyCost <= 1.0, engine);

   /* blank? */
}