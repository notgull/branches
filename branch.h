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


typedef struct br_struct {
  int hasB1;
  int hasB2;
  char *b1;
  char *b2;
  char *txt;
} branch;

branch *brCreate(char *b1, char *b2, char *txt);

int brHasBranch1(branch *br);

int brHasBranch2(branch *br);


