#include <string>

#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/SkillTree.h"
#include "Game/StatBoost.h"
#include "Game/GameParameters.h"
#include "Global.h"

Skill::Skill(GameEngine * const e,
             SkillTree * const st,
             Skill * const parent,
             int const i,
             bool const isHeadNode) 
      : GameObject(SKILL), engine(e), tree(st), index(i) {
   if (isHeadNode) {
      /* This is only the case if this is the head node of the tree */
      this->name = std::to_string(index);
   } else {
      this->name = parent->name + std::to_string(index);
   }
   this->depth = name.length();

   /* This skill is created as inactive, so we set its children to nullptrs
      until the user chooses to activate it */
   this->child0 = nullptr;
   this->child1 = nullptr;

   this->boost = new StatBoost(engine, this);
   // if (st->name == "Demoman") {
   //    boost->print();
   // }
   if (isHeadNode) {
      /* This is head node, so take both stat boosts */
      boost->add(tree->boost(0));
      boost->add(tree->boost(1));
      // if (st->name == "Demoman") {
      //    tree->boost(0)->print();
      //    tree->boost(1)->print();
      //    boost->print();
      //    PRINT(this->ID());
      //    // exit(1);
      // }
   } else {
      /* one of two possible stat boosts */
      boost->add(tree->boost(index));
   }
}

Skill::~Skill() {
   if (child0 != nullptr) child0->deallocate();
   if (child1 != nullptr) child1->deallocate();
   boost->deallocate();
}

void Skill::activate() {
   if (this->depth <= engine->parameters->MaxSkillTreeDepth) {
      /* Flag this skill as active and create two children below this one. */
      this->hasBeenActivated = true;
      this->child0 = new Skill(engine, tree, this, 0);
      this->child1 = new Skill(engine, tree, this, 1);
   } else {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "%s: Trying to activate skill '%s' beyond MaxSkillTreeDepth",
               __FUNCTION__, name.c_str());
      engine->warningMessage(warningbuf);
   }
}

bool Skill::isActive() const {
   return this->hasBeenActivated;
}

void Skill::copy(Skill const * const s) {
   this->name = s->name;
   this->index = s->index;
   this->depth = s->depth;
   this->hasBeenActivated = s->hasBeenActivated;
   if (s->child0 != nullptr) {
      this->child0->copy(s->child0);
   }
   if (s->child1 != nullptr) {
      this->child1->copy(s->child1);
   }
   this->boost->copy(s->boost);
}

void Skill::ensureValidity() const {
   ENSURE(type() == SKILL,           engine);
   ENSURE(name.length() > 0,         engine);
   ENSURE(boost->isBlank() == false, engine);
   int const MaxSkillTreeDepth = engine->parameters->MaxSkillTreeDepth;
   ENSURE(depth <= MaxSkillTreeDepth, engine);
}

void Skill::print() const {
   GameObject::print();
   printf("Skill:\n");
   printf("   engine           = %p, ID = %lu\n", engine, engine->ID());
   printf("   tree             = %p, ID = %lu\n", tree, tree->ID());
   printf("   name             = '%s'\n", name.c_str());
   printf("   index            = %d\n", index);
   printf("   hasBeenActivated = %d\n", hasBeenActivated);
   if (child0) printf("   child0           = %p, ID = %lu\n", child0, child0->ID());
   else        printf("   child0           = %p\n", nullptr);
   if (child1) printf("   child1           = %p, ID = %lu\n", child1, child1->ID());
   else        printf("   child1           = %p\n", nullptr);
   if (boost)  printf("   boost            = %p, ID = %lu\n", boost, boost->ID());
   else        printf("   boost            = %p\n", nullptr);
}