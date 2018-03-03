#ifndef __GAME_H__
#define __GAME_H__

class Parameters;
class Die;

class GameEngine {
public:
   GameEngine();
   ~GameEngine();

private:
   Die * die;
   Parameters * parameters;
};

#endif

