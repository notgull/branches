/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/2017 03:18:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "main.hpp"
#include "program.hpp"
#include "server.hpp"
#include "branches_config.hpp"

int main() {
#if br_SERVER == 0
  return runProgram();
#else
  return runServer();
#endif
}
