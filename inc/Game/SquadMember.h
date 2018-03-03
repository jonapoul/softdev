#ifndef SQUADMEMBER_H
#define SQUADMEMBER_H

#include <string>
#include <vector>
class Squad;

class SquadMember {
public:
   SquadMember();

protected:
   Squad * squad;
   
   bool isCaptain;
   bool isHierophant;

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