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
         int const i,
         bool const isHeadNode = false);
   ~Skill();

   void activate();
   bool isActive() const;
   void copy(Skill const * const s);
   virtual void ensureValidity() const;
   virtual void print() const;

private:
   GameEngine * engine;
   SkillTree * tree;
   std::string name;
   int index;
   int depth;
   bool hasBeenActivated = false;

   Skill * child0;
   Skill * child1;

   /* This pointer is shared with the SkillTree, so it doesn't get deallocated
      in the ~Skill() destructor */
   StatBoost * boost;
};

#endif
