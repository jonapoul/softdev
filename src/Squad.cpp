#include <cstring>

#include "Game/GameEngine.h"
#include "Game/GameParameters.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/Captain.h"
#include "Game/Hierophant.h"
#include "Game/SquadMember.h"
#include "Game/Item.h"
#include "Game/Weapon.h"

#include "Global.h"

extern "C" {
#include "PF.h"
}

Squad::Squad(GameEngine * const e,
             Player * const p)
      : GameObject(SQUAD), engine(e), player(p) {
   /* TODO: Create blank squad based on engine->parameters */
}

/* Build a squad and all its members, weapons/items, etc. by reading from a
   text file. */
bool Squad::init(char const * const file) {
   this->filename = file;
   bool squadFileIsValid = true;

   /* trim leading/trailing whitespace, then add the expected directory
      structure before the filename */
   Global::trim(&filename);
   filename = "data/squads/" + filename;

   /* Defaults */
   this->isPublic = true;
   this->credits  = engine->parameters->StartingCredits;

   /* Declare variables to store the libPF-read parameters in. We'll process
      them into Captain/Hierophant/SquadMember objects after */
   char username[MAX_LINE_LENGTH];
   char squadName[MAX_LINE_LENGTH];
   char isPublicStr[MAX_LINE_LENGTH];
   int     CaptainExperience    = 0;
   char    CaptainSpecialism[MAX_LINE_LENGTH];
   strncpy(CaptainSpecialism, "Unknown", MAX_LINE_LENGTH);
   char ** CaptainSkills        = nullptr;
   size_t  NumCaptainSkills     = 0;
   char ** CaptainItems         = nullptr;
   size_t  NumCaptainItems      = 0;
   char ** CaptainWeapons       = nullptr;
   size_t  NumCaptainWeapons    = 0;
   int *   CaptainStatBoosts    = nullptr;
   size_t  NumCaptainStatBoosts = 0;
   int     HierophantExperience    = 0;
   char    HierophantSpecialism[MAX_LINE_LENGTH];
   strncpy(HierophantSpecialism, "Unknown", MAX_LINE_LENGTH);
   char ** HierophantSkills        = nullptr;
   size_t  NumHierophantSkills     = 0;
   char ** HierophantItems         = nullptr;
   size_t  NumHierophantItems      = 0;
   char ** HierophantWeapons       = nullptr;
   size_t  NumHierophantWeapons    = 0;
   int *   HierophantStatBoosts    = nullptr;
   size_t  NumHierophantStatBoosts = 0;
   size_t  NumNormalSquadMembers = 0;
   char ** SquadWeapons          = nullptr;
   size_t  NumSquadWeapons       = 0;
   char ** SquadItems            = nullptr;
   size_t  NumSquadItems         = 0;

   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nSquadParameters];
   for (size_t i = 0; i < nSquadParameters; i++) {
      ParamEntries[i].IsBoolean = 0;
      ParamEntries[i].IsArray   = 1; /* Because most of these are arrays */
   }

   /* Register what we're looking for and what datatypes */
   strncpy(ParamEntries[iSquadUsername].Parameter, "Username", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadUsername].Type    = STRING;
   ParamEntries[iSquadUsername].IsArray = 0;
   ParamEntries[iSquadUsername].Pointer = &username;
   strncpy(ParamEntries[iSquadName].Parameter, "SquadName", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadName].Type    = STRING;
   ParamEntries[iSquadName].IsArray = 0;
   ParamEntries[iSquadName].Pointer = &squadName;
   strncpy(ParamEntries[iSquadIsPublic].Parameter, "IsPublic", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadIsPublic].Type    = STRING;
   ParamEntries[iSquadIsPublic].IsArray = 0;
   ParamEntries[iSquadIsPublic].Pointer = &isPublicStr;
   strncpy(ParamEntries[iSquadCredits].Parameter, "Credits", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadCredits].Type    = INTEGER;
   ParamEntries[iSquadCredits].IsArray = 0;
   ParamEntries[iSquadCredits].Pointer = &(this->credits);

   strncpy(ParamEntries[iCaptainExperience].Parameter, "CaptainExperience", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainExperience].Type    = INTEGER;
   ParamEntries[iCaptainExperience].IsArray = 0;
   ParamEntries[iCaptainExperience].Pointer = &CaptainExperience;
   strncpy(ParamEntries[iCaptainSpecialism].Parameter, "CaptainSpecialism", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainSpecialism].Type    = STRING;
   ParamEntries[iCaptainSpecialism].IsArray = 0;
   ParamEntries[iCaptainSpecialism].Pointer = CaptainSpecialism;
   strncpy(ParamEntries[iCaptainSkills].Parameter, "CaptainSkills", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainSkills].Type           = STRING;
   ParamEntries[iCaptainSkills].Pointer        = &CaptainSkills;
   ParamEntries[iCaptainSkills].NArrayElements = &NumCaptainSkills;
   strncpy(ParamEntries[iCaptainItems].Parameter, "CaptainItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainItems].Type           = STRING;
   ParamEntries[iCaptainItems].Pointer        = &CaptainItems;
   ParamEntries[iCaptainItems].NArrayElements = &NumCaptainItems;
   strncpy(ParamEntries[iCaptainWeapons].Parameter, "CaptainWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainWeapons].Type           = STRING;
   ParamEntries[iCaptainWeapons].Pointer        = &CaptainWeapons;
   ParamEntries[iCaptainWeapons].NArrayElements = &NumCaptainWeapons;
   strncpy(ParamEntries[iCaptainStatBoosts].Parameter, "CaptainStatBoosts", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iCaptainStatBoosts].Type           = INTEGER;
   ParamEntries[iCaptainStatBoosts].Pointer        = &CaptainStatBoosts;
   ParamEntries[iCaptainStatBoosts].NArrayElements = &NumCaptainStatBoosts;

   strncpy(ParamEntries[iHierophantExperience].Parameter, "HierophantExperience", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantExperience].Type    = INTEGER;
   ParamEntries[iHierophantExperience].IsArray = 0;
   ParamEntries[iHierophantExperience].Pointer = &HierophantExperience;
   strncpy(ParamEntries[iHierophantSpecialism].Parameter, "HierophantSpecialism", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantSpecialism].Type    = STRING;
   ParamEntries[iHierophantSpecialism].IsArray = 0;
   ParamEntries[iHierophantSpecialism].Pointer = HierophantSpecialism;
   strncpy(ParamEntries[iHierophantSkills].Parameter, "HierophantSkills", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantSkills].Type           = STRING;
   ParamEntries[iHierophantSkills].Pointer        = &HierophantSkills;
   ParamEntries[iHierophantSkills].NArrayElements = &NumHierophantSkills;
   strncpy(ParamEntries[iHierophantItems].Parameter, "HierophantItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantItems].Type           = STRING;
   ParamEntries[iHierophantItems].Pointer        = &HierophantItems;
   ParamEntries[iHierophantItems].NArrayElements = &NumHierophantItems;
   strncpy(ParamEntries[iHierophantWeapons].Parameter, "HierophantWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantWeapons].Type           = STRING;
   ParamEntries[iHierophantWeapons].Pointer        = &HierophantWeapons;
   ParamEntries[iHierophantWeapons].NArrayElements = &NumHierophantWeapons;
   strncpy(ParamEntries[iHierophantStatBoosts].Parameter, "HierophantStatBoosts", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iHierophantStatBoosts].Type           = INTEGER;
   ParamEntries[iHierophantStatBoosts].Pointer        = &HierophantStatBoosts;
   ParamEntries[iHierophantStatBoosts].NArrayElements = &NumHierophantStatBoosts;

   strncpy(ParamEntries[iNumNormalSquadMembers].Parameter, "NumNormalSquadMembers", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iNumNormalSquadMembers].Type    = INTEGER;
   ParamEntries[iNumNormalSquadMembers].IsArray = 0;
   ParamEntries[iNumNormalSquadMembers].Pointer = &NumNormalSquadMembers;
   strncpy(ParamEntries[iSquadWeapons].Parameter, "SquadWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadWeapons].Type           = STRING;
   ParamEntries[iSquadWeapons].Pointer        = &SquadWeapons;
   ParamEntries[iSquadWeapons].NArrayElements = &NumSquadWeapons;
   strncpy(ParamEntries[iSquadItems].Parameter, "SquadItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[iSquadItems].Type           = STRING;
   ParamEntries[iSquadItems].Pointer        = &SquadItems;
   ParamEntries[iSquadItems].NArrayElements = &NumSquadItems;

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(filename.c_str(), "r")) == NULL) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed to load squad file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      squadFileIsValid = false;
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nSquadParameters) != EXIT_SUCCESS) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for squad file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      squadFileIsValid = false;
   }

   /* Check that the numbers of items/weapons isn't too much */
   GameParameters const * const params = engine->parameters;
   if (   NumCaptainItems + NumCaptainWeapons       > params->MaxCaptainItems
       || NumCaptainWeapons                         > params->MaxCaptainWeapons
       || NumHierophantItems + NumHierophantWeapons > params->MaxHierophantItems
       || NumHierophantWeapons                      > params->MaxHierophantWeapons) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: Too many weapons/items on Hierophant/Captain for squad file '%s'",
               __FUNCTION__, filename.c_str());
      engine->warningMessage(warningbuf);
      squadFileIsValid = false;
   }

   /* Clean up parameter-reading objects */
   delete[] ParamEntries;
   fclose(ParamFile);

   /* If everything's ok so far, pass the string arrays to be converted into
      squad members, captain and hierophant */
   if (squadFileIsValid) {
      this->isPublic = (std::string(isPublicStr) == "true") ? true : false;
      this->squadMembers.resize(NumNormalSquadMembers, nullptr);
      for (auto& member : squadMembers) {
         member = new SquadMember(this);
      }

      this->captain = new Captain(this);
      this->captain->initSkills (CaptainSkills,  NumCaptainSkills, CaptainSpecialism);
      this->captain->initItems  (CaptainItems,   NumCaptainItems);
      this->captain->initWeapons(CaptainWeapons, NumCaptainWeapons);
      this->captain->updateStats();

      this->hierophant = new Hierophant(this);
      this->hierophant->initSkills (HierophantSkills,  NumHierophantSkills, HierophantSpecialism);
      this->hierophant->initItems  (HierophantItems,   NumHierophantItems);
      this->hierophant->initWeapons(HierophantWeapons, NumHierophantWeapons);
      this->hierophant->updateStats();

      this->initItems  (SquadItems,   NumSquadItems);
      this->initWeapons(SquadWeapons, NumSquadWeapons);
   }

   /* Deallocate all the various arrays */
   PF_FreeStringArray(CaptainSkills,     NumCaptainSkills);
   PF_FreeStringArray(CaptainItems,      NumCaptainItems);
   PF_FreeStringArray(CaptainWeapons,    NumCaptainWeapons);
   PF_FreeStringArray(HierophantSkills,  NumHierophantSkills);
   PF_FreeStringArray(HierophantItems,   NumHierophantItems);
   PF_FreeStringArray(HierophantWeapons, NumHierophantWeapons);
   PF_FreeStringArray(SquadItems,        NumSquadItems);
   PF_FreeStringArray(SquadWeapons,      NumSquadWeapons);
   free(CaptainStatBoosts);
   free(HierophantStatBoosts);

   return squadFileIsValid;
}

