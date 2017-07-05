/*
 * =====================================================================================
 *
 *       Filename:  branch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:28:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 *

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

#include "branch.hpp"
#include "err.hpp"
#include "shortcuts.hpp"
#include "splitstr.hpp"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

branch::branch(string b1, string b2, string txt) {
  this->b1 = b1;
  this->b2 = b2;
  this->txt = txt;

  this->branch1 = NULL;
  this->branch2 = NULL;
  this->prev = NULL;
}

bool branch::hasBranch1() {
  if (this->branch1)
    return true;
  return false;
}

bool branch::hasBranch2() {
  if (this->branch2)
    return true;
  return false;
}

string branch::getMainText() {
  return this->txt; 
}

string branch::getText1() {
  return this->b1;
}

string branch::getText2() {
  return this->b2;
}

branch *branch::getBranch1() {
  return this->branch1;
}

branch *branch::getBranch2() {
  return this->branch2;
}

branch *branch::getPrevious() {
  return this->prev;
}

void branch::setBranch1(branch *br) {
  this->branch1 = br;
  if (br)
    br->prev = this;
}

void branch::setBranch2(branch *br) {
  this->branch2 = br;
  if (br)
    br->prev = this;
}

string branch::printWorthy() {
  stringstream temp (stringstream::in | stringstream::out);
  temp << this->txt << endl;
  temp << "Option 1: " << this->b1 << endl;
  temp << "Option 2: " << this->b2 << endl;
  return temp.str();
}

void brPrint(branch br) {
  cout << br.printWorthy();
}

branch branch::clone() {
  branch br = branch(getText1(),getText2(),getMainText()); 
    if (this->hasBranch1()) br.branch1 = this->branch1;
    if (this->hasBranch2()) br.branch2 = this->branch2;
  return br;
}

branch branch::trim() {
  branch br = this->clone();
  br.branch1 = NULL;
  br.branch2 = NULL;
  return br;
}

#define BR_DEAD_END "BR_DEAD_END"

int brIsDeadEnd(branch br) {
  string txt = br.getMainText();
  string b1 = br.getText1();
  string b2 = br.getText2();

  return ((txt == BR_DEAD_END) && (b1 == BR_DEAD_END) && (b2 == BR_DEAD_END)) ? 1 : 0;
}

int getLineIndent(string line) {
  int indent = 0;
  for (char c : line)
  {
    if (c == ' ')
      indent++;
    else
      break;
  }
  return indent;
}

branch *rawFromString(string input, int indent) {
  string str;
  if (indent == 0)
    str = input;
  else
    str = input.substr (indent);

  vector<string> parts = splitString(str,'/');
  if (parts.size() != 3)
    error("Improper string",0);

  string txt = parts[0];
  string b1 = parts[1];
  string b2 = parts[2];
 
  branch *br = new branch(b1,b2,txt);
  return br; 
}

branch *constructTree(vector<branch *> br_v, vector<int> indent_v, int indent) {
  int targetIndent = indent + 1;
  branch *target = br_v[0];


  if (br_v.size() == 1) {

    return target;
  }

  branch *br1 = NULL;
  branch *br2 = NULL;
  int br1_index = -1;
  int br2_index = -1;

  for (int i = 0; i < br_v.size(); i++) {
    if (indent_v[i] == targetIndent) {
      if (br1 == NULL) {
        br1 = br_v[i];
        br1_index = i;
      }
      else if (br2 == NULL) {
        br2 = br_v[i];
        br2_index = i;
      }
    }
  }

#ifdef DEBUG
  cout << "Index 1 is " << br1_index << " and Index 2 is " << br2_index << endl;
#endif

  if (br1_index == -1 || br2_index == -1) {
#ifdef DEBUG
    cout << "Indexes are null, returning..." << endl;
#endif
    return target;
  }

  vector<branch *>::const_iterator first = br_v.begin() + br1_index;
  vector<branch *>::const_iterator last = br_v.begin() + br2_index;
  vector<branch *> sec1(first,last);
  
  vector<branch *> sec2;
    first = br_v.begin() + br2_index;
    last = br_v.begin() + br_v.size();
    sec2 = vector<branch *>(first,last);

  vector<int>::const_iterator i_first = indent_v.begin() + br1_index;
  vector<int>::const_iterator i_last = indent_v.begin() + br2_index;
  vector<int> i_sec1(i_first,i_last);

  vector<int> i_sec2(0);
    i_first = indent_v.begin() + br2_index;
    i_last = indent_v.begin() + br_v.size();
    i_sec2 = vector<int>(i_first,i_last);

#ifdef DEBUG

  cout << "Recursing constructTree..." << endl;
#endif

  br1 = constructTree(sec1,i_sec1,targetIndent);
  br2 = constructTree(sec2,i_sec2,targetIndent);
  
  int br1_isDeadEnd = brIsDeadEnd(*(sec1[0]));
  int br2_isDeadEnd = brIsDeadEnd(*(sec2[0]));

#ifdef DEBUG
  cout << "br1_isDeadEnd is " << br1_isDeadEnd << " and br2_isDeadEnd is " << br2_isDeadEnd << endl;
#endif

#ifdef DEBUG
  cout << "Setting branches..." << endl;
#endif
  if (br1_isDeadEnd == 0) target->setBranch1(br1);
  if (br2_isDeadEnd == 0) target->setBranch2(br2);

#ifdef DEBUG
  cout << "constructTree at indent " << indent << " finished successfully" << endl;
#endif

  return target;
}

branch *brFromString(string str) {
 istringstream f(str);
 string line;
 vector<branch *> branches(0);
  vector<int> indents(0);
  
  while (getline(f,line)) {
     int indent = getLineIndent(line);
     branches.push_back(rawFromString(line,indent));
     indents.push_back(indent);
  }

  branch *root = constructTree(branches,indents,0);

  return root;
}

string brToStringInternal(branch *br, int indent) {
  string str;
  for (int i = 0; i < indent; i++)
    str += " ";

  str += br->getMainText();
  str += "/";
  str += br->getText1();
  str += "/";
  str += br->getText2();
  str += "\n";

  if (br->hasBranch1() == 0 && br->hasBranch2() == 0)
    return str;

  branch dead_end (BR_DEAD_END,BR_DEAD_END,BR_DEAD_END);

  if (br->hasBranch1())
    str += brToStringInternal(br->getBranch1(),indent + 1);
  else if (br->hasBranch2())
    str += brToStringInternal(&(dead_end),indent + 1);

  if (br->hasBranch2())
    str += brToStringInternal(br->getBranch2(),indent + 1);
  else if (br->hasBranch1())
    str += brToStringInternal(&(dead_end),indent + 1);
  
  return str;
}

string branch::toString() {
  return brToStringInternal(this,0);
}

int branch::countElements() {
  int i = 1;
  if (this->hasBranch1())
    i += this->getBranch1()->countElements();
  if (this->hasBranch2())
    i += this->getBranch2()->countElements();
  return i;
}

vector<branch *> branch::compileToList() {
  vector<branch *> list(0);
  list.push_back(this);
  if (this->hasBranch1()) {
    vector<branch *> b1list = this->getBranch1()->compileToList();
    list.insert(list.end(),b1list.begin(),b1list.end());
  }
  if (this->hasBranch2()) {
    vector<branch *> b2list = this->getBranch2()->compileToList();
    list.insert(list.end(),b2list.begin(),b2list.end());
  }
  return list;
}

void branch::nullifyPrevious() {
  this->prev = NULL;
}

void brDeleteBranch(branch *br) {
  if (br->hasBranch1())
  {
    brDeleteBranch(br->getBranch1());
    br->setBranch1(NULL);
  }
  if (br->hasBranch2())
  {
    brDeleteBranch(br->getBranch2());
    br->setBranch2(NULL);
  }
  br->nullifyPrevious();
  delete br;
}