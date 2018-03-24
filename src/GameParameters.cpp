#include <iostream>
#include <cstring>

#include "Game/GameParameters.h"
#include "Game/GameEngine.h"
#include "Global.h"

extern "C" {
#include "PF.h"
}

GameParameters::GameParameters(GameEngine * const e,
                               char const * const Filename,
                               bool * const paramFileIsValid)
      : GameObject(GAMEPARAMETERS), engine(e) {

   /* Defaults */
   this->MinRoll              =   0;
   this->MaxRoll              = 100;
   this->BaseMovement         =   1;
   this->BaseStrength         =  20;
   this->BaseShooting         =  50;
   this->BaseArmour           =  20;
   this->BaseMorale           = 100;
   this->BaseHealth           = 100;
   this->BaseCost             =  40;
   this->EncryptionKey        = "nhaekanckjanckaw";
   this->StartingCredits      = 500;
   this->MaxCaptainItems      = 6;
   this->MaxCaptainWeapons    = 2;
   this->MaxHierophantItems   = 4;
   this->MaxHierophantWeapons = 1;
   char EncryptionKeyTemp[MAX_LINE_LENGTH];

   /* Allocate memory */
   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nGameParameters];

   /* Build ParamEntries array */
   for (size_t i = 0; i < nGameParameters; i++) {
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
   strncpy(ParamEntries[iEncryptionKey].Parameter, "EncryptionKey", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iEncryptionKey].Type    = STRING;
   ParamEntries[iEncryptionKey].Pointer = EncryptionKeyTemp;
   strncpy(ParamEntries[iStartingCredits].Parameter, "StartingCredits", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iStartingCredits].Type    = INTEGER;
   ParamEntries[iStartingCredits].Pointer = &(this->StartingCredits);
   strncpy(ParamEntries[iMaxCaptainItems].Parameter, "MaxCaptainItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMaxCaptainItems].Type    = UNSIGNED_LONG_INTEGER;
   ParamEntries[iMaxCaptainItems].Pointer = &(this->MaxCaptainItems);
   strncpy(ParamEntries[iMaxCaptainWeapons].Parameter, "MaxCaptainWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMaxCaptainWeapons].Type    = UNSIGNED_LONG_INTEGER;
   ParamEntries[iMaxCaptainWeapons].Pointer = &(this->MaxCaptainWeapons);
   strncpy(ParamEntries[iMaxHierophantItems].Parameter, "MaxHierophantItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMaxHierophantItems].Type    = UNSIGNED_LONG_INTEGER;
   ParamEntries[iMaxHierophantItems].Pointer = &(this->MaxHierophantItems);
   strncpy(ParamEntries[iMaxHierophantWeapons].Parameter, "MaxHierophantWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iMaxHierophantWeapons].Type    = UNSIGNED_LONG_INTEGER;
   ParamEntries[iMaxHierophantWeapons].Pointer = &(this->MaxHierophantWeapons);

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(Filename, "r")) == NULL) {
      std::cerr << "ERROR: failed to load file " << ParamFile << std::endl;
      *paramFileIsValid = false;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nGameParameters) != EXIT_SUCCESS) {
      std::cerr << "ERROR: PF_ReadParameterFile failed" << std::endl;
      *paramFileIsValid = false;
   }

   this->EncryptionKey = std::string(EncryptionKeyTemp);

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);
}

GameParameters::~GameParameters() {
   /* blank */
}

void GameParameters::ensureValidity() const {
   ENSURE(type() == GAMEPARAMETERS, engine);
   ENSURE(MinRoll < MaxRoll, engine);
   ENSURE(EncryptionKey.length() > 0, engine);
}

void GameParameters::print() const {
   GameObject::print();
   printf("GameParameters:\n");
   printf("   Engine               = %p, ID = %zu\n", engine, engine->ID());
   printf("   MinRoll              = %d\n", MinRoll);
   printf("   MaxRoll              = %d\n", MaxRoll);
   printf("   BaseMovement         = %.2f\n", BaseMovement);
   printf("   BaseStrength         = %d\n", BaseStrength);
   printf("   BaseShooting         = %d\n", BaseShooting);
   printf("   BaseArmour           = %d\n", BaseArmour);
   printf("   BaseMorale           = %d\n", BaseMorale);
   printf("   BaseHealth           = %d\n", BaseHealth);
   printf("   BaseCost             = %d\n", BaseCost);
   printf("   EncryptionKey        = '%s'\n", EncryptionKey.c_str());
   printf("   StartingCredits      = %d\n", StartingCredits);
   printf("   MaxCaptainItems      = %zu\n", MaxCaptainItems);
   printf("   MaxCaptainWeapons    = %zu\n", MaxCaptainWeapons);
   printf("   MaxHierophantItems   = %zu\n", MaxHierophantItems);
   printf("   MaxHierophantWeapons = %zu\n", MaxHierophantWeapons);
}