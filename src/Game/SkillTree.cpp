#include "Game/SkillTree.h"
#include "Game/Skill.h"

SkillTree::SkillTree(GameEngine * const e,
                     SquadMember * const s)
      : GameObject(), engine(e), squadmember(s) {
   this->setType(SKILLTREE);

}

void SkillTree::checkValidity() const {
   CHECK(skillTreeClass != NoSkillTreeClass, engine);
}