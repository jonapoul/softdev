#include <string>

#include "Game/StatBoost.h"
#include "Game/GameEngine.h"
#include "Global.h"

StatBoost::StatBoost(GameEngine * const e,
                     GameObject * const o)
      : GameObject(STATBOOST), engine(e), owner(o) {
   /* blank, all defaults as listed in StatBoost.h */
}

StatBoost::~StatBoost() {
   /* blank? */
}

bool StatBoost::init(std::string const& stat,
                     std::string const& modifier) {
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
   else if (stat == "Strength") this->addStrength  = sign * std::stoi(valueStr);
   else if (stat == "Armour")   this->addArmour    = sign * std::stoi(valueStr);
   else if (stat == "Morale")   this->addMorale    = sign * std::stoi(valueStr);
   else if (stat == "Health")   this->addHealth    = sign * std::stoi(valueStr);
   else                         return false;

   return true;
}

void StatBoost::copy(StatBoost const * const other) {
   this->engine       = other->engine;
   this->addShooting  = other->addShooting;
   this->addStrength  = other->addStrength;
   this->addArmour    = other->addArmour;
   this->addMorale    = other->addMorale;
   this->addHealth    = other->addHealth;
   this->addMovement  = other->addMovement;
   this->multiplyCost = other->multiplyCost;
}

void StatBoost::add(StatBoost const * const other) {
   this->addShooting  += other->addShooting;
   this->addStrength  += other->addStrength;
   this->addArmour    += other->addArmour;
   this->addMorale    += other->addMorale;
   this->addHealth    += other->addHealth;
   this->addMovement  += other->addMovement;
   this->multiplyCost *= other->multiplyCost;
}

bool StatBoost::add(std::string const& stat,
                    std::string const& modifier) {
   StatBoost * extraBoost = new StatBoost(engine, this);
   bool isValid = extraBoost->init(stat, modifier);
   if (isValid) {
      this->add(extraBoost);
   }
   extraBoost->deallocate();
   return isValid;
}

void StatBoost::reset() {
   this->addStrength  = 0;
   this->addShooting  = 0;
   this->addArmour    = 0;
   this->addMorale    = 0;
   this->addHealth    = 0;
   this->addMovement  = 0.0;
   this->multiplyCost = 1.0;
}

bool StatBoost::isBlank() const {
   if (addStrength != 0) return false;
   if (addShooting != 0) return false;
   if (addArmour   != 0) return false;
   if (addMorale   != 0) return false;
   if (addHealth   != 0) return false;
   if (addMovement  > 0) return false;
   if (multiplyCost > 0) return false;
   return true;
}

void StatBoost::ensureValidity() const {
   ENSURE(type() == STATBOOST, engine);
   ENSURE(multiplyCost >= 0.0, engine);
   ENSURE(multiplyCost <= 1.0, engine);
   ENSURE(addStrength >= 0,    engine);
   ENSURE(addShooting >= 0,    engine);
   ENSURE(addArmour >= 0,      engine);
   ENSURE(addMorale >= 0,      engine);
   ENSURE(addHealth >= 0,      engine);
   ENSURE(isBlank() != true,   engine);
}

void StatBoost::print() const {
   GameObject::print();
   printf("StatBoost:\n");
   printf("   engine       = %p, ID = %lu\n", engine, engine->ID());
   printf("   owner        = %p, ID = %lu\n", owner, owner->ID());
   printf("   addStrength  = %d\n", addStrength);
   printf("   addShooting  = %d\n", addShooting);
   printf("   addArmour    = %d\n", addArmour);
   printf("   addMorale    = %d\n", addMorale);
   printf("   addHealth    = %d\n", addHealth);
   printf("   addMovement  = %.2f\n", addMovement);
   printf("   multiplyCost = %.2f\n", multiplyCost);
}