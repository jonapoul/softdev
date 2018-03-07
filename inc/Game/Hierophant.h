#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include <vector>
#include <string>

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

   int stringToSpecialism(char const * const str) const override;
   static std::string specialismToString(int const spec);
   virtual void checkValidity() const;

private:
   HierophantSpecialism specialism;
};

#endif