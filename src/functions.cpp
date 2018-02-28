#include "pch.h"

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

std::string time_since(std::chrono::time_point<std::chrono::high_resolution_clock> start) {
   auto end = std::chrono::high_resolution_clock::now();
   auto secs = std::chrono::duration_cast<std::chrono::seconds>( end - start );
   int const TotalSeconds = static_cast<int>( secs.count() );
   int const NumHours =  TotalSeconds / 60 / 60;
   int const NumMins  = (TotalSeconds / 60) % 60;
   int const NumSecs  =  TotalSeconds % 60;
   std::stringstream ss;
   ss << NumHours << "h " << NumMins << "m " << NumSecs << "s";
   return ss.str();
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