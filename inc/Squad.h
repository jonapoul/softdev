#ifndef __SQUAD_H__
#define __SQUAD_H__

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