#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstddef>
#include <vector>
#include <string>

#define ENSURE(statement,engine) GameObject::ensure(statement,#statement,__FILE__,__LINE__,engine)

class GameEngine;

typedef enum {
   NO_TYPE = 0,
   CAPTAIN,
   DIE,
   GAMEENGINE,
   GAMEOBJECT,
   GAMEPARAMETERS,
   HIEROPHANT,
   ITEM,
   PLAYER,
   SKILL,
   SKILLTREE,
   SPECIALISEDSQUADMEMBER,
   SQUAD,
   SQUADMEMBER,
   STATBOOST,
   WEAPON,
   NObjectTypes
} ObjectType;

class GameObject {

public:
   /* Only public so that the static functions can access it. There's
      almost certainly a better solution but this'll do */
   static std::vector<GameObject*> all_objects;

   GameObject(ObjectType const t);

   /**** these are not used, so i'm removing the risk of implicit calling ****/
   GameObject() = delete;
   GameObject(GameObject const& other) = delete;
   GameObject& operator=(GameObject const& other) = delete;
   /**************************************************************************/

   virtual ~GameObject();

   size_t ID() const;
   ObjectType type() const;
   void deallocate();
   void setType(ObjectType const t);
   std::string typeToString() const;
   virtual void ensureValidity() const;
   virtual void print() const;

   static std::string typeToString(ObjectType const t);
   static void printAllObjects();
   static size_t numberOfType(ObjectType const t);
   static void ensureEverythingIsValid();

   /* only called through the macro ENSURE at the top of this file */
   static void ensure(bool const statement,
                      char const * const string,
                      char const * const function,
                      int const line,
                      GameEngine const * const engine);

private:
   size_t id_;
   ObjectType type_;

   static size_t id_running_counter;
};

#endif
