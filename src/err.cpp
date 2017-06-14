/*
 * =====================================================================================
 *
 *       Filename:  err.c
 *
 *    Description:  For throwing errors - implementation
 *
 *        Version:  1.0
 *        Created:  03/15/2017 10:02:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "err.hpp"
using namespace std;

void error(string msg, int showErrno) {
  if (showErrno)
    fprintf(stderr, "%s: %s\n", msg.c_str(), strerror(errno));
  else
    fprintf(stderr, "%s\n",msg.c_str());
  exit(1);
}
