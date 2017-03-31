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
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX_SIZE 256

// prints version information
void print_version(int verbose) {
  if (!verbose)
    printh("Welcome to Branches v1.5.1");
  else
    printf("You are using: Branches Version 1 Revision 5 MR 1\n");
}

// prints help menu
void print_cmds() {
  puts("List of commands:");
  puts("1 - select branch number one");
  puts("2 - select branch number two");
  puts("r - return to start");
  puts("p - reprints the current node to the console");
  puts("v - prints version information");
  puts("h - list this help menu again");
  puts("e - exit the game");
  puts("Enter the letter and press the Enter key to use the command");
}

// make a new branch from user input
branch usr_input_branch() {
  char main_text[INPUT_MAX_SIZE];
  char b1[INPUT_MAX_SIZE];
  char b2[INPUT_MAX_SIZE];
  char response[4];
  char dummy[4];

  do {
    newline();
    /*
    printf("Enter main text: ");
    //scanf("%s",main_text);
    fgets(main_text,INPUT_MAX_SIZE,stdin);
    if ((strlen(main_text)>0) && (main_text[strlen (main_text) - 1] == '\n'))
        main_text[strlen (main_text) - 1] = '\0';

    printf("Enter Option 1: ");
    //scanf("%s",b1);
    fgets(b1,INPUT_MAX_SIZE,stdin);
    if ((strlen(b1)>0) && (b1[strlen (b1) - 1] == '\n'))
        b1[strlen (b1) - 1] = '\0';

    printf("Enter Option 2: ");
    //scanf("%s",b2);
    fgets(b2,INPUT_MAX_SIZE,stdin);
    if ((strlen(b2)>0) && (b2[strlen (b2) - 1] == '\n'))
        b2[strlen (b2) - 1] = '\0';
    */
    fgets(dummy,4,stdin);
    getInput("Enter main text",main_text);
    getInput("Enter Option 1",b1);
    getInput("Enter Option 2",b2);
    newline();
    puts("Here is your branch:");
    newline();
    branch br = brCreate(b1,b2,main_text);
    //branch br = brCreate("test","test",main_text);
    brPrint(br);
    if (yesno("Is this okay?")) {
      newline();
      return br;
    }
  } while (1); 
  // inaccessible code
  error("Inaccessible code",0);
  return brCreate("","","");
}

// program entry point
int main() {
  // introduce the help menu and version info
  print_version(0);
  newline();
  print_cmds();
  newline();

  // initial branch
  branch root = brCreate("Take the left path", "Take the right path", "You come across a fork in the road.");
  brPrint(root);
//  initializeTree(&root);
  branch br1;
  branch br2;
  
  // other two branches
  br1 = brCreate("Knock on the door","Peer through the window","You come across a house on the prarie.");
  br2 = brCreate("Cross the bridge","Jump into the water","You come across a bridge crossing a river.");
  brSetBranch1(&root,&br1);
  brSetBranch2(&root,&br2);
 
  // current branch
  branch *current = &root;
  
  // don't use loop.h for this; loop.h is needed for inner loops
  // also, this is the main loop
  int cont = 1;
  char cmd[5];
  do {
    // this makes the > thing
    shell_tx();
    // get the command
    scanf("%s",cmd); 

    // outdated debugging crap
    #if DEBUG
    printf("You entered: %s",cmd);
    #endif

    // wat do?
    switch (cmd[0]) {
      case 'e':
        // user wants to exit the game
        printf("Exiting Branches...\n");
	cont = 0;
	break;
      case 'v':
        // print verbose game information
        print_version(1);
	break;
      case 'h':
        // reprint help information
        print_cmds();
	break;
      case '2':
        if (brHasBranch2(*(current)))
          current = brGetBranch2(*(current));
	else {
	  if (yesno("You have reached the end. Would you like to create a new node?")) {
	      branch br = usr_input_branch();
	      brSetBranch2(current,&br);
	      current = &br;
	  }
	  else
	      current = &root;
	}
	brPrint(*(current));
	break;
      case '1':
        if (brHasBranch1(*(current)))
          current = brGetBranch1(*(current));
	else {
	  if (yesno("You have reached the end. Would you like to create a new node?")) {
	      branch br = usr_input_branch();
	      brSetBranch1(current,&br);
	      current = &br;
	  }
	  else
	      current = &root;
	  
	}
      case 'p':
        brPrint(*(current));
	break;
      case 'r':
        current = &root;
	brPrint(root);
	break;
      default:
        fprintf(stderr,"Invalid command, please reenter\n");
	break;
    }
  } while (cont);

  return 0;
}
