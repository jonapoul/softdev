#include <vector>
#include <algorithm>

#include "TestSuite.h"
#include "Game/GameEngine.h"
#include "Game/GameObject.h"
#include "Game/GameParameters.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/SquadMember.h"
#include "Game/Captain.h"
#include "Game/Hierophant.h"
#include "Global.h"

/* I realise global functions aren't a good idea, but this is just for the tests
   not the actual product */
GameEngine * engine;
InputOption errorOption;
std::vector<InputOption> options;

/* Testing functions */
void help();
void printAllObjects();
void createSquad();
void deleteSquad();
void createPlayer();
void deletePlayer();
void reloadEngine();
void checkEverything();

/* auxiliary testing functions */
Player * choosePlayer();

TestSuite::TestSuite(GameEngine * e) {
   engine = e;
   errorOption = { 'x', "ERROR", nullptr };
   options = {
      { 'h', "Help",                &help },
      { 'q', "Quit",                nullptr }, /* Dont need a function for this */
      { '1', "Print all objects",   &printAllObjects },
      { '2', "Create new squad",    &createSquad },
      { '3', "Delete squad",        &deleteSquad },
      { '4', "Create new player",   &createPlayer },
      { '5', "Delete player",       &deletePlayer },
      { '6', "Reload Engine",       &reloadEngine },
      { '7', "Check everything",    &checkEverything },
   };
}

/* Take inputs from the user and pick the correct function using InputOptions.
   This acts as a "main menu" to the tests */
void TestSuite::run() {
   /* Print all help options on startup */
   help();

   /* Ask for inputs */
   while (true) {
      printf("Enter test option (h = help):\n");
      std::string key;
      std::cin >> key;
      if (tolower(key[0]) == 'q') return;

      /* match the inputted character to a function */
      InputOption opt = TestSuite::matchInputOption(key[0]);
      if (opt.desc == "ERROR") {
         printf("Invalid input\n\n");
      } else {
         /* Run the test function */
         opt.func();
         printf("\n");
      }
   }
}

InputOption TestSuite::matchInputOption(char const key) {
   for (auto opt : options) {
      if (tolower(key) == opt.key) {
         return opt;
      }
   }
   /* if no match, return a pseudo-error */
   return errorOption;
}

/* print out all test functions and the required key inputs */
void help() {
   printf("All test options:\n");
   for (auto o : options) {
      printf("    %c = %s\n", o.key, o.desc.c_str());
   }
}

/* Print a great big list of every object in memory that was derived from
   GameObject. That's every class in the 'inc/Game/' directory. You can also
   use this to print detailed into about every one of these objects and see
   where various pointers lead to, which objects 'own' others, etc. It's
   surprisingly useful for debugging the control flow. There's almost certainly
   more efficient ways of implementing the same kind of system though */
void printAllObjects() {
   GameObject::printAllObjects();
}

/* Create a new squad object via std::cin input and match it to a Player of the
   user's choice. I've skipped the process of initialising SkillTrees for the
   sake of this test function, but you can follow the templates in
   'data/skilltrees' and 'data/squad' to see how to add your own skill trees to
   the game and read them in via libPF */
void createSquad() {
   /* This is the player who gets the new squad attached */
   Player * player = choosePlayer();
   if (player == nullptr) return;

   /* Read in some basic info about the squad from terminal */
   Squad * squad = nullptr;
   while (true) {
      squad = new Squad(engine, player);
      squad->filename = "terminal input";
      squad->credits = engine->parameters->StartingCredits;

      printf("Should the squad be publicly visible? (y/n) (q to back out):\n");
      input = "";
      std::cin >> input;
      if (tolower(input[0]) == 'q') {
         squad->deallocate();
         return;
      }
      squad->isPublic   = (tolower(input[0]) == 'y') ? true : false;
      squad->captain    = new Captain(squad);
      squad->hierophant = new Hierophant(squad);

      printf("How many regular squad members? (%d credits each) (q to back out):\n",
             engine->parameters->BaseCost);
      input = "";
      std::cin >> input;
      if (tolower(input[0]) == 'q') {
         squad->deallocate();
         return;
      } else if (std::all_of(input.begin(), input.end(), ::isdigit) == false) {
         printf("Needs to be an integer!\n\n");
         squad->deallocate();
         continue;
      } else if (std::stoi(input)*engine->parameters->BaseCost > squad->credits) {
         printf("Costs too much! You're trying to buy %d credits worth but you "
                "have %d credits\n\n",
                std::stoi(input)*engine->parameters->BaseCost, squad->credits);
         squad->deallocate();
         continue;
      }
      squad->squadMembers.resize( std::stoi(input), nullptr );
      for (auto& member : squad->squadMembers) {
         member = new SquadMember(squad);
      }
      break;
   } /* end of while(true) */

   /* Attach the completed squad to the player's array */
   player->squads.push_back(squad);
   printf("\nSquad with ID = %lu has been successfully created. I've not added\n"
          "any skilltrees to these tests though, because that would take\n"
          "absolutely ages and it's much easier to do via parameter files in\n"
          "the directory './data/squads'.\n", squad->ID());
}

