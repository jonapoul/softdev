#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "Game/GameObject.h"

class GameEngine;
class SkillTree;
class StatBoost;

class Skill : public GameObject {

   friend class SkillTree;

public:
   Skill(GameEngine * const e,
         SkillTree * const st,
         Skill * const parent,
         int const i);
   ~Skill();

   void activate();
   bool isActive() const;
   virtual void ensureValidity() const;
   virtual void print() const;

private:
   GameEngine * engine;
   SkillTree * tree;
   std::string name;
   int index;
   bool hasBeenActivated = false;

   Skill * child0;
   Skill * child1;

   /* This pointer is shared with the SkillTree, so it doesn't get deallocated
      in the ~Skill() destructor */
   StatBoost * boost;
};

#endif
