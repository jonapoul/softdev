#include "Game/SquadMember.h"
#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"

SquadMember::SquadMember(Squad * const s)
      : GameObject(SQUADMEMBER), squad(s), engine(s->engine), player(s->player) {
   /* TODO: Something*/
}

void SquadMember::checkValidity() const {
   CHECK(engine == nullptr, engine);
   CHECK(player == nullptr, engine);
   CHECK(squad == nullptr, engine);
}