void deleteSquad() {
   /* Choose a player to delete a squad from */
   Player * player = choosePlayer();
   if (player == nullptr) return;
   if (player->numSquads() == 0) {
      printf("That player doesn't have any squads!\n");
      return;
   }

   printf("Existing squads owned by that player:\n");
   for (Squad * s : player->squads) {
      printf("    ID = %lu, nSquadMembers = %lu, Filename = '%s'\n",
             s->ID(), s->squadMembers.size(), s->filename.c_str());
   }
   while (true) {
      printf("Enter the ID of a squad (q to go back):\n");
      std::string input;
      std::cin >> input;
      if (tolower(input[0]) == 'q') return;
      if (std::all_of(input.begin(), input.end(), ::isdigit) == false) {
         printf("Try an integer!\n");
         continue;
      }
      size_t id = std::stoi(input);
      for (size_t i = 0; i < player->numSquads(); i++) {
         if (id == player->squads[i]->ID()) {
            player->squads[i]->deallocate();
            player->squads.erase(player->squads.begin() + i);
            printf("Deleted squad with ID = %lu from player '%s'!\n",
                   id, player->username.c_str());
            return;
         }
      }
      printf("That ID didn't match a squad, try again.\n");
   } /* end while loop */
}

void createPlayer() {
   printf("Creating a new Player:\n");
   Player * player = new Player(engine);
   engine->players.push_back(player);
   player->filename = "terminal input";

   printf("Enter username:\n");
   std::cin >> player->username;

   printf("Enter password:\n");
   std::cin >> player->password;

   player->print();
   printf("\nPlayer created! Try printing all objects to see it on the list.\n");
}

void deletePlayer() {
   printf("Existing players:\n");
   for (Player * player : engine->players) {
      printf("    ID = %lu, nSquads = %lu, Username = '%s'\n",
             player->ID(), player->numSquads(), player->username.c_str());
   }
   while (true) {
      printf("Enter the ID of the player you want to delete (q to go back):\n");
      std::string input;
      std::cin >> input;
      if (tolower(input[0]) == 'q') return;
      if (std::all_of(input.begin(), input.end(), ::isdigit) == false) {
         printf("Try an integer!\n");
         continue;
      }
      size_t id = std::stoi(input);
      for (size_t i = 0; i < engine->players.size(); i++) {
         if (id == engine->players[i]->ID()) {
            engine->players[i]->deallocate();
            engine->players.erase(engine->players.begin() + i);
            printf("Deleted player with ID = %lu!\n", id);
            return;
         }
      }
      printf("That ID didn't match a player, try again.\n");
   }
}

void reloadEngine() {
   printf("Deleting existing GameEngine ... ");
   engine->deallocate();
   printf("done!\n");
   printf("Creating new GameEngine ... ");
   engine = new GameEngine();
   engine->init();
   printf("done!\n");
   printf("You can do this to reload parameter/squad/skilltree/player files in\n"
          "the ./data/ directory without having to restart the whole program.\n");
}

void checkEverything() {
   printf("Validating every game object:\n");
   GameObject::ensureEverythingIsValid();
   printf("If nothing was printed, every check passed!\n");
   printf("This test goes through every GameObject-derived object in the array\n"
          "GameObject::all_objects and runs ensureValidity() on each. Have a\n"
          "look through each class' implementation to see what's being checked\n"
          "at each step.\n");
}

Player * choosePlayer() {
   printf("Existing players:\n");
   for (Player * p : engine->players) {
      printf("    ID = %lu, nSquads = %lu, Username = '%s'\n",
             p->ID(), p->numSquads(), p->username.c_str());
   }
   while (true) {
      printf("Enter the ID of a player (q to go back):\n");
      std::string input;
      std::cin >> input;
      if (tolower(input[0]) == 'q') return nullptr;
      if (std::all_of(input.begin(), input.end(), ::isdigit) == false) {
         printf("Try an integer!\n");
         continue;
      }
      size_t id = std::stoi(input);
      for (size_t i = 0; i < engine->players.size(); i++) {
         if (id == engine->players[i]->ID()) {
            return engine->players[i];
         }
      }
      printf("That ID didn't match a player, try again.\n");
   } /* end while loop */
}