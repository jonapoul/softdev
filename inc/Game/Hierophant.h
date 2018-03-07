#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include <vector>
#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"

class Squad;

typedef enum {
   NoHierophantSpecialism,
   SpeakerHS, /* +morale,   +movement */
   PriestHS,  /* +health,   +morale */
   MedicHS,   /* +health,   +strength */
   SupportHS, /* +shooting, +armour */
   NumHierophantSpecialisms
} HierophantSpecialism;

class Hierophant : public SpecialisedSquadMember {
public:
   Hierophant(Squad * const s);
   ~Hierophant();

   virtual void checkValidity() const;

private:
   HierophantSpecialism specialism;
};

#endif