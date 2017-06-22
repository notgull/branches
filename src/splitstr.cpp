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
