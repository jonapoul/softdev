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

void Captain::checkValidity() const {
   CHECK(specialism != NoCaptainSpecialism, engine);
}