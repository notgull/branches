/*
 * =====================================================================================
 *
 *       Filename:  header.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:33:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "header.h"
#include <stdio.h>

// change as needed
#define HEADER_W 6

int getheaderw() {
  return HEADER_W;
}

char headerc = '=';

char getheaderc() {
  return headerc;
}

void setheaderc(const char c) {
  headerc = c;
}

void printh(const char *s) {
  char hc = getheaderc();
  int hw = getheaderw();

  for (int i = 0; i < hw; i++)
    printf("%c",hc);

  printf(" %s ",s);

  for (int j = 0; j < hw; j++)
    printf("%c",hc);

  printf("\n");
}
