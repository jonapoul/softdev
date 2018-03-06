#include "Game/SkillTree.h"
#include "Game/Skill.h"

SkillTree::SkillTree(GameEngine * const e,
                     SquadMember * const s)
      : GameObject(SKILLTREE), engine(e), squadmember(s) {

}

void SkillTree::checkValidity() const {
   CHECK(skillTreeClass != NoSkillTreeClass, engine);
}