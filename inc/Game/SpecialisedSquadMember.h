#ifndef SPECIALISEDSQUADMEMBER_H
#define SPECIALISEDSQUADMEMBER_H

#include <vector>
#include <string>

#include "Game/SquadMember.h"

class GameEngine;
class Player;
class Squad;
class SkillTree;
class Weapon;
class Item;
class StatBoost;

class SpecialisedSquadMember : public SquadMember {
public:
   SpecialisedSquadMember(Squad * const s);
   ~SpecialisedSquadMember();

   void initSkills (char ** skillsStr,  size_t const nSkills);
   void initItems  (char ** itemsStr,   size_t const nItems);
   void initWeapons(char ** weaponsStr, size_t const nWeapons);
   void updateStats();

   float movement() const override;
   int strength() const override;
   int shooting() const override;
   int armour() const override;
   int morale() const override;
   int health() const override;
   int cost() const override;

   /* these two are implemented by Captain and Hierophant */
   virtual void setSkillTree(char const * const spec) = 0;
   virtual int stringToSpecialism(char const * const str) const = 0;

   virtual void ensureValidity() const;
   virtual void print() const;

protected:
   int experience;
   SkillTree * skillTree = nullptr;
   std::vector<Weapon *> weapons;
   std::vector<Item *> items;
   StatBoost * totalBoost = nullptr;
};

#endif
