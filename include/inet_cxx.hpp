/*
 * =====================================================================================
 *
 *       Filename:  inet_cxx.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2017 03:11:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef INET_CXX_HPP
#define INET_CXX_HPP

#include "inet.h"
#include <string>
using namespace std;

int say(int socket, string msg);
int openSocket(string host, string port);
string readIn(int socket);

#endif
