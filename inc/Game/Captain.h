#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include "SquadMember.h"

class SkillTree;
class Skill;

typedef enum {
   DemomanCS, /* +armour,   +health */
   ScoutCS,   /* +shooting, +movement */
   SoldierCS, /* +shooting, +strength */
   LeaderCS,  /* +morale,   +movement */
   HeavyCS,   /* +health,   +strength */
   EliteCS,   /* +morale,   +armour */
   NumCaptainSpecialisms
} CaptainSpecialism;

class Captain : public SquadMember {
public:
   Captain();

private:
   int experience;
   CaptainSpecialism specialism;
   SkillTree * skillTree;
   std::vector<Skill *> skills;
};

#endif