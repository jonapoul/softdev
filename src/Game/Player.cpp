#include <string>
#include <cstring>

#include "Game/Player.h"
#include "Game/GameEngine.h"
#include "Game/Squad.h"
#include "Global.h"

extern "C" {
#include "PF.h"
}

Player::Player(GameEngine * const e,
               std::string const& file,
               bool * const playerFileIsValid) 
      : GameObject(PLAYER), engine(e), loginStatus(false), filename(file) {

   /* Defaults */
   char tempUsername[MAX_LINE_LENGTH];
   char tempPassword[MAX_LINE_LENGTH];
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
   ParamEntries[iSquadFiles].Pointer        = &SquadFiles;
   ParamEntries[iSquadFiles].IsArray        = 1;
   ParamEntries[iSquadFiles].NArrayElements = &NumSquads;

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(filename.c_str(), "r")) == NULL) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed to load player file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      *playerFileIsValid = false;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nPlayerParameters) != EXIT_SUCCESS) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for player file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      *playerFileIsValid = false;
   }

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
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Player '%s' has an invalid squad file at '%s'",
                  __FUNCTION__, username.c_str(), SquadFiles[i]);
         engine->warningMessage(warningbuf);
         squads[i]->deallocate();
         /* Mark it as to-be-removed */
         squads[i] = nullptr;
      }
   }
   PF_FreeStringArray(SquadFiles, NumSquads);
   /* Remove any null pointers from the array */
   for (int i = (int)squads.size()-1; i >= 0; i--) {
      if (squads[i] == nullptr) {
         squads.erase(squads.begin() + i);
      }
   }
}

Player::~Player() {
   for (auto squad : this->squads) {
      squad->deallocate();
   }
}

void Player::deleteSquad(size_t const indexToDelete) {
   if (indexToDelete >= numSquads()) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH, 
               "%s: User '%s' tried deleting squad index out of range. "
               "[indexToDelete = %zu, nSquads = %zu]",
               __FUNCTION__, username.c_str(), indexToDelete, numSquads());
      engine->warningMessage(warningbuf);
      return;
   }
   /* clear the allocated memory */
   squads[indexToDelete]->deallocate();
   /* remove the deleted pointer from the array */
   squads.erase(squads.begin() + indexToDelete);
}

void Player::addSquad(Squad * const squad) {
   if (squad) {
      this->squads.push_back(squad);
   } else {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: Tried adding null Squad pointer to player '%s'",
               __FUNCTION__, username.c_str());
      engine->warningMessage(warningbuf);
   }
}

size_t Player::numSquads() const {
   return this->squads.size();
}

void Player::checkValidity() const {
   CHECK(type() == PLAYER, engine);
   CHECK(username.length() > 0, engine);
   CHECK(password.length() > 0, engine);
   CHECK(loginStatus == true, engine);
}