#ifndef __SKILLTREE_H__
#define __SKILLTREE_H__

class Skill;

class SkillTree {
public:
   SkillTree();

private:
   std::vector<Skill> skills;
};

#endif
