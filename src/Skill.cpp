#include <string>

#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/SkillTree.h"
#include "Game/StatBoost.h"
#include "Global.h"

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

void Skill::print() const {
   GameObject::print();
   printf("Skill:\n");
   printf("   engine           = %p, ID = %zu\n", engine, engine->ID());
   printf("   tree             = %p, ID = %zu\n", tree, tree->ID());
   printf("   name             = '%s'\n", name.c_str());
   printf("   index            = %d\n", index);
   printf("   hasBeenActivated = %d\n", hasBeenActivated);
   if (child0) printf("   child0           = %p, ID = %zu\n", child0, child0->ID());
   else        printf("   child0           = %p\n", nullptr);
   if (child1) printf("   child1           = %p, ID = %zu\n", child1, child1->ID());
   else        printf("   child1           = %p\n", nullptr);
   if (boost)  printf("   boost            = %p, ID = %zu\n", boost, boost->ID());
   else        printf("   boost            = %p\n", nullptr);
}