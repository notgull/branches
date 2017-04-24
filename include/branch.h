/*
 * =====================================================================================
 *
 *       Filename:  branch.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:27:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef BRANCH_H
#define BRANCH_H

typedef struct br_struct {
  const char *b1;
  const char *b2;
  const char *txt;
  struct br_struct *branch1;
  struct br_struct *branch2;
  struct br_struct *prev;
#ifdef DEBUG
  int uuid;
#endif
} branch;

branch *brCreate(char *b1, char *b2, char *txt);

int brHasBranch1(branch *br);

int brHasBranch2(branch *br);

char *brGetBranch1Text(branch *br);

char *brGetBranch2Text(branch *br);

char *brGetText(branch *br);

branch *brGetBranch1(branch *br);

branch *brGetBranch2(branch *br);

#ifdef DEBUG
int brGetUUID(branch *br);
#endif

// note: these return 0 if branch was already there

int brSetBranch1(branch *br, branch *value);

int brSetBranch2(branch *br, branch *value);

void brPrint(branch *br);

//void initializeTree(branch *root);

void brRelease(branch *br);

branch *brGetPrevious(branch *br);

branch *brDup(branch *br);

#endif
