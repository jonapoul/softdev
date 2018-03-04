#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

class GameEngine;
class Player;
class Captain;
class Hierophant;
class SquadMember;

class Squad {
public:
   Squad(GameEngine * const e,
         Player * const p,
         char const * const filename,
         bool * const squadFileIsValid);

private:
   GameEngine * engine;
   Player * player;
   Captain * captain;
   Hierophant * hierophant;
   std::vector<SquadMember *> squadMembers;
   bool isPublic;
};

#endif