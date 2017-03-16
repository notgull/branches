/*
 * =====================================================================================
 *
 *       Filename:  branch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/2017 10:53:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */
#include "branch.h"
#include "null.h"

Branch *br_create(char *text1, char *text2, char *mainText) {
  Branch br = {text1,text2,0,0,NULL,NULL,mainText};
  return br;
}

int br_has_branch_one(*Branch br) {

}

