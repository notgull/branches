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
#include "err.h"
#include <stdio.h>

branch *brCreate(char *b1, char *b2, char *txt) {
  branch br = {0,0,b1,b2,txt,NULL,NULL};
  return &br;
}

int brHasBranch1(branch *br) {
  return br->hasB1;
}

int brHasBranch2(branch *br) {
  return br->hasB2;
}

char *brGetBranch1Text(branch *br) {
  return br->b1;
}

char *brGetBranch2Text(branch *br) {
  return br->b2;
}

char *brGetText(branch *br) {
  return br->txt;
}

branch *brGetBranch1(branch *br) {
  if (!(br->branch1))
  {
    error("Attempted to access null branch",0);
  }
  return br->branch1;
}

branch *brGetBranch2(branch *br) {
  if (!(br->branch2))
  {
    error("Attempted to access null branch",0);
  }
  return br->branch2;
}

int brSetBranch1(branch *br, branch *value) {
  if (br->branch1)
    return 0;
  br->branch1 = value;
  return 1;
}

int brSetBranch2(branch *br, branch *value) {
  if (br->branch2)
    return 0;
  br->branch2 = value;
  return 1;
}
