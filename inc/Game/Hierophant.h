#ifndef HIEROPHANT_H
#define HIEROPHANT_H

#include <vector>
#include <string>

#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"

class Squad;

class Hierophant : public SpecialisedSquadMember {
public:
   Hierophant(Squad * const s);
   ~Hierophant();

   typedef enum {
      NoSpecialism = 0,
      Speaker, /* +morale,   +movement */
      Priest,  /* +health,   +morale */
      Medic,   /* +health,   +strength */
      Support, /* +shooting, +armour */
      NumSpecialisms
   } Specialism;

   int stringToSpecialism(char const * const str) const override;
   void setSkillTree(char const * const spec) override;
   static std::string specialismToString(Hierophant::Specialism const spec);
   virtual void ensureValidity() const;
   virtual void print() const;

private:
   Hierophant::Specialism specialism;
};

#endif