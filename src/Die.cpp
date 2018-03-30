#include <iostream>
#include <vector>
#include <numeric>

#include "Game/Die.h"
#include "Game/GameEngine.h"
#include "Game/GameObject.h"
#include "Global.h"

Die::Die(GameEngine * const e)
      : GameObject(DIE), engine(e) {
   /* blank */
}

Die::~Die() {
   delete device;
   delete generator;
   delete distribution;
}

bool Die::init(int const Min,
               int const Max) {
   this->minValue = Min;
   this->maxValue = Max;

   /* initialise the mersenne-twister int generator */
   this->device       = new std::random_device;
   this->generator    = new std::mt19937( (*device)() );
   this->distribution = new std::uniform_int_distribution<>(minRoll(), maxRoll());
   return true;
}

int Die::roll() const {
   return (*distribution)(*generator);
}

int Die::minRoll() const {
   return this->minValue;
}

int Die::maxRoll() const {
   return this->maxValue;
}

void Die::ensureValidity() const {
   ENSURE(type() == DIE, engine);
   ENSURE(minValue < maxValue, engine);
   GameObject::ensureValidity();
}

void Die::print() const {
   GameObject::print();
   printf("Die:\n");
   printf("   engine   = %p, ID = %lu\n", engine, engine->ID());
   printf("   minValue = %d\n", minValue);
   printf("   maxValue = %d\n", maxValue);
}

/* Generate a load of numbers and test their distribution. Don't know why I
   even bothered doing this, really. Call it pseudo-procrastination. */
void Die::testRandomness() const {
   size_t const NumGenerated = 1000000;
   size_t const NumBins = maxRoll() - minRoll();
   std::cout << "Testing die for uniform randomness between " << minRoll()
             << " and " << maxRoll() << " over " << NumGenerated << " rolls:\n";

   /* Generate the numbers */
   std::vector<size_t> Frequencies(NumBins, 0);
   std::vector<size_t> Generated(NumGenerated);
   for (size_t i = 0; i < NumGenerated; i++) {
      Generated[i] = roll();
      Frequencies[ Generated[i]-1 ]++;
   }
   /* Determine the standard deviation of the distributed numbers */
   double const mean = std::accumulate(Frequencies.begin(), Frequencies.end(), 0.0)
                       / (double)Frequencies.size();
   double sigma = 0.0;
   for (auto F : Frequencies) {
      sigma +=   ((double)F - mean)
               * ((double)F - mean)
               / (double)(NumBins - 1);
   }
   sigma = sqrt(sigma);

   /* Check how many numbers lie in each range */
   size_t within1Sigma = 0, within2Sigma = 0, within3Sigma = 0;
   for (size_t i = 0; i < NumBins; i++) {
      double const distance = abs((double)Frequencies[i] - mean) / sigma;
      if (distance < 1) within1Sigma++;
      if (distance < 2) within2Sigma++;
      if (distance < 3) within3Sigma++;
   }
   printf("Within 1σ = %f%%, should be 68.27%%\n", 100*(double)within1Sigma/(double)NumBins);
   printf("Within 2σ = %f%%, should be 95.45%%\n", 100*(double)within2Sigma/(double)NumBins);
   printf("Within 3σ = %f%%, should be 99.74%%\n", 100*(double)within3Sigma/(double)NumBins);
}