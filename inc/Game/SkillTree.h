#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <vector>
#include <string>

class Skill;

typedef enum {
   HierophantSkillTreeClass,
   CaptainSkillTreeClass,
   NumSkillTreeClasses
} SkillTreeClass;

class SkillTree {
public:
   SkillTree();

private:
   std::string name;
   SkillTreeClass skillTreeClass;
   int specialism; /* Either HierophantSpecialism or CaptainSpecialism enum */
   std::vector<Skill *> skills;
};

#endif
