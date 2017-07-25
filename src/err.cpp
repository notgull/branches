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
 
This file is part of Branches.

Branches is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Branches is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Branches.  If not, see <http://www.gnu.org/licenses/>.

 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "err.hpp"
#include "ismac.hpp"
#ifdef USING_MAC
#include <unistd.h>
#endif
using namespace std;

// exit the program and show the error message
void error(string msg, int showErrno) {
  if (showErrno)
    fprintf(stderr, "%s: %s\n", msg.c_str(), strerror(errno));
  else
    fprintf(stderr, "%s\n",msg.c_str());
#ifdef USING_MAC
  _exit(1);
#else
  exit(1);
#endif
}
