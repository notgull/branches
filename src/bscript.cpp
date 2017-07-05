/*
 * =====================================================================================
 *
 *       Filename:  bscript.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2017 07:31:06 AM
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

#include "bscript.hpp"
#include <sstream>
#include <fstream>
using namespace std;

void bscrWrite(vector<int> instr, string filename) {
  ofstream output;
  output.open(filename);
  for (int i : instr) {
    output << i << endl;
  }
  output.close();
}

vector<int> bscrRead(string filename) {
  vector<int> retV (0);
  ifstream input (filename);
  int i;
  string line;
  if (input.is_open()) {
    while (getline(input,line)) { 
      stringstream temp (stringstream::in | stringstream::out);
      temp << line;
      temp >> i;
      retV.push_back(i);
    }
    input.close();       
  }
  return retV;
} 

branch *bscrFollow(vector<int> values, branch *root, branch *third_tree) {
  branch *current = root;
  for (int i : values) {
    if (i == 1 && current->hasBranch1())
      current = current->getBranch1();
    if (i == 2 && current->hasBranch2())
      current = current->getBranch2();
    if (i == 3 && current == root)
      current = third_tree;
  }
  return current;
}
