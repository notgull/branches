/*
 * =====================================================================================
 *
 *       Filename:  saves.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2017 09:39:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "saves.h"
#include "brstring.h"

#include <stdio.h>

int brSaveToFile(branch *br, char *filename) {
  FILE *output = fopen(filename,"w");
  fprintf(output,brToString(br));
  fclose(output);
  return 0;
}

branch *brLoadFromFile(char *filename) {
  return brCreate("","","");
}
