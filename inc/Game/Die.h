#ifndef DIE_H
#define DIE_H

class Die {
public:
   Die(int const minValue, int const maxValue);
   int roll() const;
   int max() const;
   int min() const;
   void testRandomness() const;

private:
   int maxValue;
   int minValue;
};

#endif