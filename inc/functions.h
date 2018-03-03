#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#define PRINT(x) printf("%s: %03i: %s = %e\n",__FILE__,__LINE__,#x,(double)x);
#define ASSERT(check) assert_impl(check, #check, __FILE__, __LINE__);
#define MIN(x,y) ((x<y)?x:y)
#define MAX(x,y) ((x>y)?x:y)

void assert_impl(bool const check,
                 char const * const call,
                 char const * const file,
                 int const line);

std::string encrypt(std::string msg,
                    std::string const& key);

std::string decrypt(std::string const& msg,
                    std::string const& key);

#endif