#include "Game/Captain.h"
#include "Game/GameObject.h"
#include "Game/Squad.h"
#include "Game/GameEngine.h"
#include "Game/SkillTree.h"
#include "Game/Skill.h"

Captain::Captain(GameEngine * const e,
                 Player * const p,
                 Squad * const s)
      : SquadMember(e, p, s), specialism(NoCaptainSpecialism) {
   this->setType(CAPTAIN);
   /* TODO: something */
}

Captain::~Captain() {
   /* Delete skills? */
}

void Captain::initSkills(char ** skillsStr,
                         size_t const Nskills) {
   /* something */
}

void Captain::initItems(char ** itemsStr,
                        size_t const Nitems) {
   /* something */
}

void Captain::initWeapons(char ** weaponsStr,
                          size_t const NWeapons) {
   /* something */
}

void Captain::checkValidity() const {
   CHECK(experience >= 0, engine);
   CHECK(specialism != NoCaptainSpecialism, engine);
   /* something with skills? */
}