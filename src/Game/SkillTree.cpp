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

   this->headNode   = new Skill(engine, this, nullptr, 0);
   this->totalBoost = new StatBoost(engine); /* all blank boosts */
   this->boost0     = new StatBoost(engine);
   this->boost1     = new StatBoost(engine);
}

bool SkillTree::init(ObjectType const ownerType,
                     int const specialism,
                     char ** skillStrings) {
   switch (ownerType) {
      case CAPTAIN:
         this->name = Captain::specialismToString(specialism);
         this->skillTreeClass = CaptainSkillTreeClass;
         break;
      case HIEROPHANT:
         this->name = Hierophant::specialismToString(specialism);
         this->skillTreeClass = HierophantSkillTreeClass;
         break;
      default:
         /* Only captain/hierophant have access to skill trees */
         return false;
   }

   /* skillStrings should have two elements:
        e.g. [ '+1 Strength', '+1 Shooting' ] */
   for (size_t i = 0; i < 2; i++) {
      /* Each skillString needs a modifer and a stat to modify */
      if (Global::wordCount(skillStrings[i]) != 2) {
         return false;
      }
      std::stringstream ss(skillStrings[i]);
      std::string modifier, modifiedStat;
      ss >> modifier >> modifiedStat;
      StatBoost * b = new StatBoost(engine);
      /* check if the strings are valid */
      bool const boostIsValid = b->init(modifiedStat, modifier);
      if (!boostIsValid) {
         /* if not, close program */
         b->deallocate();
         char critbuf[MAX_MESSAGE_LENGTH];
         snprintf(critbuf, MAX_MESSAGE_LENGTH,
                  "%s: SkillTree '%s' has an invalid modifer: '%s'",
                  __FUNCTION__, name.c_str(), skillStrings[i]);
         engine->criticalMessage(critbuf);
         /* QUIT */
      } else {
         StatBoost * ptr = (i == 0) ? boost0 : boost1;
         ptr->copy(b);
         b->deallocate();
      }
   }
   return true;
}

SkillTree::~SkillTree() {
   headNode->deallocate(); /* also deallocates all children */
   totalBoost->deallocate();
   boost0->deallocate();
   boost1->deallocate();
}

void SkillTree::setSpecialism(char const * const specialismStr) {
   /* e.g. convert the string 'Demoman' to enum integer DEMOMAN */
   this->specialism = owner->stringToSpecialism(specialismStr);
   /* No recognised specialism string */
   if (specialism == 0) {
      char criticalbuf[MAX_MESSAGE_LENGTH];
      snprintf(criticalbuf, MAX_MESSAGE_LENGTH,
               "%s: Couldn't recognise SkillTree specialism '%s'",
               __FUNCTION__, specialismStr);
      engine->criticalMessage(criticalbuf);
      /* QUIT */
   }
}

StatBoost * SkillTree::boost(int const index) const {
   switch (index) {
      case 0:  return this->boost0;
      case 1:  return this->boost1;
      default: return nullptr;
   }
}

std::vector<Skill*> SkillTree::getAllActiveSkills() const {
   std::vector<Skill*> array = {};
   if (headNode->isActive() == false) {
      return array; /* No skills */
   }
   array.push_back(headNode);
   getAllActiveSkillsRecursive(headNode, &array);
   return array;
}

/* Recursively go through the tree and append any skills that the user has
   activated */
void SkillTree::getAllActiveSkillsRecursive(Skill * const s,
                                            std::vector<Skill*> * array) const {
   if (s->child0 != nullptr && s->child0->isActive()) {
      array->push_back(s->child0);
      getAllActiveSkillsRecursive(s->child0, array);
   }
   if (s->child1 != nullptr && s->child1->isActive()) {
      array->push_back(s->child1);
      getAllActiveSkillsRecursive(s->child1, array);
   }
}

StatBoost * SkillTree::summedBoosts() {
   /* 1) Get all active skill objects
      2) Reset the existing totalBoost object to defaults
      3) Sum the skills' cumulative effect on stats and put it in totalBoost
      4) Return */
   std::vector<Skill*> allSkills = getAllActiveSkills();
   this->totalBoost->reset();
   for (auto s : allSkills) {
      this->totalBoost->add(s->boost);
   }
   return this->totalBoost;
}

void SkillTree::ensureValidity() const {
   ENSURE(type() == SKILLTREE,                engine);
   ENSURE(skillTreeClass != NoSkillTreeClass, engine);
}
