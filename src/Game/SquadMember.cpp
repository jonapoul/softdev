#include "Game/SquadMember.h"
#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/GameParameters.h"

SquadMember::SquadMember(Squad * const s)
      : GameObject(SQUADMEMBER), squad(s), engine(s->engine), player(s->player) {
   /* TODO: Something*/
}

SquadMember::~SquadMember() {
   /* blank */
}

float SquadMember::movement() const {
   return engine->parameters->BaseMovement;
}

int SquadMember::strength() const {
   return engine->parameters->BaseStrength;
}

int SquadMember::shooting() const {
   return engine->parameters->BaseShooting;
}

int SquadMember::armour() const {
   return engine->parameters->BaseArmour;
}

int SquadMember::morale() const {
   return engine->parameters->BaseMorale;
}

int SquadMember::health() const {
   return engine->parameters->BaseHealth;
}

int SquadMember::cost() const {
   return engine->parameters->BaseCost;
}

void SquadMember::checkValidity() const {
   CHECK(type() == SQUADMEMBER, engine);
   CHECK(player != nullptr, engine);
   CHECK(squad  != nullptr, engine);
   CHECK(movement() > 0.0, engine);
   CHECK(strength() >= 0, engine);
   CHECK(shooting() >= 0, engine);
   CHECK(health() >= 0, engine);
   CHECK(armour() >= 0, engine);
   CHECK(morale() >= 0, engine);
   CHECK(cost() >= 0, engine);
}