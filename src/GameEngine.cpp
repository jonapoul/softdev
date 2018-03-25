#include <iostream>
#include <string>
#include <cstring>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Game/GameEngine.h"
#include "Game/GameParameters.h"
#include "Game/Die.h"
#include "Game/Player.h"
#include "Game/Item.h"
#include "Game/Weapon.h"
#include "Game/SkillTree.h"
#include "Global.h"

#ifdef ENABLE_QT_UI
# include "UI/GameWindow.h"
#endif

extern "C" {
#include "PF.h"
}

#ifdef ENABLE_QT_UI
GameEngine::GameEngine(GameWindow * const gw)
      : GameObject(GAMEENGINE), window(gw) {
   if (gw == nullptr) {
      informationMessage("GameWindow is a nullptr, using std::cout for output");
   }
}
#else
GameEngine::GameEngine()
      : GameObject(GAMEENGINE) { }
#endif

GameEngine::~GameEngine() {
   die->deallocate();
   parameters->deallocate();
   for (auto item : this->all_valid_items) {
      item->deallocate();
   }
   for (auto weapon : this->all_valid_weapons) {
      weapon->deallocate();
   }
   for (auto skilltree : this->all_valid_skilltrees) {
      skilltree->deallocate();
   }
   for (auto player : this->players) {
      player->deallocate();
   }
}

void GameEngine::init() {
   initGameParameters("data/parameters.input");
   initDie();
   initItems("data/items.input");
   initWeapons("data/weapons.input");
   initSkillTrees("data/skilltrees/");
   initPlayers("data/players/");
}

std::vector<Item *> GameEngine::allItems() const {
   return this->all_valid_items;
}

std::vector<Weapon *> GameEngine::allWeapons() const {
   return this->all_valid_weapons;
}

std::vector<SkillTree *> GameEngine::allSkillTrees() const {
   return this->all_valid_skilltrees;
}


void GameEngine::criticalMessage(char const * const message) const {
#ifdef ENABLE_QT_UI
   if (window) {
      window->criticalMessage(message);
   } else {
      std::cout << "CRITICAL:    " << message << std::endl;
      exit(EXIT_FAILURE);
   }
#else
   std::cout << "CRITICAL:    " << message << std::endl;
   exit(EXIT_FAILURE);
#endif
}

void GameEngine::warningMessage(char const * const message) const {
#ifdef ENABLE_QT_UI
   if (window) {
      window->warningMessage(message);
   } else {
      std::cout << "WARNING:     " << message << std::endl;
   }
#else
   std::cout << "WARNING:     " << message << std::endl;
#endif
}

void GameEngine::informationMessage(char const * const message) const {
#ifdef ENABLE_QT_UI
   if (window) {
      window->informationMessage(message);
   } else {
      std::cout << "INFORMATION: " << message << std::endl;
   }
#else
   std::cout << "INFORMATION: " << message << std::endl;
#endif
}

bool GameEngine::login(Player const * const player,
                       std::string const& password) {
   std::string encrypted = Global::encrypt(password, parameters->EncryptionKey);

   /* Something like this, but its not really important for the sake of a
      prototype */
   // bool passwordIsValid = sendEncryptedPasswordToServer(encrypted);
   // if (passwordIsValid) {
   //    player->loginStatus = true;
   //    return true;
   // } else {
   //    return false;
   // }

   return true;
}

void GameEngine::initGameParameters(char const * const filename) {
   bool isValid = true;
   this->parameters = new GameParameters(this, filename, &isValid);
   if (!isValid) {
      this->parameters->deallocate();
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed reading parameter file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
   }
}

void GameEngine::initDie() {
   this->die = new Die(parameters->MinRoll, parameters->MaxRoll, this);
}

