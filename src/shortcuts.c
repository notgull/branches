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
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

// used for accumulation
char *acc_var = 0;
int is_accumulating = 0;

void beginAccumulation() {
  if (is_accumulating == 1)
    error("Already in the process of accumulation",0);
  is_accumulating = 1;
}

void stackAccumulation(char *acc) {
  if (!is_accumulating)
    error("Not in the process of accumulation",0);
  if (!acc_var)
    acc_var = strdup(acc);
  else {
    strcat(acc_var,acc);
  }
}

char *finishAccumulation() {
  if (!is_accumulating)
    error("Not in the process of accumulation",0);
  if (!acc_var)
    error("No accumulation has been done",0);
  
  is_accumulating = 0;
  char *duplicated = strdup(acc_var);
  acc_var = 0;
  return strdup(duplicated);
}

int check_file(char *filename) {
  struct stat st;
  if (stat(filename,&st) != 0) {
    return 1;
  }
  if (st.st_size == 0)
    return 1;
  return 0;
}
