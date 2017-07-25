/*
 * =====================================================================================
 *
 *       Filename:  inet_windows.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/22/2017 04:09:55 PM
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

#ifndef NET_WIN_H
#define NET_WIN_H

#include "iswin.hpp"

#ifdef USING_WIN

#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

// initialize WS2
int initialize_wininet();
// open a socket to a server
SOCKET openSocket_win(const char *host, const char *port);
// open a socket to a client
SOCKET openListenerSocket();
// bind a socket to a port
void bindToPort(SOCKET listener, int port);
// say something to a server
int say_win(SOCKET sock, const char *msg);
// read a string from a server
int readIn_win(SOCKET sock, char *buffer, int length);

#endif

#endif
