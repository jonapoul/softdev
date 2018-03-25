#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Game/GameObject.h"

class Squad;
class GameEngine;

class Player : public GameObject {
public:
   Player(GameEngine * const e);
   ~Player();

   /* Used for parameter reading in init() */
   enum {
      iUsername,
      iPassword,
      iSquadFiles,
      nPlayerParameters
   };

   bool init(std::string const& file);

   void deleteSquad(size_t const indexToDelete);
   void addSquad(Squad * const squad);
   size_t numSquads() const;

   virtual void ensureValidity() const;
   virtual void print() const;

   GameEngine * engine = nullptr;
   std::string username;
   std::string password;
   std::vector<Squad *> squads;
   bool loginStatus; /* TODO: change this to an enum? Probably not necessary if no networking */
   std::string filename;
};

#endif