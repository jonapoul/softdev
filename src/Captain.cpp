#include "Game/Captain.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"

Captain::Captain(Squad * const s)
      : SpecialisedSquadMember(s), specialism(NoCaptainSpecialism) {
   this->setType(CAPTAIN);
   /* TODO: something */
}

Captain::~Captain() {
   /* Delete skills? */
}

void Captain::ensureValidity() const {
   ENSURE(type() == CAPTAIN, engine);
   ENSURE(specialism == NoCaptainSpecialism, engine);
}

int Captain::stringToSpecialism(char const * const str) const {
   std::string const string(str);
   if      (string == "Demoman") return DemomanCS;
   else if (string == "Scout")   return ScoutCS;
   else if (string == "Soldier") return SoldierCS;
   else if (string == "Leader")  return LeaderCS;
   else if (string == "Heavy")   return HeavyCS;
   else if (string == "Elite")   return EliteCS;
   else                          return NoCaptainSpecialism;
}

std::string Captain::specialismToString(int const spec) {
   switch (spec) {
      case DemomanCS: return "Demoman";
      case ScoutCS:   return "Scout";
      case SoldierCS: return "Soldier";
      case LeaderCS:  return "Leader";
      case HeavyCS:   return "Heavy";
      case EliteCS:   return "Elite";
      default:        return "Unknown";
   }
}