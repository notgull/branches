/*
 * =====================================================================================
 *
 *       Filename:  str-to-ptr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/2017 03:23:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "string_helper.hpp"
//#include "shortcuts.h"
//#include "err.h"
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>

//#define DEBUG

#include <iostream>

using namespace std;

char *getPointerFrom(std::string str) {
  vector<char> v(str.length() + 1);
  strcpy(&v[0], str.c_str());
  char *ptr = &v[0];
  return strdup(ptr);
}

string getStringFrom(char *str) {
#ifdef DEBUG
  cout << "Converting str " << str << endl;
#endif
  return string(str);
}

char *getAllLinesFromFile(char *filename) { 
  string fname(filename);
  ifstream input(fname);
  string result = "";
  string line;

  while (std::getline(input,line)) {
#ifdef DEBUG
  cout << "Adding line " << line << endl;
#endif
    result += line;
    result += "\n";
  }

  return getPointerFrom(result);
}