void GameEngine::initItems(char const * const filename) {
   char ** ItemStrings    = nullptr;
   size_t  NumItemStrings = 0;

   PF_ParameterEntry * ParamEntry = new PF_ParameterEntry;
   strncpy(ParamEntry->Parameter, "AllItems", MAX_PARAMETER_NAME_LENGTH);
   ParamEntry->Type           = STRING;
   ParamEntry->IsArray        = 1;
   ParamEntry->IsBoolean      = 0;
   ParamEntry->Pointer        = &ItemStrings;
   ParamEntry->NArrayElements = &NumItemStrings;

   /* Open the file */
   FILE * ItemFile = fopen(filename, "r");
   if (ItemFile == NULL) {
      delete ParamEntry;
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Invalid items file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ItemFile, ParamEntry, 1) != EXIT_SUCCESS) {
      delete ParamEntry;
      PF_FreeStringArray(ItemStrings, NumItemStrings);
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for item file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* create our valid Item objects */
   for (size_t iItem = 0; iItem < NumItemStrings; iItem++) {
      Item * item = new Item(this, this);
      bool const itemIsValid = item->initFromEngine(ItemStrings[iItem]);
      if (!itemIsValid) {
         item->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid Item found in file '%s'",
                  __FUNCTION__, filename);
         warningMessage(warningbuf);
      } else {
         this->all_valid_items.push_back(item);
      }
   }

   /* Clean up */
   delete ParamEntry;
   fclose(ItemFile);
   PF_FreeStringArray(ItemStrings, NumItemStrings);
}

void GameEngine::initWeapons(char const * const filename) {
   char ** WeaponStrings    = nullptr;
   size_t  NumWeaponStrings = 0;

   PF_ParameterEntry * ParamEntry = new PF_ParameterEntry;
   strncpy(ParamEntry->Parameter, "AllWeapons", MAX_PARAMETER_NAME_LENGTH);
   ParamEntry->Type           = STRING;
   ParamEntry->IsArray        = 1;
   ParamEntry->IsBoolean      = 0;
   ParamEntry->Pointer        = &WeaponStrings;
   ParamEntry->NArrayElements = &NumWeaponStrings;

   /* Open the file */
   FILE * WeaponFile = fopen(filename, "r");
   if (WeaponFile == NULL) {
      delete ParamEntry;
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Invalid weapons file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(WeaponFile, ParamEntry, 1) != EXIT_SUCCESS) {
      delete ParamEntry;
      PF_FreeStringArray(WeaponStrings, NumWeaponStrings);
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for weapon file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* create our valid Weapon objects */
   for (size_t iWeapon = 0; iWeapon < NumWeaponStrings; iWeapon++) {
      Weapon * weapon = new Weapon(this, this);
      bool const weaponIsValid = weapon->initFromEngine(WeaponStrings[iWeapon]);
      if (!weaponIsValid) {
         weapon->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid Weapon found in file '%s'",
                  __FUNCTION__, filename);
         warningMessage(warningbuf);
      } else {
         this->all_valid_weapons.push_back(weapon);
      }
   }

   /* Clean up */
   delete ParamEntry;
   fclose(WeaponFile);
   PF_FreeStringArray(WeaponStrings, NumWeaponStrings);
}

void GameEngine::initSkillTrees(char const * const directory) {
   std::string const cFile = std::string(directory) + "captain.skilltree";
   std::string const hFile = std::string(directory) + "hierophant.skilltree";
   readCaptainSkillTreeFile(cFile.c_str());
   readHierophantSkillTreeFile(hFile.c_str());
}

void GameEngine::initPlayers(char const * const directory) {
   /* Find all player files in the directory */
   fs::path playersDirectory = fs::path(directory);
   std::vector<std::string> playerFiles;
   if (!fs::exists(playersDirectory)) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Directory '%s' doesn't exist!",
               __FUNCTION__, directory);
      criticalMessage(criticalbuf);
   } else {
      for (auto& itr : fs::directory_iterator(playersDirectory)) {
         if (fs::is_regular_file(itr) && itr.path().extension() == ".player") {
            playerFiles.push_back(itr.path().string());
         }
      }
   }

   /* Allocate the space for each player's info */
   for (size_t i = 0; i < playerFiles.size(); i++) {
      /* Read the file in the Player() constructor */
      Player * p = new Player(this);
      bool const playerFileIsValid = p->init(playerFiles[i]);
      /* If the file has something wrong, clear the memory and let the user know */
      if ( !playerFileIsValid ) {
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Player %lu has an invalid player file '%s'",
                  __FUNCTION__, i, playerFiles[i].c_str());
         warningMessage(warningbuf);
         p->deallocate();
      } else {
         this->players.push_back(p);
      }
   }
}

