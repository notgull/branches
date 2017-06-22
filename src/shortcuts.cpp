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
  cout << question << " [Y/n] ";
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
