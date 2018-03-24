#include <chrono>
#include <sstream>

#include "Global.h"

void Global::assert_impl(bool const check,
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

std::string Global::encrypt(std::string msg, 
                            std::string const& key) {
   if (key.empty()) return msg;
   for (size_t i = 0; i < msg.length(); i++)
      msg[i] ^= key[i % key.length()];
   return msg;
}

std::string Global::decrypt(std::string const& msg, 
                            std::string const& key) {
   return encrypt(msg, key);
}

void Global::trim(std::string * str) {
   while ( (*str)[0] == ' ' ) {
      str->erase(str->begin() + 0);
   }
   while ( (*str)[str->length()-1] == ' ' ) {
      str->erase(str->begin() + str->length() - 1);
   }
}

size_t Global::wordCount(char const * const str) {
   return Global::wordCount(std::string(str));
}

size_t Global::wordCount(std::string const& str) {
   size_t count = 0;
   std::stringstream ss(str);
   std::string word;
   while (ss >> word) {
      count++;
   }
   return count;
}
