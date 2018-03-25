#include "Game/Captain.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"
#include "Global.h"

Captain::Captain(Squad * const s)
      : SpecialisedSquadMember(s), specialism(NoSpecialism) {
   this->setType(CAPTAIN);
   /* TODO: something? */
}

Captain::~Captain() {
   /* blank */
}

int Captain::stringToSpecialism(char const * const str) const {
   std::string const string(str);
   if      (string == "Demoman") return Demoman;
   else if (string == "Scout")   return Scout;
   else if (string == "Soldier") return Soldier;
   else if (string == "Leader")  return Leader;
   else if (string == "Heavy")   return Heavy;
   else if (string == "Elite")   return Elite;
   else                          return NoSpecialism;
}

void Captain::setSkillTree(char const * const specStr) {
   int const specInt = this->stringToSpecialism(specStr);
   this->specialism = static_cast<Captain::Specialism>(specInt);

   /* initialise the captain's skill tree by copying off the array of valid
      skilltrees stored in the GameEngine */
   this->skillTree->copy(CAPTAIN, specialism);
}

std::string Captain::specialismToString(Captain::Specialism const spec) {
   switch (spec) {
      case Demoman: return "Demoman";
      case Scout:   return "Scout";
      case Soldier: return "Soldier";
      case Leader:  return "Leader";
      case Heavy:   return "Heavy";
      case Elite:   return "Elite";
      default:      return "Unknown";
   }
}

void Captain::ensureValidity() const {
   ENSURE(type() == CAPTAIN, engine);
   ENSURE(specialism == NoSpecialism, engine);
}

void Captain::print() const {
   SpecialisedSquadMember::print();
   printf("Captain:\n");
   printf("   specialism       = %d\n", specialism);
   printf("   specialismString = '%s'\n", Captain::specialismToString(specialism).c_str());
}