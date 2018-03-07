#include <string>
#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/SkillTree.h"

Skill::Skill(GameEngine * const e,
             SkillTree * const st,
             Skill * const parent,
             std::string const& index) 
      : GameObject(SKILL), engine(e), tree(st) {
   if (parent == nullptr) this->name = index;
   else                   this->name = parent->name + index;
   //this->child = new Skill*[2];
   //child[0] = child[1] = nullptr;
}

Skill::~Skill() {
   // if (child[0] != nullptr) child[0]->deallocate();
   // if (child[1] != nullptr) child[1]->deallocate();
}

void Skill::checkValidity() const {
   CHECK(type() == SKILL, engine);
   CHECK(name.length() > 0, engine);
}
