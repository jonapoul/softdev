#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include "Game/GameObject.h"
#include "Game/SpecialisedSquadMember.h"

class Squad;

typedef enum {
   NoCaptainSpecialism,
   DemomanCS, /* +armour,   +health */
   ScoutCS,   /* +shooting, +movement */
   SoldierCS, /* +shooting, +strength */
   LeaderCS,  /* +morale,   +movement */
   HeavyCS,   /* +health,   +strength */
   EliteCS,   /* +morale,   +armour */
   NumCaptainSpecialisms
} CaptainSpecialism;

class Captain : public SpecialisedSquadMember {
public:
   Captain(Squad * const s);
   ~Captain();

   virtual void checkValidity() const;

private:
   CaptainSpecialism specialism;
};

#endif