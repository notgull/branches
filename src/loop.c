/*
 * =====================================================================================
 *
 *       Filename:  loop.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2017 10:41:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "loop.h"

int _looping = 0;

void beginLoop() {
  _looping = 1;
}

int isLooping() {
  return _looping;
}

void stopLoop() {
  _looping = 0;
}
