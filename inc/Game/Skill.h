#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "Game/GameObject.h"

class GameEngine;
class SkillTree;

class Skill : public GameObject {
public:
   Skill(GameEngine * const e,
         SkillTree * const st,
         Skill * const parent,
         std::string const& index);
   ~Skill();

   virtual void checkValidity() const;

private:
   GameEngine * engine;
   SkillTree * tree;
   //Skill ** child;
   std::string name;
};

#endif
