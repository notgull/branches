/*
 * =====================================================================================
 *
 *       Filename:  shortcuts.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/16/2017 08:49:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "shortcuts.hpp"
#include "err.hpp"
#include <iostream>
#include <stdio.h>
#include <cctype>
#include <sys/stat.h>
using namespace std;


#define SIZE_OF_INPUT 256

void newline() {
  cout << endl;
}

void shell_tx() {
  cout << "> ";
}

int yesno(int nullfirst, string question) {
  int first = nullfirst;
  string response;
  cout << question << " [Y/n]";
  getline(cin,response);
  do {
    if (tolower(response[0]) == 'y')
    {
       return 1;
    }
    else if (tolower(response[0]) == 'n') {
       return 0;
    }
    else {
       if (first) {
         puts("Invalid response.");
         cout << question << " [Y/n]";
       }
       first = 1;
       getline(cin,response);
    }
  } while (1);
  return -1;
}

int check_file(string filename) {
  struct stat st;
  if (stat(filename.c_str(),&st) != 0) {
    return 1;
  }
  if (st.st_size == 0)
    return 1;
  return 0;
}
