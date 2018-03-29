#include <iostream>
#include <algorithm>

#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "Global.h"

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

/* Instead of just 'delete'ing each pointer when we're done with them, always
   pass it this function instead so that it gets removed from the all_objects
   array */
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
   /* blank, we don't have anything to check */
}

void GameObject::print() const {
   printf("GameObject:\n");
   printf("   ID   = %lu\n", this->ID());
   printf("   Type = '%s'\n", this->typeToString().c_str());
}

/* Dump info about every GameObject currently in memory, in the order that they
   were created */
void GameObject::printAllObjects() {
   while (true) {
      printf("%s\n", std::string(50, '-').c_str());
      printf("%15s %10s %15s\n", "Address", "ID", "Type");
      printf("%s\n", std::string(50, '-').c_str());
      for (GameObject* o : GameObject::all_objects) {
         printf("%15p %10zu %15s\n", o, o->ID(), o->typeToString().c_str());
      }
      if (GameObject::all_objects.size() == 0) {
         printf("    No objects currently exist!\n");
         printf("%s\n", std::string(50, '-').c_str());
         return;
      }
      printf("%s\n", std::string(50, '-').c_str());

      while (true) {
         printf("Enter an object ID (q = back to testing menu, p = print, h = help, s = sort):\n");
         std::string input;
         std::cin >> input;
         char letter = tolower(input[0]);
         if (letter == 'q') {
            return;
         } else if (letter == 'p') {
            break;
         } else if (letter == 'h') {
            printf("Each line in the list above represents a GameObject-derived object that\n"
                   "is currently in memory, along with its unique ID number and class name.\n"
                   "Typing that ID number in here will print more info about that object,\n"
                   "with member variables and the ID numbers of any pointers. Using this you\n"
                   "can keep track of memory allocation and the state of the system at any\n"
                   "time just by shoving a call to GameObject::printAllObjects() in the\n"
                   "code. For example, if you create a player as part of the tests, you'll\n"
                   "then see a PLAYER object at the bottom of this list.\n");
            continue;
         } else if (letter == 's') {
            /* This could probably have been structured better but I was in a
               rush, sorry! */
            typedef enum { byID, byType } SortType;
            static SortType sortMethod = byID;
            static auto sortByID   = [](GameObject* a, GameObject* b) { return a->ID()   < b->ID(); };
            static auto sortByType = [](GameObject* a, GameObject* b) { return a->type() < b->type(); };
            if (sortMethod == byID) {
               std::sort(GameObject::all_objects.begin(),
                         GameObject::all_objects.end(),
                         sortByType);
               sortMethod = byType;
            } else { /* sortMethod == byType */
               std::sort(GameObject::all_objects.begin(),
                         GameObject::all_objects.end(),
                         sortByID);
               sortMethod = byID;
            }
            break;
         }
         if (!isdigit(input[0])) {
            printf("Enter a number or q/p/s/h:\n");
            continue;
         }
         size_t id = std::stoi(input);
         for (GameObject* o : GameObject::all_objects) {
            if (id == o->ID()) {
               o->print();
               printf("\n");
               break;
            }
         } // loop over objects
      } // second while true
   } // first while true
}

/* Static function to make it available without a GameObject to reference */
std::string GameObject::typeToString(ObjectType const t) {
   GameObject temp(t);
   return temp.typeToString();
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

/* Pass enum representing a derived class, and return how many of that type
   currently exist in memory */
size_t GameObject::numberOfType(ObjectType const t) {
   size_t count = 0;
   for (GameObject* object : GameObject::all_objects) {
      if (object->type() == t) count++;
   }
   return count;
}

/* Go through every registered object and make sure nothing is broken */
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
                       char const * const function,
                       int const line,
                       GameEngine const * const engine) {
   if (!statement) {
      char warningbuf[MAX_MESSAGE_LENGTH];
      snprintf(warningbuf, MAX_MESSAGE_LENGTH,
               "FAILED CHECK:\n"
               "    Statement: '%s'\n"
               "    File:      '%s'\n"
               "    Line:       %d\n",
               statementString, function);
      engine->warningMessage(warningbuf);
   }
}
