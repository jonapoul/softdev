#include "pch.h"

#include "Die.h"
#include "functions.h"

Die::Die(int const Min,
         int const Max) {
   this->minValue = Min;
   this->maxValue = Max;
   ASSERT( Max > Min );
}

/* Seeds the generator on the first roll, then returns a value within the 
   specified range */
int Die::roll() const {
   static std::mt19937 generator;
   static std::uniform_int_distribution<> distribution;
   static bool hasBeenSeeded = false;
   if (!hasBeenSeeded) {
      std::random_device device;
      generator = std::mt19937(device());
      distribution = std::uniform_int_distribution<>(min(), max());
      hasBeenSeeded = true;
   }
   return distribution(generator);
}

int Die::min() const {
   return this->minValue;
}

int Die::max() const {
   return this->maxValue;
}

/* Generate a load of numbers and test their distribution */
void Die::testRandomness() const {
   namespace plt = matplotlibcpp;

   size_t const NumGenerated = 1000000;
   size_t const NumBins = max() - min();
   std::cout << "Testing die for uniform randomness between " << min()
             << " and " << max() << " over " << NumGenerated << " rolls:\n";

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

   /* Plot our histogram with overlaid lines for +/-sigma boundaries */
   std::vector<double> x = { min()-1.0, (double)max() };
   auto horiz = [](double const yval) { return std::vector<double>(2, yval); };
   plt::named_hist("Frequencies", Generated, NumBins, "b");
   plt::named_plot("Mean",   x, horiz(mean),         "r-");
   plt::named_plot("1sigma", x, horiz(mean+1*sigma), "c-");
   plt::plot(                x, horiz(mean-1*sigma), "c-");
   plt::named_plot("2sigma", x, horiz(mean+2*sigma), "g-");
   plt::plot(                x, horiz(mean-2*sigma), "g-");
   plt::named_plot("3sigma", x, horiz(mean+3*sigma), "y-");
   plt::plot(                x, horiz(mean-3*sigma), "y-");
   plt::legend();
   plt::ylim(mean-4*sigma, mean+4*sigma);
   plt::show();
}