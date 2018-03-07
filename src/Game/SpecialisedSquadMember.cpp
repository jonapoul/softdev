#include "Game/SpecialisedSquadMember.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/SkillTree.h"
#include "Game/Weapon.h"
#include "Game/Item.h"

SpecialisedSquadMember::SpecialisedSquadMember(Squad * const s)
      : SquadMember(s), experience(0) {
   this->setType(SPECIALISEDSQUADMEMBER);
}

SpecialisedSquadMember::~SpecialisedSquadMember() {
   this->skillTree->deallocate();
   for (Weapon * w : this->weapons) {
      w->deallocate();
   }
   for (Item * i : this->items) {
      i->deallocate();
   }
}

void SpecialisedSquadMember::initSkills(char ** skillsStr,
                                        size_t const nSkills) {
   /* something */
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

void SpecialisedSquadMember::checkValidity() const {
   CHECK(experience >= 0, engine);
   CHECK(skillTree != nullptr, engine);
   /* something with skills? */
}