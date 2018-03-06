#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include "SquadMember.h"

class GameEngine;
class Player;
class Squad;
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
   Captain(GameEngine * const e,
           Player * const p,
           Squad * const s);
   ~Captain();
   void initSkills(char ** skillsStr,
                   size_t const Nskills);
   void initItems(char ** itemsStr,
                  size_t const Nitems);
   void initWeapons(char ** weaponsStr,
                    size_t const NWeapons);

private:
   int experience;
   CaptainSpecialism specialism;
   SkillTree * skillTree;
   std::vector<Skill *> skills;
};

#endif