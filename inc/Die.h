#ifndef __DIE_H__
#define __DIE_H__

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