#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include <vector>
#include "SquadMember.h"

class GameEngine;
class Player;
class Squad;
class SkillTree;
class Skill;

typedef enum {
   SpeakerHS, /* +morale,   +movement */
   PriestHS,  /* +health,   +morale */
   MedicHS,   /* +health,   +strength */
   SupportHS, /* +shooting, +armour */
   NumHierophantSpecialisms
} HierophantSpecialism;

class Hierophant : public SquadMember {
public:
   Hierophant(GameEngine * const e,
              Player * const p,
              Squad * const s);
   ~Hierophant();

   void initSkills(char ** skillsStr,
                   size_t const Nskills);
   void initItems(char ** itemsStr,
                  size_t const Nitems);
   void initWeapons(char ** weaponsStr,
                    size_t const NWeapons);

private:
   int experience;
   HierophantSpecialism specialism;
   SkillTree * skillTree;
   std::vector<Skill *> skills;
};

#endif