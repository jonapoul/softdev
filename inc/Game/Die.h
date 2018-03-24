#ifndef DIE_H
#define DIE_H

#include <random>
#include "Game/GameObject.h"

class GameEngine;

class Die : public GameObject {
public:
   Die(int const minValue,
       int const maxValue,
       GameEngine * const e);
   ~Die();

   int roll() const;
   int maxRoll() const;
   int minRoll() const;
   virtual void ensureValidity() const;
   virtual void print() const;

   void testRandomness() const; /* debugging */

private:
   GameEngine * engine;
   int maxValue;
   int minValue;

   std::random_device * device;
   std::mt19937 * generator;
   std::uniform_int_distribution<> * distribution;
};

#endif