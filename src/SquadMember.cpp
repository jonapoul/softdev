#include "Game/SquadMember.h"
#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/GameParameters.h"
#include "Global.h"

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

void SquadMember::ensureValidity() const {
   ENSURE(type() == SQUADMEMBER, engine);
   ENSURE(player != nullptr,     engine);
   ENSURE(squad != nullptr,      engine);
   ENSURE(movement() > 0.0,      engine);
   ENSURE(strength() >= 0,       engine);
   ENSURE(shooting() >= 0,       engine);
   ENSURE(health() >= 0,         engine);
   ENSURE(armour() >= 0,         engine);
   ENSURE(morale() >= 0,         engine);
   ENSURE(cost() >= 0,           engine);
}

void SquadMember::print() const {
   GameObject::print();
   printf("SquadMember:\n");
   printf("   engine = %p, ID = %zu\n", engine, engine->ID());
   printf("   player = %p, ID = %zu\n", player, player->ID());
   printf("   squad  = %p, ID = %zu\n", squad, squad->ID());
}