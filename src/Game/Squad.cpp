#include "Game/GameEngine.h"
#include "Game/Player.h"
#include "Game/Squad.h"
#include "Game/Captain.h"
#include "Game/Hierophant.h"
#include "Game/SquadMember.h"

#include "functions.h"

Squad::Squad(GameEngine * const e,
             Player * const p,
             char const * const filename,
             bool * const squadFileIsValid)
      : engine(e), player(p) {
   char buf[256];
   snprintf(buf, 256, "Building squad from '%s'", filename);
   e->informationMessage(buf);

   if ( *squadFileIsValid == false ) {
      return;
   }
}