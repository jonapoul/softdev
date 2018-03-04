#include "Game/Captain.h"
#include "Game/GameEngine.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"

Captain::Captain(GameEngine * const e,
                 Player * const p,
                 Squad * const s,
                 char ** skillsStr,
                 size_t const Nskills,
                 char ** itemsStr,
                 size_t const Nitems,
                 char ** weaponsStr,
                 size_t const NWeapons)
      : SquadMember(e, p, s) {

   /* TODO: something */
}

Captain::~Captain() {
   /* Delete skills? */
}