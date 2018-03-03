#ifndef SQUAD_H
#define SQUAD_H

#include <vector>
class Captain;
class Hierophant;
class SquadMember;

class Squad {
public:
   Squad();

private:
   Captain * captain;
   Hierophant * hierophant;
   std::vector<SquadMember> squad_members;
};

#endif