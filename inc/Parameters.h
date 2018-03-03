#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

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
   nParameters
};

class Parameters {
public:
   Parameters(char const * const Filename);
   ~Parameters();
   int writeToFile(PF_ParameterEntry * const ParameterEntries,
                   size_t const NParameterEntries,
                   char const * const Filename);

   // size_t NumParameters;
   // void ** DataPtrs;
   // DataType * datatypes;

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