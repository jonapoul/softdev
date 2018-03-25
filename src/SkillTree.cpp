#include <sstream>

#include "Game/SkillTree.h"
#include "Game/Skill.h"
#include "Game/GameEngine.h"
#include "Game/Captain.h"
#include "Game/Hierophant.h"
#include "Game/StatBoost.h"
#include "Game/GameParameters.h"
#include "Global.h"

SkillTree::SkillTree(GameEngine * const e,
                     GameObject * const o)
      : GameObject(SKILLTREE), engine(e), owner(o) {

   this->totalBoost = new StatBoost(engine, this); /* all blank boosts */
   this->boost0     = new StatBoost(engine, this);
   this->boost1     = new StatBoost(engine, this);
   this->headNode   = nullptr;
}

/* This is only called from GameEngine, when populating the list of available
   SkillTrees */
bool SkillTree::init(ObjectType const ownerType,
                     int const specialism,
                     char ** skillStrings) {
   this->specialism = specialism;
   switch (ownerType) {
      case CAPTAIN:
         this->name = Captain::specialismToString((Captain::Specialism)specialism);
         this->treeType = CaptainTreeType;
         break;
      case HIEROPHANT:
         this->name = Hierophant::specialismToString((Hierophant::Specialism)specialism);
         this->treeType = HierophantTreeType;
         break;
      default:
         /* Only captain/hierophant have access to skill trees, this should
            never be triggered */
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
      StatBoost * b = new StatBoost(engine, this);
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
         StatBoost * ptr = (i == 0) ? this->boost0 : this->boost1;
         ptr->copy(b);
         b->deallocate();
      }
   }
   if (headNode == nullptr) {
      this->headNode = new Skill(engine, this, nullptr, 0, true);
   }
   return true;
}

/* Grabs the list of all valid skill trees from the GameEngine, finds which
   one matches the specialism we're looking for, then copies all info over */
void SkillTree::copy(ObjectType const type,
                     int const spec) {
   auto const allTrees = engine->allSkillTrees();
   for (auto tree : allTrees) {
      bool bothCaptain    = (type == CAPTAIN    && tree->treeType == CaptainTreeType);
      bool bothHierophant = (type == HIEROPHANT && tree->treeType == HierophantTreeType);
      if (bothCaptain || bothHierophant) {
         if (spec == tree->specialism) {
            this->name       = tree->name;
            this->treeType   = tree->treeType;
            this->specialism = tree->specialism;
            this->boost0->copy(tree->boost0);
            this->boost1->copy(tree->boost1);
            if (headNode == nullptr) {
               this->headNode = new Skill(engine, this, nullptr, 0, true);
            }
            this->headNode->copy(tree->headNode);
            return;
         }
      }
   }
}

SkillTree::~SkillTree() {
   totalBoost->deallocate();
   boost0->deallocate();
   boost1->deallocate();
   if (headNode != nullptr) headNode->deallocate(); /* also deallocates all children */
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

std::vector<Skill*> SkillTree::getAllAvailableSkills() const {
   std::vector<Skill*> array = {};
   if (headNode->isActive() == false) {
      array.push_back(headNode);
   } else {
      getAllAvailableSkillsRecursive(headNode, &array);
   }
   return array;
}

/* Recursively go through the tree and append any skills that the user is able
   to choose and havent already been activated */
void SkillTree::getAllAvailableSkillsRecursive(Skill * const s,
                                               std::vector<Skill*> * array) const {
   if (s->child0->isActive()) {
      getAllAvailableSkillsRecursive(s->child0, array);
   } else {
      array->push_back(s->child0);
   }
   if (s->child1->isActive()) {
      getAllAvailableSkillsRecursive(s->child1, array);
   } else {
      array->push_back(s->child1);
   }
}

StatBoost * SkillTree::summedBoosts() {
   /* 1) Get all active skill objects
      2) Reset the existing totalBoost object to defaults
      3) Sum the skills' cumulative effect on stats and put it in totalBoost
      4) Return */
   this->updateTotalBoost();
   return this->totalBoost;
}

bool SkillTree::skillStringIsValid(std::string const& skillString) {
/* Must be all zeros and ones, e.g. '0010' */
   for (char c : skillString) {
      if (c != '0' && c != '1') {
         return false;
      }
   }
   /* If we're trying to go too deep in */
   if ((int)skillString.length() > engine->parameters->MaxSkillTreeDepth) {
      return false;
   }
   /* If the first character isn't the head node (0) */
   if (skillString[0] != '0') {
      return false;
   }
   /* If we're only selecting the head node, and it isnt already active */
   if (skillString == "0" && this->headNode->isActive() == false) {
      return true;
   }
   Skill * currentSkill = this->headNode;
   /* Iterate through the string and check that the path leads to a valid skill */
   for (size_t i = 1; i < skillString.length(); i++) {
      std::string const subTree = skillString.substr(i);
      currentSkill = (subTree[0] == '0') ? currentSkill->child0 : currentSkill->child1;
      if (currentSkill->isActive() == false) {
         return (subTree.length() == 1);
      }
   }
   return false;
}

/* Traverses the tree based on the numerical directions in the skill string.
     e.g. for a string of '011': 
         1) currentSkill set to headNode (first '0')
         2) currentIndex set to 1, since thats the next index in the string
         3) currentSkill set to head->child1
         4) Next iteration
         4) currentIndex set to 1
         5) currentSkill set to head->child1->child1
         6) activate this skill
   No error checking done in here, because that's all done by
   skillStringIsValid() right before this is called
*/
void SkillTree::activateSkill(std::string const& skillString) {
   Skill * currentSkill = this->headNode;
   for (size_t i = 1; i < skillString.length(); i++) {
      int const currentIndex = skillString[i] - '0';
      currentSkill = (currentIndex == 0) ? currentSkill->child0 : currentSkill->child1;
   }
   currentSkill->activate();
   this->updateTotalBoost();
}

void SkillTree::updateTotalBoost() {
   std::vector<Skill*> const allSkills = getAllActiveSkills();
   this->totalBoost->reset();
   for (auto s : allSkills) {
      this->totalBoost->add(s->boost);
   }
}

void SkillTree::ensureValidity() const {
   ENSURE(type() == SKILLTREE,    engine);
   ENSURE(treeType != NoTreeType, engine);
}

void SkillTree::print() const {
   GameObject::print();
   printf("SkillTree:\n");
   printf("   engine           = %p, ID = %lu\n", engine, engine->ID());
   printf("   owner            = %p, ID = %lu\n", owner, owner->ID());
   printf("   name             = '%s'\n", name.c_str());
   printf("   specialism       = %d\n", specialism);
   printf("   headNode         = %p, ID = %lu\n", headNode, headNode->ID());
   printf("   totalBoost       = %p, ID = %lu\n", totalBoost, totalBoost->ID());
   printf("   boost0           = %p, ID = %lu\n", boost0, boost0->ID());
   printf("   boost1           = %p, ID = %lu\n", boost1, boost1->ID());
   auto activeSkills = getAllActiveSkills();
   printf("   Active Skills    = [ ");
   for (auto s : activeSkills) printf("%lu ", s->ID());
   printf("]\n");
   auto availableSkills = getAllAvailableSkills();
   printf("   Available Skills = [ ");
   for (auto s : availableSkills) printf("%lu ", s->ID());
   printf("]\n");
}