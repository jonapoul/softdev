#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <chrono>
#include <string>

#define PRINT(x) printf("%s: %03i: %s = %e\n",__FILE__,__LINE__,#x,(double)x);
#define ASSERT(check) assert_impl(check, #check, __FILE__, __LINE__);

void assert_impl(bool const check,
                 char const * const call,
                 char const * const file,
                 int const line);

std::string time_since(std::chrono::time_point<std::chrono::high_resolution_clock> start);

std::string encrypt(std::string msg,
                    std::string const& key);

std::string decrypt(std::string const& msg,
                    std::string const& key);

#endif