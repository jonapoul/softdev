#include "Game/Hierophant.h"
#include "Game/SquadMember.h"
#include "Game/Skill.h"
#include "Game/SkillTree.h"

Hierophant::Hierophant(GameEngine * const e,
                       Player * const p,
                       Squad * const s)
      : SquadMember(e, p, s), specialism(NoHierophantSpecialism) {
   this->setType(HIEROPHANT);
   /* TODO: Something */
}

Hierophant::~Hierophant() {
   /* Delete skills? */
}

void Hierophant::initSkills(char ** skillsStr,
                            size_t const Nskills) {
   /* something */
}

void Hierophant::initItems(char ** itemsStr,
                           size_t const Nitems) {
   /* something */
}

void Hierophant::initWeapons(char ** weaponsStr,
                             size_t const NWeapons) {
   /* something */
}

void Hierophant::checkValidity() const {
   CHECK(experience >= 0, engine);
   CHECK(specialism != NoHierophantSpecialism, engine);
   /* Something with skills? */
}