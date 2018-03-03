#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <vector>
class Skill;

class SkillTree {
public:
   SkillTree();

private:
   std::vector<Skill> skills;
};

#endif
