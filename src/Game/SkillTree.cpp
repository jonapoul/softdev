#include <sstream>

#include "Game/SkillTree.h"
#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/SpecialisedSquadMember.h"
#include "Game/Captain.h"
#include "Game/Hierophant.h"
#include "Game/StatBoost.h"
#include "Global.h"

SkillTree::SkillTree(GameEngine * const e,
                     SpecialisedSquadMember * const o)
      : GameObject(SKILLTREE), engine(e), owner(o) {
   this->boost = new StatBoost*[2];
   boost[0] = new StatBoost(engine);
   boost[1] = new StatBoost(engine);
   this->child = new Skill*[2];
   child[0] = new Skill(engine, this, nullptr, "0");
   child[1] = new Skill(engine, this, nullptr, "1");
}

SkillTree::SkillTree(GameEngine * const e,
                     ObjectType const t,
                     int const specialism,
                     char ** skillString,
                     bool * const isValid)
      : GameObject(SKILLTREE), engine(e), owner(nullptr) {

   this->boost = new StatBoost*[2];
   boost[0] = new StatBoost(engine);
   boost[1] = new StatBoost(engine);
   this->child = new Skill*[2];
   child[0] = new Skill(engine, this, nullptr, "0");
   child[1] = new Skill(engine, this, nullptr, "1");

   switch (t) {
      case CAPTAIN:
         this->name = Captain::specialismToString(specialism);
         this->skillTreeClass = CaptainSkillTreeClass;
         break;
      case HIEROPHANT:
         this->name = Hierophant::specialismToString(specialism);
         this->skillTreeClass = HierophantSkillTreeClass;
         break;
      default:
         *isValid = false;
         return;
   }

   for (size_t i = 0; i < 2; i++) {
      if (Global::wordCount(skillString[i]) != 2) {
         *isValid = false;
         return;
      }
      std::stringstream ss(skillString[i]);
      std::string modifier, modifiedStat;
      ss >> modifier >> modifiedStat;
      bool boostIsValid = true;
      StatBoost * b = new StatBoost(engine, modifiedStat, modifier, &boostIsValid);
      if (boostIsValid) {
         boost[i]->deallocate();
         boost[i] = b;
      } else {
         b->deallocate();
         *isValid = false;
         return;
      }
   }
}

SkillTree::~SkillTree() {
   for (size_t i = 0; i < 2; i++) {
      child[i]->deallocate();
      boost[i]->deallocate();
   }
   delete[] child;
   delete[] boost;
}

void SkillTree::setSpecialism(char const * const specialismStr) {
   bool isValid = true;
   this->specialism = owner->stringToSpecialism(specialismStr);
   /* No recognised specialism string */
   if (specialism == 0) {
      isValid = false;
   }
   switch (owner->type()) {
      case CAPTAIN: 
         this->skillTreeClass = CaptainSkillTreeClass;
         break;
      case HIEROPHANT:
         this->skillTreeClass = HierophantSkillTreeClass;
         break;
      default:
         this->skillTreeClass = NoSkillTreeClass;
         isValid = false;
         break;
   }
   if (!isValid) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Failed to recognise skill specialism '%s'",
               __FUNCTION__, specialismStr);
      engine->criticalMessage(criticalbuf);
      /* QUIT */
   }
}

void SkillTree::checkValidity() const {
   CHECK(type() == SKILLTREE, engine);
   CHECK(skillTreeClass != NoSkillTreeClass, engine);
}
