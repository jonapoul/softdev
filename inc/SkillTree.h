#ifndef __SKILLTREE_H__
#define __SKILLTREE_H__

#include <vector>
class Skill;

class SkillTree {
public:
   SkillTree();

private:
   std::vector<Skill> skills;
};

#endif
