/*
 * =====================================================================================
 *
 *       Filename:  branch.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/2017 09:26:49 AM
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

// branch struct
struct Branch {
  char *text1;
  char *text2;
  int hasBranchOne;
  int hasBranchTwo;
  Branch *choice1;
  Branch *choice2;
  char *mainText;
}

Branch *br_create(char *text1, char *text2, char *mainText);

int br_has_branch_one(*Branch br);

int br_has_branch_two(*Branch br);

void br_set_branch_one(*Branch br, *Branch toSet);

void br_set_branch_two(*Branch br, *Branch toSet);

Branch *br_get_branch_one(*Branch br);

Branch *br_get_branch_two(*Branch br);

char *br_get_main_text(*Branch br);

char *br_get_choice_one_text(*Branch br);

char *br_get_choice_two_text(*Branch br);

#endif // BRANCH_H
