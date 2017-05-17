/*
 * =====================================================================================
 *
 *       Filename:  splitstr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/02/2017 05:52:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "splitstr.hpp"
#include <iostream>
#include <sstream>

using namespace std;

vector<string> splitString(string str, char sep) {
  vector<string> collection(0);
  stringstream temp (stringstream::in | stringstream::out);

  if (str.size() == 0 || sep == 0) {
    collection.push_back(str);
    return collection;
  }
 
  for (char c : str) {
    if (c == sep) {
      collection.push_back(temp.str());
      temp = stringstream(stringstream::in | stringstream::out);
    }
    else {
      temp << c;
    }
  }

  if (temp.str().size() > 0) {
    collection.push_back(temp.str());
  }

  return collection;
}
