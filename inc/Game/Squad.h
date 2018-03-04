#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

class GameEngine;
class Player;
class Captain;
class Hierophant;
class SquadMember;

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

class Squad {
public:
   /* New squad initialisation */
   Squad(GameEngine * const e,
         Player * const p);

   /* Loading from an existing save file */
   Squad(GameEngine * const e,
         Player * const p,
         char const * const filename,
         bool * const squadFileIsValid);

   ~Squad();

private:
   GameEngine * engine;
   Player * player;
   Captain * captain;
   Hierophant * hierophant;
   std::vector<SquadMember *> squadMembers;
   bool isPublic;
   int credits;
   std::string filename;
};

#endif
