#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include "SquadMember.h"
class SkillTree;
class Skill;

enum HierophantSpecialism {
   SpeakerHS, /* +morale,   +movement */
   PriestHS,  /* +health,   +morale */
   MedicHS,   /* +health,   +strength */
   SupportHS, /* +shooting, +armour */
   CountHS
};

class Hierophant : public SquadMember {
public:
   Hierophant();

private:
   int experience;
   HierophantSpecialism specialism;
   SkillTree * skill_tree;
   std::vector<Skill> skills;
};

#endif