#include "Game/GameObject.h"
#include "Game/GameEngine.h"

size_t GameObject::id_running_counter = 0;
std::vector<GameObject*> GameObject::all_objects = {};

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

void GameObject::checkValidity() const {
   /* blank, we don't have a GameEngine to reference */
}

void GameObject::printAllObjects() {
   printf("%s\n", std::string(55, '-').c_str());
   printf("%15s %10s %15s %6s\n", "Address", "ID", "Type", "Size");
   printf("%s\n", std::string(55, '-').c_str());
   for (GameObject* o : GameObject::all_objects) {
      printf("%15p %10zu %15s %6zu\n", o, o->ID(), o->typeToString().c_str(), sizeof(*o));
   }
   printf("%s\n", std::string(55, '-').c_str());
}

std::string GameObject::typeToString() const {
   switch (this->type()) {
      case NO_TYPE:        return "NO_TYPE";
      case CAPTAIN:        return "CAPTAIN";
      case DIE:            return "DIE";
      case GAMEENGINE:     return "GAMEENGINE";
      case GAMEOBJECT:     return "GAMEOBJECT";
      case GAMEPARAMETERS: return "GAMEPARAMETERS";
      case HIEROPHANT:     return "HIEROPHANT";
      case PLAYER:         return "PLAYER";
      case SKILL:          return "SKILL";
      case SKILLTREE:      return "SKILLTREE";
      case SQUAD:          return "SQUAD";
      case SQUADMEMBER:    return "SQUADMEMBER";
      default:             return "UNKNOWN";
   }
}

std::vector<GameObject*> GameObject::getAllOfType(ObjectType const t) {
   std::vector<GameObject*> result;
   for (GameObject* object : GameObject::all_objects) {
      if (object->type() == t) result.push_back(object);
   }
   return result;
}

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

size_t GameObject::numberOfType(ObjectType const t) {
   size_t count = 0;
   for (GameObject* object : GameObject::all_objects) {
      if (object->type() == t) count++;
   }
   return count;
}

void GameObject::checkEverythingIsValid() {
   for (GameObject* object : GameObject::all_objects) {
      object->checkValidity();
   }
}

void GameObject::check(bool const statement,
                       char const * const string,
                       char const * const Class,
                       GameEngine const * const engine) {
   if (!statement) {
      char checkbuf[MAX_MESSAGE_LENGTH];
      snprintf(checkbuf, MAX_MESSAGE_LENGTH,
               "Failed check '%s' in class '%s'", string, Class);
      engine->warningMessage(checkbuf);
   }
}