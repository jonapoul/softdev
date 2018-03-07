#ifndef SQUADMEMBER_H
#define SQUADMEMBER_H

#include <string>
#include <vector>
#include "Game/GameObject.h"

class Squad;
class GameEngine;
class Player;

class SquadMember : public GameObject {
public:
   SquadMember(Squad * const s);
   ~SquadMember();

   virtual void checkValidity() const;

   virtual float movement() const;
   virtual int strength() const;
   virtual int shooting() const;
   virtual int armour() const;
   virtual int morale() const;
   virtual int health() const;
   virtual int cost() const;

protected:
   Squad * squad;
   GameEngine * engine;
   Player * player;
};

#endif
