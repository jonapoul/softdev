#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>

#define PRINT(x) std::cout<<__FILE__<<": "<<__LINE__<<": "<<#x<<" = "<<x<<std::endl;
#define ASSERT(check) Global::assert_impl(check, #check, __FILE__, __LINE__);
#define MIN(x,y) ((x<y)?x:y)
#define MAX(x,y) ((x>y)?x:y)
#define TO_STRING(x) std::string(#x)

namespace Global {

void assert_impl(bool const check,
                 char const * const call,
                 char const * const file,
                 int const line);

std::string encrypt(std::string msg,
                    std::string const& key);

std::string decrypt(std::string const& msg,
                    std::string const& key);

void trim(std::string * str);

size_t wordCount(char const * const str);
   
}

#endif