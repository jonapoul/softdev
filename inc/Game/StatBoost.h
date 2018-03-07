#ifndef STATBOOST_H
#define STATBOOST_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;

class StatBoost : public GameObject {
public:
   StatBoost(GameEngine * const e);
   StatBoost(GameEngine * const e,
             std::string const& stat,
             std::string const& modifier,
             bool * const isValid);
   StatBoost(StatBoost const * const other);
   ~StatBoost();

   void add(StatBoost const * const other);
   bool add(std::string const& stat,
            std::string const& modifier);
   void reset();

   virtual void checkValidity() const;

   float addMovement  = 0.0;
   int   addStrength  = 0;
   int   addShooting  = 0;
   int   addArmour    = 0;
   int   addMorale    = 0;
   int   addHealth    = 0;
   float multiplyCost = 1.0;

private:
   GameEngine * engine;
};

#endif