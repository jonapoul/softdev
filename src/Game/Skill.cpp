#include <string>

#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/SkillTree.h"
#include "Game/StatBoost.h"

Skill::Skill(GameEngine * const e,
             SkillTree * const st,
             Skill * const parent,
             int const i) 
      : GameObject(SKILL), engine(e), tree(st), index(i) {
   if (parent == nullptr) {
      /* This is only the case if this is the head node of the tree */
      this->name = std::to_string(index);
   } else {
      this->name = parent->name + std::to_string(index);
   }

   /* This skill is created as inactive, so we set its children to nullptrs
      until the user chooses to activate it */
   this->child0 = nullptr;
   this->child1 = nullptr;

   /* one of two possible stat boosts */
   this->boost = tree->boost(index);
}

Skill::~Skill() {
   if (child0 != nullptr) child0->deallocate();
   if (child1 != nullptr) child1->deallocate();
}

void Skill::activate() {
   /* Flag this skill as active and create two children below this one. */
   this->hasBeenActivated = true;
   this->child0 = new Skill(engine, tree, this, 0);
   this->child1 = new Skill(engine, tree, this, 1);
}

bool Skill::isActive() const {
   return this->hasBeenActivated;
}

void Skill::ensureValidity() const {
   ENSURE(type() == SKILL,           engine);
   ENSURE(name.length() > 0,         engine);
   ENSURE(boost->isBlank() == false, engine);
}