/*
 * =====================================================================================
 *
 *       Filename:  initialtree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/18/2017 06:21:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "initialtree.h"

void initializeTree(branch *root) {
  // variables
  branch br1;
  branch br2;

  br1 = brCreate("Knock on the door","Peer through the window","You come across a house on the prarie.");
  br2 = brCreate("Cross the bridge","Jump into the water","You come across a bridge crossing a river.");

  brSetBranch1(root,&br1);
  brSetBranch2(root,&br2);
}
