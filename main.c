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

#include "header.h"
#include "err.h"
#include "shortcuts.h"
#include "branch.h"
#include <stdio.h>
#include <string.h>

void print_version(int verbose) {
  if (!verbose)
    printh("Welcome to Branches vBeta.1");
  else
    printf("You are using: Branches Beta.1 Revision 2\n");
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

int main() {
  print_version(0);
  newline();
  print_cmds();
  newline();

  branch root = brCreate("Take the left path", "Take the right path", "You come across a fork in the road.");
  brPrint(root);
//  initializeTree(&root);
  branch br1;
  branch br2;
  
  br1 = brCreate("Knock on the door","Peer through the window","You come across a house on the prarie.");
  br2 = brCreate("Cross the bridge","Jump into the water","You come across a bridge crossing a river.");
  brSetBranch1(&root,&br1);
  brSetBranch2(&root,&br2);
 
  branch *current = &root;
  
  int cont = 1;
  char cmd[5];
  do {
    // todo: print node
    shell_tx();
    scanf("%s",cmd); 
    #if DEBUG
    printf("You entered: %s",cmd);
    #endif
    switch (cmd[0]) {
      case 'e':
        printf("Exiting Branches...\n");
	cont = 0;
	break;
      case 'v':
        print_version(1);
	break;
      case 'h':
        print_cmds();
	break;
      case '2':
        current = brGetBranch2(*(current));
	brPrint(*(current));
	break;
      case '1':
        current = brGetBranch1(*(current));
      case 'p':
        brPrint(*(current));
	break;
      default:
        fprintf(stderr,"Invalid command, please reenter\n");
	break;
    }
  } while (cont);

  return 0;
}
