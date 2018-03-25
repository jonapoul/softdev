#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

#include "Game/GameObject.h"

class GameEngine;
class Player;
class Captain;
class Hierophant;
class SquadMember;
class Item;
class Weapon;

enum {
   iSquadUsername,
   iSquadName,
   iSquadIsPublic,
   iSquadCredits,

   iCaptainExperience,
   iCaptainSpecialism,
   iCaptainSkills,
   iCaptainItems,
   iCaptainWeapons,
   iCaptainStatBoosts,

   iHierophantExperience,
   iHierophantSpecialism,
   iHierophantSkills,
   iHierophantItems,
   iHierophantWeapons,
   iHierophantStatBoosts,

   iNumNormalSquadMembers,
   iSquadWeapons,
   iSquadItems,

   nSquadParameters
};

class Squad : public GameObject {
public:
   Squad(GameEngine * const e,
         Player * const p);
   ~Squad();

   bool init(char const * const file);
   void initItems(char ** itemsStr,
                  size_t const Nitems);
   void initWeapons(char ** weaponsStr,
                    size_t const NWeapons);

   virtual void ensureValidity() const;
   virtual void print() const;


   GameEngine * engine     = nullptr;
   Player * player         = nullptr;
   Captain * captain       = nullptr;
   Hierophant * hierophant = nullptr;
   std::vector<SquadMember *> squadMembers;
   std::vector<Item *> items;
   std::vector<Weapon *> weapons;
   bool isPublic;
   int credits;
   std::string filename;
};

#endif
