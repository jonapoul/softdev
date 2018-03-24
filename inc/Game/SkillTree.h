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

   friend class Skill;

public:
   SkillTree(GameEngine * const e,
             SpecialisedSquadMember * const s);
   ~SkillTree();

   bool init(ObjectType const ownerType,
             int const specialism,
             char ** modiferStrings);

   void setSpecialism(char const * const specialismStr);
   StatBoost * boost(int const index) const;
   StatBoost * summedBoosts();
   virtual void ensureValidity() const;

private:
   GameEngine * engine;
   SpecialisedSquadMember * owner;
   std::string name;
   SkillTreeClass skillTreeClass;
   int specialism; /* Either HierophantSpecialism or CaptainSpecialism enum */

   /* totalBoost is the sum of all bonuses from child skills that have been
      chosen from the tree.
      boost1 and boost2 have only one non-default member each. The Head Skill
      node will give bonuses from both of these, but every subsequent skill
      below that will give one of these two boosts.
         e.g. if boost1 = +1 strength, boost2 = +1 shooting:
            - choosing headNode gives +1 strength AND +1 shooting.
            - headNode then has two children, child1 gives +1 shooting and
              child2 gives +1 strength.
            - choosing one of these two children builds two more children below
              it, each with the same bonuses.
      There's probably a better way of explaining it
   */
   Skill * headNode;
   StatBoost * totalBoost;
   StatBoost * boost0;
   StatBoost * boost1;

   std::vector<Skill*> getAllActiveSkills() const;
   void getAllActiveSkillsRecursive(Skill * const s,
                                    std::vector<Skill*> * array) const;
};

#endif
