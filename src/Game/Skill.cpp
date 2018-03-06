#include <string>
#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SquadMember.h"

Skill::Skill(GameEngine * const e,
             SquadMember * const s) 
      : GameObject(SKILL), engine(e), squadmember(s) {

}

void Skill::checkValidity() const {
   CHECK(name.length() > 0, engine);
   CHECK(description.length() > 0, engine);
}
