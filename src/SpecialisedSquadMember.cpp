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
   this->totalBoost = new StatBoost(engine); /* blank, all default values */
   this->skillTree  = new SkillTree(engine, this); /* blank, no skills active */
}

SpecialisedSquadMember::~SpecialisedSquadMember() {
   skillTree->deallocate();
   totalBoost->deallocate();
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
   /* CONTINUE */
}

void SpecialisedSquadMember::initItems(char ** itemsStr,
                                       size_t const nItems) {
   for (size_t iItem = 0; iItem < nItems; iItem++) {
      Item * item = new Item(this, engine);
      bool const isValid = item->init(itemsStr[iItem]);
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
      Weapon * weapon = new Weapon(this, engine);
      bool const isValid = weapon->init(weaponsStr[iWeapon]);
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
   this->totalBoost->reset();
   for (Item * item : items) {
      this->totalBoost->add( item->getBoost() );
   }
   for (Weapon * weapon : weapons) {
      this->totalBoost->add( weapon->getBoost() );
   }
   this->totalBoost->add( skillTree->summedBoosts() );
}

float SpecialisedSquadMember::movement() const {
   return engine->parameters->BaseMovement + totalBoost->addMovement;
}

int SpecialisedSquadMember::strength() const {
   return engine->parameters->BaseStrength + totalBoost->addStrength;
}

int SpecialisedSquadMember::shooting() const {
   return engine->parameters->BaseShooting + totalBoost->addShooting;
}

int SpecialisedSquadMember::armour() const {
   return engine->parameters->BaseArmour + totalBoost->addArmour;
}

int SpecialisedSquadMember::morale() const {
   return engine->parameters->BaseMorale + totalBoost->addMorale;
}

int SpecialisedSquadMember::health() const {
   return engine->parameters->BaseHealth + totalBoost->addHealth;
}

int SpecialisedSquadMember::cost() const {
   return engine->parameters->BaseCost * totalBoost->multiplyCost;
}

void SpecialisedSquadMember::ensureValidity() const {
   ENSURE(type() == SPECIALISEDSQUADMEMBER, engine);
   ENSURE(experience >= 0, engine);
   ENSURE(skillTree != nullptr, engine);
   /* something with skills? */
}
