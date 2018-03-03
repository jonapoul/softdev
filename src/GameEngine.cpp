#include "GameEngine.h"
#include "Parameters.h"
#include "Die.h"

GameEngine::GameEngine() {
   this->parameters = new Parameters("data/parameters.input"/*, GAME_PARAMETERS*/);
   this->die        = new Die(parameters->MinRoll, parameters->MaxRoll);
}

GameEngine::~GameEngine() {
   delete this->parameters;
   delete this->die;
}