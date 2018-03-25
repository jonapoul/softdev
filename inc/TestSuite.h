#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <vector>
#include <string>

class GameEngine;
class TestSuite;

/* for taking user input */
typedef struct { 
   unsigned char key;
   std::string desc;
   void (*func)(void);
} InputOption;

class TestSuite {
public:
   TestSuite(GameEngine * e);
   void run();

   InputOption matchInputOption(char const key);
};

#endif