void GameEngine::ensureValidity() const {
   ENSURE(type() == GAMEENGINE, this);
   ENSURE(GameObject::numberOfType(GAMEENGINE) == 1, this);
}

void GameEngine::print() const {
   GameObject::print();
   printf("GameEngine:\n");
#ifdef ENABLE_QT_UI
   printf("   GameWindow            = %p\n", window);
#endif
   printf("   Die                   = %p, ID = %lu\n", die, die->ID());
   printf("   Parameters            = %p, ID = %lu\n", parameters, parameters->ID());
   printf("   Players               = [ ");
   for (auto p : players) printf("%lu ", p->ID());
   printf("]\n");
   printf("   AllPossibleItems      = [ ");
   for (auto i : all_valid_items) printf("%lu ", i->ID());
   printf("]\n");
   printf("   AllPossibleWeapons    = [ ");
   for (auto w : all_valid_weapons) printf("%lu ", w->ID());
   printf("]\n");
   printf("   AllPossibleSkillTrees = [ ");
   for (auto st : all_valid_skilltrees) printf("%lu ", st->ID());
   printf("]\n");
}

void GameEngine::readCaptainSkillTreeFile(char const * const filename) {
   char **DemomanModifiers, **ScoutModifiers, **SoldierModifiers,
        **LeaderModifiers,  **HeavyModifiers, **EliteModifiers;
   size_t NumDemomanModifiers, NumScoutModifiers, NumSoldierModifiers,
          NumLeaderModifiers,  NumHeavyModifiers, NumEliteModifiers;
   size_t const nParameters = 6;
   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nParameters];
   for (size_t i = 0; i < nParameters; i++) {
      ParamEntries[i].Type      = STRING;
      ParamEntries[i].IsBoolean = 0;
      ParamEntries[i].IsArray   = 1;
   }

   strncpy(ParamEntries[0].Parameter, "Demoman", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[0].Pointer        = &DemomanModifiers;
   ParamEntries[0].NArrayElements = &NumDemomanModifiers;
   strncpy(ParamEntries[1].Parameter, "Scout", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[1].Pointer        = &ScoutModifiers;
   ParamEntries[1].NArrayElements = &NumScoutModifiers;
   strncpy(ParamEntries[2].Parameter, "Soldier", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[2].Pointer        = &SoldierModifiers;
   ParamEntries[2].NArrayElements = &NumSoldierModifiers;
   strncpy(ParamEntries[3].Parameter, "Leader", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[3].Pointer        = &LeaderModifiers;
   ParamEntries[3].NArrayElements = &NumLeaderModifiers;
   strncpy(ParamEntries[4].Parameter, "Heavy", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[4].Pointer        = &HeavyModifiers;
   ParamEntries[4].NArrayElements = &NumHeavyModifiers;
   strncpy(ParamEntries[5].Parameter, "Elite", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[5].Pointer        = &EliteModifiers;
   ParamEntries[5].NArrayElements = &NumEliteModifiers;

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(filename, "r")) == NULL) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed to load skill tree file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nParameters) != EXIT_SUCCESS) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for skill tree file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* check that no skill trees have been given anything other than two statboosts */
   for (size_t i = 0; i < nParameters; i++) {
      size_t const arraySize = *(ParamEntries[i].NArrayElements);
      if (arraySize != 2) {
         char criticalbuf[MAX_MESSAGE_LENGTH];
         snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
                  "%s: Skill Tree '%s' has been given %lu elements instead of 2",
                  __FUNCTION__, ParamEntries[i].Parameter, arraySize);
         criticalMessage(criticalbuf);
         /* QUIT */
      }
   }

   /* Build each Skill tree, only keep if it's valid */
   for (size_t i = 0; i < nParameters; i++) {
      SkillTree * tree = new SkillTree(this, this);
      char ** skillStrings = *((char***)ParamEntries[i].Pointer);
      int const specialism = (int)(i+1); /* see Captain::Specialism enum to translate i+1 */
      bool const isValid = tree->init(CAPTAIN, specialism, skillStrings);
      if (isValid) {
         this->all_valid_skilltrees.push_back(tree);
      } else {
         tree->deallocate();
      }
   }

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);
   PF_FreeStringArray(DemomanModifiers, NumDemomanModifiers);
   PF_FreeStringArray(ScoutModifiers,   NumScoutModifiers);
   PF_FreeStringArray(SoldierModifiers, NumSoldierModifiers);
   PF_FreeStringArray(LeaderModifiers,  NumLeaderModifiers);
   PF_FreeStringArray(HeavyModifiers,   NumHeavyModifiers);
   PF_FreeStringArray(EliteModifiers,   NumEliteModifiers);
}

