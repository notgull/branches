/*
 * =====================================================================================
 *
 *       Filename:  str-to-ptr.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/2017 03:22:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef STR-TO-PTR-HPP
#define STR-TO-PTR-HPP

#include <string>

char *getPointerFrom(std::string str);
std::string getStringFrom(char *str);

extern "C" {
  char *getAllLinesFromFile(char *filename);
}

#endif
