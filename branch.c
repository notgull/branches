/*
 * =====================================================================================
 *
 *       Filename:  branch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:28:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "branch.h"

branch *brCreate(char *b1, char *b2, char *txt) {
  branch br = {0,0,b1,b2,txt};
  return &br;
}

int brHasBranch1(branch *br) {
  return br->hasB1;
}

int brHasBranch2(branch *br) {
  return br->hasB2;
}


