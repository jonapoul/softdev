#include <iostream>
#include <string>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "Game/GameEngine.h"
#include "Game/GameParameters.h"
#include "Game/Die.h"
#include "Game/Player.h"
#include "UI/GameWindow.h"
#include "functions.h"

GameEngine::GameEngine(GameWindow * const gw)
      : window(gw) {
   if (!gw) {
      informationMessage("GameEngine->window is a nullptr, using std::cout for output");
   }

   bool paramFileIsValid = true;
   this->parameters = new GameParameters("data/parameters.input", &paramFileIsValid);
   if (!paramFileIsValid) {
      delete this->parameters;
      criticalMessage("Parameter file is invalid");
   }

   this->die = new Die(parameters->MinRoll, parameters->MaxRoll);
   
   initialisePlayers();
}

GameEngine::~GameEngine() {
   delete this->parameters;
   delete this->die;
   for (auto player : this->players) {
      delete player;
   }
}

void GameEngine::criticalMessage(char const * const message) {
   if (window) {
      window->criticalMessage(message);
   } else {
      std::cout << "CRITICAL:    " << message << std::endl;
      exit(EXIT_FAILURE);
   }
}

void GameEngine::warningMessage(char const * const message) {
   if (window) {
      window->warningMessage(message);
   } else {
      std::cout << "WARNING:     " << message << std::endl;
   }
}

void GameEngine::informationMessage(char const * const message) {
   if (window) {
      window->informationMessage(message);
   } else {
      std::cout << "INFORMATION: " << message << std::endl;
   }
}

bool GameEngine::login(Player const * const player,
                       std::string const& plaintextPassword) {
   std::string const encryptedPassword = encrypt(plaintextPassword, parameters->EncryptionKey);
   return true;
}

void GameEngine::initialisePlayers() {
   /* Find all player files in the directory */
   fs::path playersDirectory = fs::path("data/players");
   std::vector<std::string> playerFiles;
   if (!fs::exists(playersDirectory)) {
      criticalMessage("Directory './data/players' doesn't exist!");
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
         char warningbuf[256];
         snprintf(warningbuf, 256, "Player %zu has an invalid player file at '%s'",
                  i, playerFiles[i].c_str());
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