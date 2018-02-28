#include "pch.h"

#include "Parameters.h"
#include "PF.h"
#include "functions.h"

Parameters::Parameters(char const * const Filename)
   : MinRoll(0), MaxRoll(100), BaseMovement(1), BaseStrength(20), BaseShooting(50), 
     BaseArmour(20), BaseMorale(100), BaseHealth(100), BaseCost(40) {

   std::ifstream ParamsFile(Filename);
   std::string Line;
}