void GameEngine::readHierophantSkillTreeFile(char const * const filename) {
   char **SpeakerModifiers, **PriestModifiers, **MedicModifiers, **SupportModifiers;
   size_t NumSpeakerModifiers, NumPriestModifiers, NumMedicModifiers, NumSupportModifiers;
   size_t const nParameters = 4;
   PF_ParameterEntry * ParamEntries = new PF_ParameterEntry[nParameters];
   for (size_t i = 0; i < nParameters; i++) {
      ParamEntries[i].Type      = STRING;
      ParamEntries[i].IsBoolean = 0;
      ParamEntries[i].IsArray   = 1;
   }

   strncpy(ParamEntries[0].Parameter, "Speaker", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[0].Pointer        = &SpeakerModifiers;
   ParamEntries[0].NArrayElements = &NumSpeakerModifiers;
   strncpy(ParamEntries[1].Parameter, "Priest", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[1].Pointer        = &PriestModifiers;
   ParamEntries[1].NArrayElements = &NumPriestModifiers;
   strncpy(ParamEntries[2].Parameter, "Medic", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[2].Pointer        = &MedicModifiers;
   ParamEntries[2].NArrayElements = &NumMedicModifiers;
   strncpy(ParamEntries[3].Parameter, "Support", MAX_PARAMETER_NAME_LENGTH);
   ParamEntries[3].Pointer        = &SupportModifiers;
   ParamEntries[3].NArrayElements = &NumSupportModifiers;

   /* Open Parameters file for reading */
   FILE * ParamFile;
   if ( (ParamFile = fopen(filename, "r")) == NULL) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed to load skill tree file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* Read the Parameters */
   if (PF_ReadParameterFile(ParamFile, ParamEntries, nParameters) != EXIT_SUCCESS) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: PF_ReadParameterFile() failed for skill tree file '%s'",
               __FUNCTION__, filename);
      criticalMessage(criticalbuf);
      /* QUIT */
   }

   /* check that no skill trees have been given anything other than two statboosts */
   for (size_t i = 0; i < nParameters; i++) {
      size_t const arraySize = *(ParamEntries[i].NArrayElements);
      if (arraySize != 2) {
         char criticalbuf[MAX_MESSAGE_LENGTH];
         snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
                  "%s: Skill Tree '%s' has been given %lu elements instead of 2",
                  __FUNCTION__, ParamEntries[i].Parameter, arraySize);
         criticalMessage(criticalbuf);
         /* QUIT */
      }
   }

   for (size_t i = 0; i < nParameters; i++) {
      /* nullptr in the constructor means it's not attached to a squad member */
      SkillTree * tree = new SkillTree(this, this);
      char ** skillStrings = *((char***)ParamEntries[i].Pointer);
      int const specialism = i+1; /* see HierohantSpecialism enum to translate i+1 */
      bool const isValid = tree->init(HIEROPHANT, specialism, skillStrings);
      if (isValid) {
         this->all_valid_skilltrees.push_back(tree);
      } else {
         tree->deallocate();
      }
   }

   /* Clean up */
   delete[] ParamEntries;
   fclose(ParamFile);
   PF_FreeStringArray(SpeakerModifiers, NumSpeakerModifiers);
   PF_FreeStringArray(PriestModifiers,  NumPriestModifiers);
   PF_FreeStringArray(MedicModifiers,   NumMedicModifiers);
   PF_FreeStringArray(SupportModifiers, NumSupportModifiers);
}
