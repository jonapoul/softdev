#ifndef SPECIALISEDSQUADMEMBER_H
#define SPECIALISEDSQUADMEMBER_H

#include <vector>
#include "Game/SquadMember.h"

class GameEngine;
class Player;
class Squad;
class SkillTree;
class Weapon;
class Item;

class SpecialisedSquadMember : public SquadMember {
public:
   SpecialisedSquadMember(Squad * const s);
   ~SpecialisedSquadMember();

   void initSkills(char ** skillsStr,
                   size_t const nSkills);
   void initItems(char ** itemsStr,
                  size_t const nItems);
   void initWeapons(char ** weaponsStr,
                    size_t const nWeapons);

   virtual void checkValidity() const;

protected:
   int experience;
   SkillTree * skillTree;
   std::vector<Weapon *> weapons;
   std::vector<Item *> items;
};

#endif
