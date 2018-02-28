#ifndef __CAPTAIN_H__
#define __CAPTAIN_H__

#include "pch.h"
#include "SquadMember.h"
class SkillTree;
class Skill;

enum CaptainSpecialism {
   DemomanCS, /* +armour,   +health */
   ScoutCS,   /* +shooting, +movement */
   SoldierCS, /* +shooting, +strength */
   LeaderCS,  /* +morale,   +movement */
   HeavyCS,   /* +health,   +strength */
   EliteCS,   /* +morale,   +armour */
   CountCS
};

class Captain : public SquadMember {
public:
   Captain();

private:
   int experience;
   CaptainSpecialism specialism;
   SkillTree * skill_tree;
   std::vector<Skill> skills;
};

#endif