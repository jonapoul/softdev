#include "Game/Hierophant.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"

Hierophant::Hierophant(Squad * const s)
      : SpecialisedSquadMember(s), specialism(NoHierophantSpecialism) {
   this->setType(HIEROPHANT);
   /* TODO: Something */
}

Hierophant::~Hierophant() {
   /* Delete skills? */
}

void Hierophant::ensureValidity() const {
   ENSURE(type() == HIEROPHANT, engine);
   ENSURE(specialism == NoHierophantSpecialism, engine);
}

int Hierophant::stringToSpecialism(char const * const str) const {
   std::string const string(str);
   if      (string == "Speaker") return SpeakerHS;
   else if (string == "Priest")  return PriestHS;
   else if (string == "Medic")   return MedicHS;
   else if (string == "Support") return SupportHS;
   else                          return NoHierophantSpecialism;
}

std::string Hierophant::specialismToString(int const spec) {
   switch (spec) {
      case SpeakerHS: return "Speaker";
      case PriestHS:  return "Priest";
      case MedicHS:   return "Medic";
      case SupportHS: return "Support";
      default:        return "Unknown";
   }
}