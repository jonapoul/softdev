#ifndef GAME_PARAMETERS_H
#define GAME_PARAMETERS_H

#include <cstddef>
#include <stdio.h>

extern "C" {
#include "PF.h"
}

#define ENCRYPTION_KEY_SIZE MAX_PARAMETER_NAME_LENGTH

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
   nGameParameters
};

class GameParameters {
public:
   GameParameters(char const * const Filename,
                  bool * const paramFileIsValid);
   ~GameParameters();

   int writeToFile(PF_ParameterEntry * const ParameterEntries,
                   size_t const NParameterEntries,
                   char const * const Filename);

   int MinRoll;
   int MaxRoll;
   float BaseMovement;
   int BaseStrength;
   int BaseShooting;
   int BaseArmour;
   int BaseMorale;
   int BaseHealth;
   int BaseCost;
   char* EncryptionKey;
};

#endif