Squad::~Squad() {
   /* TODO: Prompt the user to save to file? */
   for (auto member : this->squadMembers) {
      member->deallocate();
   }
   captain->deallocate();
   hierophant->deallocate();
   for (auto item : this->items) {
      item->deallocate();
   }
   for (auto weapon : this->weapons) {
      weapon->deallocate();
   }
}

void Squad::initItems(char ** itemsStr,
                      size_t const nItems) {
   for (size_t iItem = 0; iItem < nItems; iItem++) {
      Item * item = new Item(this, engine);
      bool const itemIsValid = item->init(itemsStr[iItem]);
      if (!itemIsValid) {
         item->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid item string '%s'",
                  __FUNCTION__, itemsStr[iItem]);
         engine->warningMessage(warningbuf);
      } else {
         this->items.push_back(item);
      }
   }
}

void Squad::initWeapons(char ** weaponsStr,
                        size_t const nWeapons) {
   for (size_t iWeapon = 0; iWeapon < nWeapons; iWeapon++) {
      Weapon * weapon = new Weapon(this, engine);
      bool const weaponIsValid = weapon->init(weaponsStr[iWeapon]);
      if (!weaponIsValid) {
         weapon->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid weapon string '%s'",
                  __FUNCTION__, weaponsStr[iWeapon]);
         engine->warningMessage(warningbuf);
      } else {
         this->weapons.push_back(weapon);
      }
   }}

void Squad::ensureValidity() const {
   ENSURE(type() == SQUAD, engine);
   ENSURE(credits >= 0,    engine);
}