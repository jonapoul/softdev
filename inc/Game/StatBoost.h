#ifndef STATBOOST_H
#define STATBOOST_H

#include <string>
#include "Game/GameObject.h"

class GameEngine;

class StatBoost : public GameObject {
public:
   StatBoost(GameEngine * const e,
             GameObject * const o);
   StatBoost(StatBoost const * const other);
   ~StatBoost();

   bool init(std::string const& stat,
             std::string const& modifier);
   
   void copy(StatBoost const * const other);
   void add(StatBoost const * const other);
   bool add(std::string const& stat,
            std::string const& modifier);
   void reset();
   bool isBlank() const;

   virtual void ensureValidity() const;
   virtual void print() const;

   int   addStrength  = 0;
   int   addShooting  = 0;
   int   addArmour    = 0;
   int   addMorale    = 0;
   int   addHealth    = 0;
   float addMovement  = 0.0;
   float multiplyCost = 1.0;

private:
   GameEngine * engine;
   GameObject * owner;
};

#endif