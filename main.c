/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:29:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "branch.h"
#include "header.h"
#include "err.h"
#include <stdio.h>
#include <string.h>

void print_version(int verbose) {
  if (!verbose)
    printh("Welcome to Branches vAlpha.2");
  else
    printf("You are using: Branches Alpha.2");
}

void print_cmds() {
  puts("List of commands:");
  puts("1 - select branch number one");
  puts("2 - select branch number two");
  puts("p - reprints the current node to the console");
  puts("v - prints version information");
  puts("h - list this help menu again");
  puts("e - exit the game");
  puts("Enter the letter and press the Enter key to use the command");
}

void newline() {
  printf("\n");
}

int main() {
  print_version(0);
  newline();
  print_cmds();
  newline();

  

  return 0;
}
