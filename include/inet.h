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
