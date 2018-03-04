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
              Squad * const s,
              char ** skillsStr,
              size_t const Nskills,
              char ** itemsStr,
              size_t const Nitems,
              char ** weaponsStr,
              size_t const NWeapons);
   ~Hierophant();

private:
   int experience;
   HierophantSpecialism specialism;
   SkillTree * skillTree;
   std::vector<Skill *> skills;
};

#endif