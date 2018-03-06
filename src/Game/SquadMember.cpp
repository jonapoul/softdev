#include "Game/SquadMember.h"
#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"

SquadMember::SquadMember(GameEngine * const e,
                         Player * const p,
                         Squad * const s)
      : GameObject(SQUADMEMBER), engine(e), player(p), squad(s) {
   /* TODO: Something*/
}

void SquadMember::checkValidity() const {
   CHECK(engine == nullptr, engine);
   CHECK(player == nullptr, engine);
   CHECK(squad == nullptr, engine);
}