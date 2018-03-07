#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include <string>

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

   int stringToSpecialism(char const * const str) const override;
   virtual void checkValidity() const;
   static std::string specialismToString(int const spec);

private:
   CaptainSpecialism specialism;
};

#endif