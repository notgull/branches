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
 */

#include "inet_cxx.hpp"
#include <string.h>
using namespace std;

int say(int socket, string msg) {
  return say_c(socket,msg.c_str());
}

int openSocket(string host, string port) {
  return openSocket_c(host.c_str(),port.c_str());
}

string readIn(int socket) {
  string str;
  char *writable = new char[1024];
  std::copy(str.begin(), str.end(), writable);
  writable[str.size()] = '\0';

  readIn_c(socket,writable,1024);   

  string result(writable);
  delete[] writable; 
 
  return result;
}
