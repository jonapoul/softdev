#ifndef __GAME_H__
#define __GAME_H__

class Parameters;
class Die;

class Game {
public:
   Game();
   ~Game();
   bool run();

private:
   Die * die;
   Parameters * parameters;
};

#endif

