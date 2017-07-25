/*
 * =====================================================================================
 *
 *       Filename:  inet.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2017 02:48:21 PM
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

#ifndef INET_H
#define INET_H

#include "iswin.hpp"
#ifndef USING_WIN

/*
Since this is a C-based file, instead of a C++ based file, we need this wrapper so it is compatible with C++.
However, if we are using a C compiler, which happens when we compile inet.c, this will throw an error. So I wrap it in __cplusplus so it will only be compiled in if we are using a C++ compiler.
*/
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

// say something to a server
int say_c(int socket, const char *msg);
// bind to a port
void bindToPort(int socket, int port);
// open a client socket
int openSocket_c(const char *host, const char *port);
// open a listener socket
int openListenerSocket();
// read in a string
int readIn_c(int socket, char *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif

#endif
