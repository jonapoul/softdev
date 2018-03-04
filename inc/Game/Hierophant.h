#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include <vector>
#include "SquadMember.h"

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
   Hierophant();

private:
   int experience;
   HierophantSpecialism specialism;
   SkillTree * skillTree;
   std::vector<Skill *> skills;
};

#endif