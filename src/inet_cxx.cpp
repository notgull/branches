/*
 * =====================================================================================
 *
 *       Filename:  inet_cxx.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2017 03:15:47 PM
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

#include "inet_cxx.hpp"
#include <string.h>
#include "iswin.hpp"
using namespace std;

// send a message to a server through a socket
#ifdef USING_WIN
int say(SOCKET sock, string msg) {
  return say_win(sock,msg.c_str());
}
#else
int say(int sock, string msg) {
  return say_c(sock,msg.c_str());
}
#endif

// open a socket to communicate through
#ifdef USING_WIN
SOCKET openSocket(string host, string port) {
  return openSocket_win(host.c_str(),port.c_str());
}
#else
int openSocket(string host, string port) {
  return openSocket_c(host.c_str(),port.c_str());
}
#endif

// read a message in through a socket
#ifndef USING_WIN
string readIn(int sock) {
#else
string readIn(SOCKET sock) {
#endif
  string str;
  char *writable = new char[1024];
  std::copy(str.begin(), str.end(), writable);
  writable[str.size()] = '\0';

#ifdef USING_WIN
  readIn_win(sock,writable,1024);
#else
  readIn_c(sock,writable,1024);
#endif

  string result(writable);
  delete[] writable; 
 
  return result;
}
