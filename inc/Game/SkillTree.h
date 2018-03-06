#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <vector>
#include <string>

#include "Game/GameObject.h"

class GameEngine;
class SquadMember;
class Skill;

typedef enum {
   NoSkillTreeClass,
   HierophantSkillTreeClass,
   CaptainSkillTreeClass,
   NumSkillTreeClasses
} SkillTreeClass;

class SkillTree : public GameObject {
public:
   SkillTree(GameEngine * const e,
             SquadMember * const s);

   virtual void checkValidity() const;

private:
   GameEngine * engine;
   SquadMember * squadmember;

   std::string name;
   SkillTreeClass skillTreeClass;
   int specialism; /* Either HierophantSpecialism or CaptainSpecialism enum */
   std::vector<Skill *> skills;
};

#endif
