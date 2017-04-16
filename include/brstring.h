/*
 * =====================================================================================
 *
 *       Filename:  brstring.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2017 03:29:17 PM
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

#include "branch.h"

char *brToString(branch *br);

branch *brFromString(char *s);

#endif BRSTRING_H
