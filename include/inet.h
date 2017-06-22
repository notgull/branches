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

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

int say_c(int socket, const char *msg);
void bindToPort(int socket, int port);
int openSocket_c(const char *host, const char *port);
int openListenerSocket();
int readIn_c(int socket, char *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif
