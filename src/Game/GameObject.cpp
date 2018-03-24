#include "Game/GameObject.h"
#include "Game/GameEngine.h"

size_t GameObject::id_running_counter = 0;
std::vector<GameObject*> GameObject::all_objects = {};

/* Force the user to pass a ObjectType enum value as part of the constructor.
   This helps with debugging things like memory leaks, etc. */
GameObject::GameObject(ObjectType const t)
      : id_(GameObject::id_running_counter), type_(t) {
   GameObject::id_running_counter++;
   GameObject::all_objects.push_back(this);
}

GameObject::~GameObject() {
   /* blank, nothing to delete */
}

size_t GameObject::ID() const {
   return this->id_;
}

ObjectType GameObject::type() const {
   return this->type_;
}

void GameObject::setType(ObjectType const t) {
   this->type_ = t;
}

void GameObject::deallocate() {
   for (size_t i = 0; i < GameObject::all_objects.size(); i++) {
      if (GameObject::all_objects[i]->ID() == this->ID()) {
         auto start = GameObject::all_objects.begin();
         GameObject::all_objects.erase(start + i);
         break;
      }
   }
   delete this; // NEPHEW
}

void GameObject::ensureValidity() const {
   /* blank, we don't have a GameEngine to reference */
}

/* Dump info about every GameObject currently in memory, in the order that they
   were created */
void GameObject::printAllObjects() {
   printf("%s\n", std::string(50, '-').c_str());
   printf("%15s %10s %15s\n", "Address", "ID", "Type");
   printf("%s\n", std::string(50, '-').c_str());
   for (GameObject* o : GameObject::all_objects) {
      printf("%15p %10zu %15s\n", o, o->ID(), o->typeToString().c_str());
   }
   printf("%s\n", std::string(50, '-').c_str());
}

/* Used for debugging and printAllObjects() */
std::string GameObject::typeToString() const {
   switch (this->type()) {
      case NO_TYPE:                return "NO_TYPE";
      case CAPTAIN:                return "CAPTAIN";
      case DIE:                    return "DIE";
      case GAMEENGINE:             return "GAMEENGINE";
      case GAMEOBJECT:             return "GAMEOBJECT";
      case GAMEPARAMETERS:         return "GAMEPARAMETERS";
      case HIEROPHANT:             return "HIEROPHANT";
      case ITEM:                   return "ITEM";
      case PLAYER:                 return "PLAYER";
      case SKILL:                  return "SKILL";
      case SKILLTREE:              return "SKILLTREE";
      case SPECIALISEDSQUADMEMBER: return "SPECIALISEDSQUADMEMBER";
      case SQUAD:                  return "SQUAD";
      case SQUADMEMBER:            return "SQUADMEMBER";
      case STATBOOST:              return "STATBOOST";
      case WEAPON:                 return "WEAPON";
      default:                     return "UNKNOWN";
   }
}

/* Return a vector of all objects with a given type.
     e.g.
       auto array = getAllOfType(PLAYER)
   returns pointers to all Player objects. It's up to the user to cast them to
   Player*.
*/
std::vector<GameObject*> GameObject::getAllOfType(ObjectType const t) {
   std::vector<GameObject*> result;
   for (GameObject* object : GameObject::all_objects) {
      if (object->type() == t) result.push_back(object);
   }
   return result;
}

/* Return a vector of all objects that belong to the given array of types..
     e.g.
       auto array = getAllOfTypes({PLAYER, SQUAD, ENGINE})
   returns pointers to all Player objects, all Squad objects and all Engine
   objects. It's up to the user to cast them correctly, using the pointer's 
   type() function
*/
std::vector<GameObject*> GameObject::getAllOfTypes(std::vector<ObjectType> const& types) {
   std::vector<GameObject*> result;
   for (GameObject* object : GameObject::all_objects) {
      for (ObjectType t : types) {
         if (object->type() == t) {
            result.push_back(object);
            break;
         }
      }
   }
   return result;
}

/* Pass enum representing a derived class, and return how many of that type
   currently exist in memory */
size_t GameObject::numberOfType(ObjectType const t) {
   size_t count = 0;
   for (GameObject* object : GameObject::all_objects) {
      if (object->type() == t) count++;
   }
   return count;
}

/* Go through every registered object and make sure nothing is invalid */
void GameObject::ensureEverythingIsValid() {
   for (GameObject* object : GameObject::all_objects) {
      object->ensureValidity();
   }
}

/* Make sure the passed boolean statement evaluates to true, and if not send
   a warning to the game engine. It'll pass a message to the user (via either
   UI or CLI) showing what failed and where */
void GameObject::ensure(bool const statement,
                       char const * const statementString,
                       char const * const className,
                       GameEngine const * const engine) {
   if (!statement) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "FAILED CHECK:\n"
               "    Statement: '%s'\n"
               "    Location:  '%s'", 
               statementString, className);
      engine->warningMessage(warningbuf);
   }
}