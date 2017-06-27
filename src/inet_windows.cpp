/*
 * =====================================================================================
 *
 *       Filename:  inet_windows.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/22/2017 04:13:56 PM
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

#include "inet_windows.hpp"
#include "err.hpp"
#include "iswin.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;

#ifdef USING_WIN

int initialize_wininet() {
//  cout << "Initializing wininet..." << endl;
  WSADATA wsaData;
  int result;

  result = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (result != 0) {
    error("WSAStartup failed: " + result,0);
  }
//  cout << "Initialized wininet" << endl;
  return result;
}

struct sockaddr *ai_addr;
int ai_addrlen;

SOCKET openListenerSocket() {
  struct addrinfo *result = NULL, *ptr = NULL, hints;
  ZeroMemory(&hints,sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  int iResult = getaddrinfo(NULL, "32001", &hints, &result);
  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);
    WSACleanup();
    return 1;
  }

  ai_addr = result->ai_addr;
  ai_addrlen = (int)result->ai_addrlen;
  SOCKET s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (s == INVALID_SOCKET) {
    fprintf(stderr,"Unable to open socket: %ld\n",WSAGetLastError());
    freeaddrinfo(result);
    WSACleanup();
    exit(1);
  }
  return s;
}

void bindToPort(SOCKET listener, int port) {
//  cout << "Binding to port..." << endl;
  int iResult = bind(listener,ai_addr,ai_addrlen);
  if (iResult == SOCKET_ERROR) {
    fprintf(stderr,"Unable to bind to port: %d\n",iResult);
    closesocket(listener);
    WSACleanup();
    exit(1);
  }
//  cout << "Bound to port" << endl;
}

SOCKET openSocket_win(const char *host, const char *port) {
//  cout << "Opening socket..." << endl;
  struct addrinfo *result = NULL;
  struct addrinfo *ptr = NULL;
  struct addrinfo hints;

  ZeroMemory(&hints,sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if (getaddrinfo(host,port,&hints,&result) != 0) {
    fprintf(stderr,"Unable to resolve the address: %d\n",WSAGetLastError());
    WSACleanup();
    exit(1);
  }
//  cout << "Got address info..." << endl;
  SOCKET connection = INVALID_SOCKET;
  ptr = result;
  connection = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
  
  if (connection == INVALID_SOCKET) {
    fprintf(stderr,"Unable to open socket");
    freeaddrinfo(result);
    WSACleanup();
    exit(1);
  }

  int iresult = connect(connection,ptr->ai_addr,(int)ptr->ai_addrlen);
  if (iresult == SOCKET_ERROR) {
    closesocket(connection);
    connection = INVALID_SOCKET;
  }
  freeaddrinfo(result);

  if (connection == INVALID_SOCKET) {
    fprintf(stderr,"Unable to connect to server: %d\n",WSAGetLastError());
    WSACleanup();
    exit(1);
  }
  return connection;
}

int say_win(SOCKET sock, const char *msg) {
  int result = send(sock,msg,strlen(msg),0);
  if (result == SOCKET_ERROR) {
    fprintf(stderr,"Unable to send message: %d\n",WSAGetLastError());
    closesocket(sock);
    WSACleanup();
    exit(1);
  }
  return result;
}

int readIn_win(SOCKET sock, char *buffer, int length) {
  char *s = buffer;
  int slen = length;
  int c = recv(sock,s,slen,0);
  while ((c > 0) && (s[c - 1] != '\n')) {
    s += c; slen -= c;
    c = recv(sock,s,slen,0);
  }
  if (c < 0)
    return c;
  else if (c == 0)
    buffer[0] = '\0';
  else
    s[c-1] = '\0';
  return length - slen;
}

#endif
