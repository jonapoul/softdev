#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstddef>
#include <vector>
#include <string>

#define ENSURE(statement,engine) GameObject::ensure(statement,#statement,typeid(*this).name(),engine)

class GameEngine;

typedef enum {
   NO_TYPE,
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
   virtual ~GameObject();

   size_t ID() const;
   ObjectType type() const;
   void deallocate();
   void setType(ObjectType const t);
   virtual void ensureValidity() const;
   virtual void print() const;

   static void printAllObjects();
   static std::vector<GameObject*> getAllOfType(ObjectType const t);
   static std::vector<GameObject*> getAllOfTypes(std::vector<ObjectType> const& types);
   static size_t numberOfType(ObjectType const t);
   static void ensureEverythingIsValid();
   static void ensure(bool const statement,
                      char const * const string,
                      char const * const Class,
                      GameEngine const * const engine);

private:
   std::string typeToString() const;

   size_t id_;
   ObjectType type_;

   static size_t id_running_counter;
};

#endif
