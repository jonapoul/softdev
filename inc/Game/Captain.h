#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include <string>

#include "Game/GameObject.h"
#include "Game/SpecialisedSquadMember.h"

class Squad;

class Captain : public SpecialisedSquadMember {
public:
   Captain(Squad * const s);
   ~Captain();

   typedef enum {
      NoSpecialism = 0,
      Demoman, /* +armour,   +health */
      Scout,   /* +shooting, +movement */
      Soldier, /* +shooting, +strength */
      Leader,  /* +morale,   +movement */
      Heavy,   /* +health,   +strength */
      Elite,   /* +morale,   +armour */
      NumSpecialisms
   } Specialism;

   int stringToSpecialism(char const * const str) const override;
   void setSkillTree(char const * const spec) override;
   virtual void ensureValidity() const;
   virtual void print() const;
   static std::string specialismToString(Captain::Specialism const spec);

private:
   Captain::Specialism specialism;
};

#endif