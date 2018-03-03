#include "Game/GameEngine.h"
#include "Game/GameParameters.h"
#include "Game/Die.h"

GameEngine::GameEngine() {
   this->parameters = new GameParameters("data/parameters.input");
   this->die        = new Die(parameters->MinRoll, parameters->MaxRoll);
}

GameEngine::~GameEngine() {
   delete this->parameters;
   delete this->die;
}