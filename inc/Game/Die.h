#ifndef DIE_H
#define DIE_H

#include "Game/GameObject.h"

class GameEngine;

class Die : public GameObject {
public:
   Die(int const minValue,
       int const maxValue,
       GameEngine * const e);
   int roll() const;
   int maxRoll() const;
   int minRoll() const;
   virtual void checkValidity() const;

   void testRandomness() const; /* debugging */

private:
   GameEngine * engine;
   int maxValue;
   int minValue;
};

#endif