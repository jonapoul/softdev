#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

class Parameters {
public:
   Parameters(char const * const Filename);

   int MinRoll;
   int MaxRoll;
   int BaseMovement;
   int BaseStrength;
   int BaseShooting;
   int BaseArmour;
   int BaseMorale;
   int BaseHealth;
   int BaseCost;
};

#endif