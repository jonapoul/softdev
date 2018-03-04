#include <chrono>
#include <sstream>

#include "functions.h"

void assert_impl(bool const check,
                 char const * const call,
                 char const * const file,
                 int const line) {
   if (!check) {
      printf("---------------- ASSERT FAILED ----------------\n");
      printf("    Check = %s\n", call);
      printf("    File  = %s\n", file);
      printf("    Line  = %i\n", line);
      exit(1);
   }
}

std::string encrypt(std::string msg, 
                    std::string const& key) {
   if (key.empty()) return msg;
   for (size_t i = 0; i < msg.length(); i++)
      msg[i] ^= key[i % key.length()];
   return msg;
}

std::string decrypt(std::string const& msg, 
                    std::string const& key) {
   return encrypt(msg, key);
}

void freeArrayOfCStrings(char ** array,
                         size_t const nElements) {
   for (size_t i = 0; i < nElements; i++) {
      free(array[i]);
   }
   free(array);
}

void trim(std::string * str) {
   while ( (*str)[0] == ' ' ) {
      str->erase(str->begin() + 0);
   }
   while ( (*str)[str->length()-1] == ' ' ) {
      str->erase(str->begin() + str->length() - 1);
   }
}