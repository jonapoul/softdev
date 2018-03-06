#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "Game/GameObject.h"

class GameEngine;
class SquadMember;

class Skill : public GameObject {
public:
   Skill(GameEngine * const e,
         SquadMember * const s);

   virtual void checkValidity() const;

private:
   GameEngine * engine;
   SquadMember * squadmember;
   std::string name;
   std::string description;
};

#endif
