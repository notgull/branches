/*
 * =====================================================================================
 *
 *       Filename:  shortcuts.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/16/2017 08:49:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "shortcuts.h"
#include <stdio.h>
#include <string.h>

#define SIZE_OF_INPUT 256

void newline() {
  printf("\n");
}

void shell_tx() {
  printf("> ");
}

int yesno(char *question) {
  char response[4];
  printf("%s [Y/n] ",question);
  scanf("%3s",response);
  do {
    if (tolower(response[0]) == 'y')
    {
       return 1;
    }
    else if (tolower(response[0]) == 'n') {
       return 0;
    }
    else {
       puts("Invalid response.");
       printf("%s [Y/n] ",question);
       scanf("%3s",response);
    }
  } while (1);
  return -1;
}

void getInput(char *inputGet, char *output) {
  printf("%s: ",inputGet);
  fgets(output,SIZE_OF_INPUT,stdin);
  if ((strlen(output) > 0) && (output[strlen(output) - 1] == '\n'))
    output[strlen(output) - 1] = '\0';
}
