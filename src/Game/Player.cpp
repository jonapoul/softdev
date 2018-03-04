#include <string>
#include <cstring>

#include "Game/Player.h"
#include "Game/GameEngine.h"
#include "Game/Squad.h"
#include "functions.h"

extern "C" {
#include "PF.h"
}

Player::Player(GameEngine * const e,
               std::string const& filename,
               bool * const playerFileIsValid) 
      : engine(e), loginStatus(false) {
   char buf[256];
   snprintf(buf, 256, "Building player from file %s", filename.c_str());
   engine->informationMessage(buf);

   /* Defaults */
   this->username = "";
   this->password = "";
   char tempUsername[MAX_PARAMETER_NAME_LENGTH];
   char tempPassword[MAX_PARAMETER_NAME_LENGTH];
   size_t NumSquads;
   char ** SquadFiles = nullptr;

   /* Allocate memory for temporary parameter reading structs */
   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nPlayerParameters];
   for (size_t i = 0; i < nPlayerParameters; i++) {
      ParamEntries[i].IsBoolean = 0;
      ParamEntries[i].IsArray   = 0;
   }

   strncpy(ParamEntries[iUsername].Parameter, "Username", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iUsername].Type    = STRING;
   ParamEntries[iUsername].Pointer = tempUsername;
   strncpy(ParamEntries[iPassword].Parameter, "Password", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iPassword].Type    = STRING;
   ParamEntries[iPassword].Pointer = tempPassword;
   strncpy(ParamEntries[iSquadFiles].Parameter, "SquadFiles", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadFiles].Type           = STRING;
   ParamEntries[iSquadFiles].Pointer        = SquadFiles;
   ParamEntries[iSquadFiles].IsArray        = 1;
   ParamEntries[iSquadFiles].NArrayElements = &NumSquads;

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(filename.c_str(), "r")) == NULL) {
      char warningbuf[256];
      snprintf(warningbuf, 256, "Failed to load player file '%s'", filename.c_str());
      engine->warningMessage(warningbuf);
      *playerFileIsValid = false;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nPlayerParameters) != EXIT_SUCCESS) {
      char warningbuf[256];
      snprintf(warningbuf, 256, "PF_ReadParameterFile() failed for player file '%s'",
               filename.c_str());
      engine->warningMessage(warningbuf);
      *playerFileIsValid = false;
   }

   SquadFiles = (char**)(ParamEntries[iSquadFiles].Pointer);

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);

   /* Back out if the file is invalid for whatever reason */
   if ( *playerFileIsValid == false ) {
      return;
   }

   this->username = std::string(tempUsername);
   this->password = std::string(password);
   this->squads.resize(NumSquads, nullptr);

   /* Create the Squad objects and check for validity */
   for (size_t i = 0; i < NumSquads; i++) {
      bool squadFileIsValid = true;
      squads[i] = new Squad(engine, this, SquadFiles[i], &squadFileIsValid);
      if ( !squadFileIsValid ) {
         char warningbuf[256];
         snprintf(warningbuf, 256, "Player '%s' has an invalid squad file at '%s'",
                  username.c_str(), SquadFiles[i]);
         engine->warningMessage(warningbuf);
         delete squads[i];
         squads[i] = nullptr;
      }
      free(SquadFiles[i]);
   }
   free(SquadFiles);
   /* Remove any null pointers from the array */
   for (int i = (int)squads.size()-1; i >= 0; i--) {
      if (squads[i] == nullptr) {
         squads.erase(squads.begin() + i);
      }
   }
}

Player::~Player() {
   for (auto& squad : this->squads) {
      delete squad;
   }
}

void Player::deleteSquad(size_t const indexToDelete) {
   if (indexToDelete >= numSquads()) {
      char warningbuf[256];
      snprintf(warningbuf, 256, "User '%s' tried deleting squad index out of "
               "range in %s: indexToDelete = %zu, nSquads = %zu",
               username.c_str(), __FILE__, indexToDelete, numSquads());
      engine->warningMessage(warningbuf);
      return;
   }
   /* clear the allocated memory */
   delete squads[indexToDelete];
   /* remove the null pointer from the array */
   squads.erase(squads.begin() + indexToDelete);
}

void Player::addSquad(Squad * const squad) {
   if (squad) {
      this->squads.push_back(squad);
   } else {
      char warningbuf[256];
      snprintf(warningbuf, 256, "Tried adding null Squad pointer to player '%s'",
               this->username.c_str());
      engine->warningMessage(warningbuf);
   }
}

size_t Player::numSquads() const {
   return this->squads.size();
}