#include "Game/Hierophant.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/GameObject.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"
#include "Global.h"

Hierophant::Hierophant(Squad * const s)
      : SpecialisedSquadMember(s), specialism(NoSpecialism) {
   this->setType(HIEROPHANT);
   /* TODO: Something */
}

Hierophant::~Hierophant() {
   /* Delete skills? */
}

void Hierophant::ensureValidity() const {
   ENSURE(type() == HIEROPHANT, engine);
   ENSURE(specialism != NoSpecialism, engine);
   SpecialisedSquadMember::ensureValidity();
}

int Hierophant::stringToSpecialism(char const * const str) const {
   std::string const string(str);
   if      (string == "Speaker") return Speaker;
   else if (string == "Priest")  return Priest;
   else if (string == "Medic")   return Medic;
   else if (string == "Support") return Support;
   else                          return NoSpecialism;
}

void Hierophant::setSkillTree(char const * const spec) {
   int const specInt = this->stringToSpecialism(spec);
   this->specialism = static_cast<Hierophant::Specialism>(specInt);

   /* initialise the hierophant's skill tree by copying off the array of valid
      skilltrees stored in the GameEngine */
   this->skillTree->copy(HIEROPHANT, specialism);
}

std::string Hierophant::specialismToString(Hierophant::Specialism const spec) {
   switch (spec) {
      case Speaker: return "Speaker";
      case Priest:  return "Priest";
      case Medic:   return "Medic";
      case Support: return "Support";
      default:      return "Unknown";
   }
}

void Hierophant::print() const {
   SpecialisedSquadMember::print();
   printf("Hierophant:\n");
   printf("   Specialism       = %d\n", specialism);
   printf("   SpecialismString = '%s'\n", Hierophant::specialismToString(specialism).c_str());
}