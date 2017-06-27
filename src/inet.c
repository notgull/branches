/*
 * =====================================================================================
 *
 *       Filename:  inet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2017 02:54:01 PM
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

#include "iswin.hpp"

#ifndef USING_WIN

#include "inet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

// since err.hpp is C++, let's write our own function
void error(char *msg) {
  fprintf(stderr,"%s: %s\n",msg,strerror(errno));
  exit(1);
}

int openListenerSocket() {
  int s = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
  if (s == -1)
    error("Unable to open socket");
  return s;
}

int openSocket_c(const char *host, const char *port) {
  struct addrinfo *res;
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  if (getaddrinfo(host, port, &hints, &res) == -1)
    error("Unable to resolve the address");
  int d_sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
  if (d_sock == -1)
    error("Unable to open socket");
  int c = connect(d_sock,res->ai_addr,res->ai_addrlen);
  freeaddrinfo(res);
  if (c == -1)
    error("Unable to connect to socket");
  return d_sock;
}

int say_c(int socket, const char *msg) {
  int result = send(socket,msg,strlen(msg),0);
  if (result == -1)
    fprintf(stderr,"%s: %s\n", "Error communicating with server",strerror(errno));
  return result;
}

void bindToPort(int socket, int port) {
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;
  if (setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(int)) == -1)
    error("Unable to set the reuse option on the socket");
  int c = bind(socket,(struct sockaddr *)&name,sizeof(name));
  if (c == -1)
    error("Unable to bind to socket");
}

int readIn_c(int socket, char *buffer, int length) {
  char *s = buffer;
  int slen = length;
  int c = recv(socket,s,slen,0);
  while ((c > 0) && (s[c - 1] != '\n')) {
    s += c; slen -= c;
    c = recv(socket,s,slen,0);
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
