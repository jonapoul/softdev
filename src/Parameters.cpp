#include <iostream>
#include <cstring>

#include "Parameters.h"
extern "C" {
#include "PF.h"
}

Parameters::Parameters(char const * const Filename) {
   /* Defaults */
   this->MinRoll      =   0;
   this->MaxRoll      = 100;
   this->BaseMovement =   1;
   this->BaseStrength =  20;
   this->BaseShooting =  50;
   this->BaseArmour   =  20;
   this->BaseMorale   = 100;
   this->BaseHealth   = 100;
   this->BaseCost     =  40;

   /* Allocate memory */
   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nParameters];

   /* Build ParamEntries array */
   for (size_t i = 0; i < nParameters; i++) {
      ParamEntries[i].IsBoolean = 0;
      ParamEntries[i].IsArray   = 0;
   }

   strncpy(ParamEntries[iMinRoll].Parameter, "MinRoll", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMinRoll].Type    = INTEGER;
   ParamEntries[iMinRoll].Pointer = &(this->MinRoll);

   strncpy(ParamEntries[iMaxRoll].Parameter, "MaxRoll", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMaxRoll].Type    = INTEGER;
   ParamEntries[iMaxRoll].Pointer = &(this->MaxRoll);

   strncpy(ParamEntries[iBaseMovement].Parameter, "BaseMovement", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseMovement].Type    = FLOAT;
   ParamEntries[iBaseMovement].Pointer = &(this->BaseMovement);

   strncpy(ParamEntries[iBaseStrength].Parameter, "BaseStrength", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseStrength].Type    = INTEGER;
   ParamEntries[iBaseStrength].Pointer = &(this->BaseStrength);

   strncpy(ParamEntries[iBaseShooting].Parameter, "BaseShooting", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseShooting].Type    = INTEGER;
   ParamEntries[iBaseShooting].Pointer = &(this->BaseShooting);

   strncpy(ParamEntries[iBaseArmour].Parameter, "BaseArmour", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseArmour].Type    = INTEGER;
   ParamEntries[iBaseArmour].Pointer = &(this->BaseArmour);

   strncpy(ParamEntries[iBaseMorale].Parameter, "BaseMorale", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseMorale].Type    = INTEGER;
   ParamEntries[iBaseMorale].Pointer = &(this->BaseMorale);

   strncpy(ParamEntries[iBaseHealth].Parameter, "BaseHealth", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseHealth].Type    = INTEGER;
   ParamEntries[iBaseHealth].Pointer = &(this->BaseHealth);

   strncpy(ParamEntries[iBaseCost].Parameter, "BaseCost", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iBaseCost].Type    = INTEGER;
   ParamEntries[iBaseCost].Pointer = &(this->BaseCost);

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(Filename, "r")) == NULL) {
      std::cerr << "ERROR: failed to load file " << ParamFile << std::endl;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nParameters) != EXIT_SUCCESS) {
      std::cerr << "ERROR: PF_ReadParameterFile failed" << std::endl;
   }

   /* Print the Parameters using PF_WriteParameters */
   std::cout << std::string(50, '-') << std::endl
             << "Priting Parameters:" << std::endl;
   if (PF_WriteParameters(ParamEntries, nParameters) != EXIT_SUCCESS) {
      std::cerr << "ERROR: PF_WriteParameters failed" << std::endl;
   }
   std::cout << std::string(50, '-') << std::endl;

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);
}