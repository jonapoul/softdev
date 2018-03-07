#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <vector>
#include <string>

#include "Game/GameObject.h"

class GameEngine;
class SpecialisedSquadMember;
class Skill;
class StatBoost;

typedef enum {
   NoSkillTreeClass,
   HierophantSkillTreeClass,
   CaptainSkillTreeClass,
   NumSkillTreeClasses
} SkillTreeClass;

class SkillTree : public GameObject {
public:
   SkillTree(GameEngine * const e,
             SpecialisedSquadMember * const s);
   SkillTree(GameEngine * const e,
             ObjectType const t,
             int const specialism,
             char ** modiferStrings,
             bool * const isValid);
   ~SkillTree();

   void setSpecialism(char const * const specialismStr);
   virtual void checkValidity() const;

private:
   GameEngine * engine;
   SpecialisedSquadMember * owner;
   std::string name;
   SkillTreeClass skillTreeClass;
   int specialism; /* Either HierophantSpecialism or CaptainSpecialism enum */
   Skill ** child;
   StatBoost ** boost;
};

#endif
