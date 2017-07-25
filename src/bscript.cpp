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
#include "iswin.hpp"
#include "inet_cxx.hpp"
#include "splitstr.hpp"
#include <sstream>
#include <fstream>
using namespace std;

// write the list of ints to a file
void bscrWrite(vector<int> instr, string filename) {
  ofstream output;
  output.open(filename);
  for (int i : instr) {
    output << i << endl;
  }
  output.close();
}

// read a list of ints from a file
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

// take a root branch and follow a list of ints to another branch
#ifdef USING_WIN
branch *bscrFollow(vector<int> values, branch *root, branch *third_tree, SOCKET sock) {
#else
#define INVALID_SOCKET -1
branch *bscrFollow(vector<int> values, branch *root, branch *third_tree, int sock) {
#endif
  branch *current = root;
  for (int i : values) {
    if (i == 1 && current->hasBranch1()) {
      current = current->getBranch1();
      if (sock != INVALID_SOCKET)
        say(sock,"N:1\n");   
    }
    else if (i == 1 && sock != INVALID_SOCKET && !(current->hasBranch1())) {
      say(sock,"E:1\n");
      string result = readIn(sock);
      if (result[0] != '1')
      {
        string br = (splitString(result,':'))[0];
        current->setBranch1(brFromString(br));
        current = current->getBranch1();
      }
      else return current;
    }
    else if (i == 1 && !(current->hasBranch1())) return current;

    if (i == 2 && current->hasBranch2()) {
      current = current->getBranch2();
      if (sock != INVALID_SOCKET)
        say(sock,"N:2\n");   
    }
    else if (i == 2 && sock != INVALID_SOCKET && !(current->hasBranch2())) {
      say(sock,"E:2\n");
      string result = readIn(sock);
      if (result[0] != '1')
      {
        string br = (splitString(result,':'))[0];
        current->setBranch2(brFromString(br));
        current = current->getBranch2();
      }
      else return current;
    }
    else if (i == 2 && !(current->hasBranch2())) return current;

    if (i == 3 && current == root) {
      current = third_tree;
      if (sock != INVALID_SOCKET)
        say(sock,"3\n");
    }
  }
  return current;
}
