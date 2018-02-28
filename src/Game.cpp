#include "pch.h"

#include "Game.h"
#include "Parameters.h"
#include "Die.h"

Game::Game() {
   this->parameters = new Parameters("data/parameters.input");
   this->die = new Die(parameters->MinRoll, parameters->MaxRoll);
}

Game::~Game() {
   delete this->parameters;
   delete this->die;
}

bool Game::run() {
   return true;
}