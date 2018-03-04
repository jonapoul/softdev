#include "Game/Hierophant.h"
#include "Game/SquadMember.h"
#include "Game/Skill.h"
#include "Game/SkillTree.h"

Hierophant::Hierophant(GameEngine * const e,
                       Player * const p,
                       Squad * const s,
                       char ** skillsStr,
                       size_t const Nskills,
                       char ** itemsStr,
                       size_t const Nitems,
                       char ** weaponsStr,
                       size_t const NWeapons)
      : SquadMember(e, p, s) {
   /* TODO: Something */
}

Hierophant::~Hierophant() {
   /* Delete skills? */
}