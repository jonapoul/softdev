#include <iostream>
#include <cstring>

#include "Game/GameParameters.h"
#include "Game/GameEngine.h"

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

/* Copied PF_WriteParameters(), but writing to file instead of terminal */
int GameParameters::writeToFile(PF_ParameterEntry * const ParameterEntries,
                                size_t const NParameterEntries,
                                char const * const Filename) {
   char criticalbuf[MAX_LINE_LENGTH];
   snprintf(criticalbuf, MAX_LINE_LENGTH,
            "%s: Need to redo function with streams rather than fprintf",
            __FUNCTION__);
   engine->criticalMessage(criticalbuf);
   return EXIT_FAILURE;

   FILE * OutputFile = fopen(Filename, "w");
   for (size_t i = 0; i < NParameterEntries; i++) {
      PF_ParameterEntry * ParameterEntry = &(ParameterEntries[i]);
      if (ParameterEntry->IsBoolean == 1) {
         if ( *((int *)ParameterEntry->Pointer) == 1) {
            fprintf(OutputFile, "%s\n",ParameterEntry->Parameter);
         }
      } else if(ParameterEntry->IsArray==1) {
         for (size_t j = 0; j < *(ParameterEntry->NArrayElements); j++) {
            switch(ParameterEntry->Type) {
            case INTEGER:
               fprintf(OutputFile, "%s[%lu] %i\n",
                       ParameterEntry->Parameter, j,
                       (*((int **)(ParameterEntry->Pointer)))[j]);
               break;
            case LONG_INTEGER:
               fprintf(OutputFile, "%s[%lu] %li\n",
                       ParameterEntry->Parameter, j,
                       (*((long int **)(ParameterEntry->Pointer)))[j]);
               break;
            case UNSIGNED_INTEGER:
               fprintf(OutputFile, "%s[%lu] %u\n",
                       ParameterEntry->Parameter, j,
                       (*((unsigned int **)(ParameterEntry->Pointer)))[j]);
               break;
            case UNSIGNED_LONG_INTEGER:
               fprintf(OutputFile, "%s[%lu] %lu\n",
                       ParameterEntry->Parameter, j,
                       (*((unsigned long int **)(ParameterEntry->Pointer)))[j]);
               break;
            case FLOAT:
               fprintf(OutputFile, "%s[%lu] %e\n",
                       ParameterEntry->Parameter, j,
                       (*((float **)(ParameterEntry->Pointer)))[j]);
               break;
            case DOUBLE:
               fprintf(OutputFile, "%s[%lu] %e\n",
                       ParameterEntry->Parameter, j,
                       (*((double **)(ParameterEntry->Pointer)))[j]);
               break;
            case CHAR:
               fprintf(OutputFile, "%s[%lu] %c\n",
                       ParameterEntry->Parameter, j,
                       (*((char **)(ParameterEntry->Pointer)))[j]);
               break;
            case STRING:
               fprintf(OutputFile, "%s[%lu] %s\n",
                       ParameterEntry->Parameter, j,
                       (((char **)(ParameterEntry->Pointer)))[j]);
               break;
            default:
               fprintf(OutputFile, "%s: %i: ERROR: Unknown type %i\n",
                       __FILE__,__LINE__,ParameterEntry->Type);
               return EXIT_FAILURE;
            }
         } /* loop over j < NArrayElements */
      } else {
         /* Regular Parameters = value entry */
         switch(ParameterEntry->Type) {
         case INTEGER:
            fprintf(OutputFile, "%s %i\n",
                    ParameterEntry->Parameter,
                    *((int *)ParameterEntry->Pointer));
            break;
         case LONG_INTEGER:
            fprintf(OutputFile, "%s %li\n",
                    ParameterEntry->Parameter,
                    *((long int *)ParameterEntry->Pointer));
            break;
         case UNSIGNED_INTEGER:
            fprintf(OutputFile, "%s %u\n",
                    ParameterEntry->Parameter,
                    *((unsigned int *)ParameterEntry->Pointer));
            break;
         case UNSIGNED_LONG_INTEGER:
            fprintf(OutputFile, "%s %lu\n",
                    ParameterEntry->Parameter,
                    *((long int *)ParameterEntry->Pointer));
            break;
         case FLOAT:
            fprintf(OutputFile, "%s %e\n",
                    ParameterEntry->Parameter,
                    *((float *)ParameterEntry->Pointer));
            break;
         case DOUBLE:
            fprintf(OutputFile, "%s %e\n",
                    ParameterEntry->Parameter,
                    *((double *)ParameterEntry->Pointer));
            break;
         case STRING:
            fprintf(OutputFile, "%s %s\n",
                    ParameterEntry->Parameter,
                    (char *)(ParameterEntry->Pointer));
            break;
         default:
            fprintf(OutputFile, "%s: %i: ERROR: Unknown type %i\n",
                    __FILE__,__LINE__,ParameterEntry->Type);
            return EXIT_FAILURE;
         }
      } /* End of if IsBoolean, elseif IsArray, else tree */
   } /* End of loop over all parameters */
   fclose(OutputFile);
   return EXIT_SUCCESS;
}

void GameParameters::ensureValidity() const {
   ENSURE(type() == GAMEPARAMETERS, engine);
   ENSURE(MinRoll < MaxRoll, engine);
   ENSURE(EncryptionKey.length() > 0, engine);
}