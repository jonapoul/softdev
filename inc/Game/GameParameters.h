#ifndef GAME_PARAMETERS_H
#define GAME_PARAMETERS_H

#include <cstddef>
#include <stdio.h>
#include <string>

#include "Game/GameObject.h"

extern "C" {
#include "PF.h"
}

class GameEngine;

enum {
   iMinRoll,
   iMaxRoll,
   iBaseMovement,
   iBaseStrength,
   iBaseShooting,
   iBaseArmour,
   iBaseMorale,
   iBaseHealth,
   iBaseCost,
   iEncryptionKey,
   iStartingCredits,
   iMaxCaptainItems,
   iMaxCaptainWeapons,
   iMaxHierophantItems,
   iMaxHierophantWeapons,
   nGameParameters
};

class GameParameters : public GameObject {
public:
   GameParameters(GameEngine * const e,
                  char const * const Filename,
                  bool * const paramFileIsValid);
   ~GameParameters();

   virtual void ensureValidity() const;
   virtual void print() const;

   int MinRoll;
   int MaxRoll;
   float BaseMovement;
   int BaseStrength;
   int BaseShooting;
   int BaseArmour;
   int BaseMorale;
   int BaseHealth;
   int BaseCost;
   std::string EncryptionKey;
   int StartingCredits;
   size_t MaxCaptainItems;
   size_t MaxCaptainWeapons;
   size_t MaxHierophantItems;
   size_t MaxHierophantWeapons;
   
private:
   GameEngine * engine;
};

#endif