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
#include "shortcuts.h"
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
int nextUuid = 0;
#endif

#define true 1
#define false 0

branch *brCreate(char *b1, char *b2, char *txt) {
  branch *br = malloc(sizeof(branch));
  br->b1 = strdup(b1);
  br->b2 = strdup(b2);
  br->txt = strdup(txt);
  br->branch1 = NULL;
  br->branch2 = NULL;
#ifdef DEBUG
  nextUuid = nextUuid + 1;
  br->uuid = nextUuid;
#endif
  return br;
}

int brHasBranch1(branch *br) {
  if (br->branch1)
    return true;
  return false;
}

int brHasBranch2(branch *br) {
  if (br->branch2)
    return true;
  return false;
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
//  br->hasB1 = 1;
  return 1;
}

int brSetBranch2(branch *br, branch *value) {
  if (br->branch2)
    return 0;
  br->branch2 = value;
//  br->hasB2 = 1;
  return 1;
}

void brPrint(branch *br) {
  puts(br->txt);
  printf("Option 1: %s\n",br->b1);
  printf("Option 2: %s\n",br->b2);
  newline();
}

#ifdef DEBUG
int brGetUUID(branch *br) {
  return br->uuid;
}
#endif

void brRelease(branch *br) {
  if (br) {
    if (br->branch1)
      brRelease(br->branch1);
    if (br->branch2)
      brRelease(br->branch2);
    if (br->b1);
      free(br->b1);
    if (br->b2)
      free(br->b2);
    if (br->txt)
      free(br->txt);
    free(br);
  }
}
