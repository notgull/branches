/*
 * =====================================================================================
 *
 *       Filename:  brstring.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/2017 03:51:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef BRSTRING_H
#define BRSTRING_H

extern "C" {
  #include "branch.h"

  branch *brFromString(char *str);
  char *brToString(branch *br);
}

#endif
