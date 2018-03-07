#include "Game/SpecialisedSquadMember.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/SkillTree.h"
#include "Game/Weapon.h"
#include "Game/Item.h"
#include "Game/StatBoost.h"
#include "Game/GameParameters.h"
#include "Global.h"

SpecialisedSquadMember::SpecialisedSquadMember(Squad * const s)
      : SquadMember(s), experience(0) {
   this->setType(SPECIALISEDSQUADMEMBER);
   this->summedBoosts = new StatBoost(engine); /* blank, all default values */
   this->skillTree = new SkillTree(engine, this); /* blank, no skills active */
}

SpecialisedSquadMember::~SpecialisedSquadMember() {
   skillTree->deallocate();
   summedBoosts->deallocate();
   for (Weapon * weapon : weapons) {
      weapon->deallocate();
   }
   for (Item * item : items) {
      item->deallocate();
   }
}

void SpecialisedSquadMember::initSkills(char ** skillsStr,
                                        size_t const nSkills,
                                        char * specialismStr) {
   skillTree->setSpecialism(specialismStr);
}

void SpecialisedSquadMember::initItems(char ** itemsStr,
                                       size_t const nItems) {
   for (size_t iItem = 0; iItem < nItems; iItem++) {
      bool isValid = true;
      Item * item = new Item(this, engine, itemsStr[iItem], &isValid);
      item->setOwner(this);
      if (!isValid) {
         item->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid item string '%s'",
                  __FUNCTION__, itemsStr[iItem]);
         engine->warningMessage(warningbuf);
      } else {
         this->items.push_back(item);
      }
   }
}

void SpecialisedSquadMember::initWeapons(char ** weaponsStr,
                                         size_t const nWeapons) {
   for (size_t iWeapon = 0; iWeapon < nWeapons; iWeapon++) {
      bool isValid = true;
      Weapon * weapon = new Weapon(this, engine, weaponsStr[iWeapon], &isValid);
      weapon->setOwner(this);
      if (!isValid) {
         weapon->deallocate();
         char warningbuf[MAX_MESSAGE_LENGTH];
         snprintf(warningbuf, MAX_MESSAGE_LENGTH,
                  "%s: Invalid weapon string '%s'",
                  __FUNCTION__, weaponsStr[iWeapon]);
         engine->warningMessage(warningbuf);
      } else {
         this->weapons.push_back(weapon);
      }
   }
}

void SpecialisedSquadMember::updateStats() {
   summedBoosts->reset();
   for (Item * item : items) {
      summedBoosts->add(item->getBoost());
   }
   for (Weapon * weapon : weapons) {
      summedBoosts->add(weapon->getBoost());
   }
   /*summedBoosts->add(skillTree->getBoost());*/
}

float SpecialisedSquadMember::movement() const {
   return engine->parameters->BaseMovement + summedBoosts->addMovement;
}

int SpecialisedSquadMember::strength() const {
   return engine->parameters->BaseStrength + summedBoosts->addStrength;
}

int SpecialisedSquadMember::shooting() const {
   return engine->parameters->BaseShooting + summedBoosts->addShooting;
}

int SpecialisedSquadMember::armour() const {
   return engine->parameters->BaseArmour + summedBoosts->addArmour;
}

int SpecialisedSquadMember::morale() const {
   return engine->parameters->BaseMorale + summedBoosts->addMorale;
}

int SpecialisedSquadMember::health() const {
   return engine->parameters->BaseHealth + summedBoosts->addHealth;
}

int SpecialisedSquadMember::cost() const {
   return engine->parameters->BaseCost * summedBoosts->multiplyCost;
}

void SpecialisedSquadMember::checkValidity() const {
   CHECK(type() == SPECIALISEDSQUADMEMBER, engine);
   CHECK(experience >= 0, engine);
   CHECK(skillTree != nullptr, engine);
   /* something with skills? */
}
