#include <string>
#include <cstring>

#include "Game/Player.h"
#include "Game/GameEngine.h"
#include "Game/Squad.h"
#include "Global.h"

extern "C" {
#include "PF.h"
}

Player::Player(GameEngine * const e)
      : GameObject(PLAYER), engine(e), loginStatus(false) { }

bool Player::init(std::string const& file) {
   this->filename = file;
   bool playerFileIsValid = true;

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
      playerFileIsValid = false;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nPlayerParameters) != EXIT_SUCCESS) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for player file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      playerFileIsValid = false;
   }

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);

   /* Back out if the file is invalid for whatever reason */
   if (!playerFileIsValid) {
      return false;
   }

   this->username = std::string(tempUsername);
   this->password = std::string(tempPassword);

   /* Create the Squad objects based on the input files, then check that they're
      legit before adding them to the squads array */
   for (size_t i = 0; i < NumSquads; i++) {
      Squad * s = new Squad(engine, this);
      bool const squadFileIsValid = s->init(SquadFiles[i]);
      if ( !squadFileIsValid ) {
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Player '%s' has an invalid squad file at '%s'",
                  __FUNCTION__, username.c_str(), SquadFiles[i]);
         engine->warningMessage(warningbuf);
         s->deallocate();
      } else {
         this->squads.push_back(s);
      }
   }
   /* Clear array of malloc'ed strings */
   PF_FreeStringArray(SquadFiles, NumSquads);
   /* Success! */
   return true;
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
               "[indexToDelete = %lu, nSquads = %lu]",
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

/* ENSURE() macro defined in GameObject.h */
void Player::ensureValidity() const {
   ENSURE(type() == PLAYER,      engine);
   ENSURE(username.length() > 0, engine);
   ENSURE(password.length() > 0, engine);
   // ENSURE(loginStatus == true,   engine);
}

void Player::print() const {
   GameObject::print();
   printf("Player:\n");
   printf("   engine      = %p, ID = %lu\n", engine, engine->ID());
   printf("   username    = '%s'\n", username.c_str());
   printf("   password    = '%s'\n", password.c_str());
   printf("   squads      = [ ");
   for (auto s : squads) printf("%lu ", s->ID());
   printf("]\n");
   printf("   filename    = '%s'\n", filename.c_str());
   printf("   loginStatus = %d\n", loginStatus);
}