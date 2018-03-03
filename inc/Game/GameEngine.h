#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameParameters;
class Die;

class GameEngine {
public:
   GameEngine();
   ~GameEngine();

private:
   Die * die;
   GameParameters * parameters;
};

#endif

