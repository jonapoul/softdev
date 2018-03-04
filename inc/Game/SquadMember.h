#ifndef SQUADMEMBER_H
#define SQUADMEMBER_H

#include <string>
#include <vector>

class Squad;
class GameEngine;
class Player;

class SquadMember {
public:
   SquadMember(GameEngine * const e,
               Player * const p,
               Squad * const s);

protected:
   GameEngine * engine;
   Player * player;
   Squad * squad;
   bool isCaptain;
   bool isHierophant;

   /* MAYBE GET RID OF THESE AND JUST USE engine->parameters? */
   unsigned movement; /* max movement distance in inches */
   int strength;      /* roll under this number in attacking/defending (+/-) */
   int shooting;      /* roll under this number in shooting */
   unsigned armour;   /* value a weapon must exceed to recieve damage */
   unsigned morale;   /* percentage likelihood to keep fighting */
   unsigned health;   /* amount of health left */
   unsigned cost;     /* value, in credits */
   std::vector<std::string> notes; /* additional info, characteristics/equipment */
};

#endif
