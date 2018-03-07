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

void Hierophant::checkValidity() const {
   CHECK(specialism != NoHierophantSpecialism, engine);
}