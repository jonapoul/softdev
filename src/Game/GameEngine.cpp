#include <iostream>
#include <string>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Game/GameEngine.h"
#include "Game/GameParameters.h"
#include "Game/Die.h"
#include "Game/Player.h"
#include "Game/Item.h"
#include "Game/Weapon.h"
#include "UI/GameWindow.h"
#include "Global.h"

extern "C" {
#include "PF.h"
}

GameEngine::GameEngine(GameWindow * const gw)
      : GameObject(GAMEENGINE), window(gw) {
   if (!gw) {
      informationMessage("GameWindow is a nullptr, using std::cout for output");
   }

   initGameParameters("data/parameters.input");
   initDie();
   initItems("data/items.input");
   initWeapons("data/weapons.input");
   initPlayers("data/players/");

   GameObject::printAllObjects();
}

GameEngine::~GameEngine() {
   parameters->deallocate();
   die->deallocate();
   for (auto player : this->players) {
      player->deallocate();
   }
}

std::vector<Item *> GameEngine::allItems() const {
   return this->all_valid_items;
}

std::vector<Weapon *> GameEngine::allWeapons() const {
   return this->all_valid_weapons;
}

void GameEngine::criticalMessage(char const * const message) const {
   if (window) {
      window->criticalMessage(message);
   } else {
      std::cout << "CRITICAL:    " << message << std::endl;
      exit(EXIT_FAILURE);
   }
}

void GameEngine::warningMessage(char const * const message) const {
   if (window) {
      window->warningMessage(message);
   } else {
      std::cout << "WARNING:     " << message << std::endl;
   }
}

void GameEngine::informationMessage(char const * const message) const {
   if (window) {
      window->informationMessage(message);
   } else {
      std::cout << "INFORMATION: " << message << std::endl;
   }
}

bool GameEngine::login(Player const * const player,
                       std::string const& plaintextPassword) {
   std::string encryptPassword = Global::encrypt(plaintextPassword, parameters->EncryptionKey);
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
      bool isValid = true;
      Item * item = new Item(this, this, ItemStrings[iItem], &isValid, InitialiseItem);
      if (isValid) {
         this->all_valid_items.push_back(item);
      } else {
         item->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid Item found in file '%s'",
                  __FUNCTION__, filename);
         warningMessage(warningbuf);
      }
   }

   /* Clean up */
   delete ParamEntry;
   fclose(ItemFile);
   PF_FreeStringArray(ItemStrings, NumItemStrings);
}

void GameEngine::initWeapons(char const * const filename) {

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
   this->players.resize(playerFiles.size(), nullptr);
   for (size_t i = 0; i < players.size(); i++) {
      /* Read the file in the Player() constructor */
      bool playerFileIsValid = true;
      players[i] = new Player(this, playerFiles[i], &playerFileIsValid);
      /* If it's not valid for whatever reason, clear the memory and let the user know */
      if ( !playerFileIsValid ) {
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Player %zu has an invalid player file '%s'",
                  __FUNCTION__, i, playerFiles[i].c_str());
         warningMessage(warningbuf);
         delete players[i];
         players[i] = nullptr;
      }
   }
   /* Remove any null pointers from the array */
   for (int i = (int)players.size()-1; i >= 0; i--) {
      if (players[i] == nullptr) {
         players.erase(players.begin() + i);
      }
   }
}

void GameEngine::checkValidity() const {
   CHECK(GameObject::numberOfType(GAMEENGINE) == 1, this);
}