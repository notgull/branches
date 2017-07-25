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

// standard constructor
branch::branch(string b1, string b2, string txt) {
  this->b1 = b1;
  this->b2 = b2;
  this->txt = txt;
  this->isEnd = false;

  this->branch1 = NULL;
  this->branch2 = NULL;
  this->prev = NULL;
}

// ending constructor
branch::branch(string txt) {
  this->b1 = "";
  this->b2 = "";
  this->txt = txt;
  this->isEnd = true;

  this->branch1 = NULL;
  this->branch2 = NULL;
  this->prev = NULL;
}

/*
Note: in this code, I do the following:
  if (this->branch1)

This is because if you do if (<a pointer>) it will become true if the pointer has a value, or false if it does not.
*/

// determine if branch1 exists
bool branch::hasBranch1() {
  if (this->branch1)
    return true;
  return false;
}

// determine if branch2 exists
bool branch::hasBranch2() {
  if (this->branch2)
    return true;
  return false;
}

// get the main text
string branch::getMainText() {
  return this->txt; 
}

// get the text for option 1
string branch::getText1() {
  return this->b1;
}

// get the text for option 2
string branch::getText2() {
  return this->b2;
}

// get the pointer to branch 1
branch *branch::getBranch1() {
  return this->branch1;
}

// get the pointer to branch 2
branch *branch::getBranch2() {
  return this->branch2;
}

// get the pointer to the previous branch
branch *branch::getPrevious() {
  return this->prev;
}

// get the boolean determining if this is an ending branch
bool branch::isEnding() {
  return this->isEnd;
}

// set branch pointer 1 to another branch
void branch::setBranch1(branch *br) {
  this->branch1 = br;
  if (br)
    br->prev = this;
}

// set branch pointer 2 to another branch
void branch::setBranch2(branch *br) {
  this->branch2 = br;
  if (br)
    br->prev = this;
}

// convert this branch to a nice format
string branch::printWorthy() {
  stringstream temp (stringstream::in | stringstream::out);
  temp << this->txt << endl;
  temp << "Option 1: " << this->b1 << endl;
  temp << "Option 2: " << this->b2 << endl;
  return temp.str();
}

// print the aforementioned nice format
void brPrint(branch br) {
  cout << br.printWorthy();
}

// clone the branch
branch branch::clone() {
  branch br = branch(getText1(),getText2(),getMainText()); 
    if (this->hasBranch1()) br.branch1 = this->branch1;
    if (this->hasBranch2()) br.branch2 = this->branch2;
  return br;
}

// trim the branch
branch branch::trim() {
  branch br = this->clone();
  br.branch1 = NULL;
  br.branch2 = NULL;
  return br;
}

#define BR_DEAD_END "BR_DEAD_END"

// determine if a branch is a dead end, used in reading algorithms
int brIsDeadEnd(branch br) {
  string txt = br.getMainText();
  string b1 = br.getText1();
  string b2 = br.getText2();

  return ((txt == BR_DEAD_END) && (b1 == BR_DEAD_END) && (b2 == BR_DEAD_END)) ? 1 : 0;
}

// determine the identation of a line, used in reading algorithms
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

// gets one node raw from a string
branch *rawFromString(string input, int indent) {
  // set str to an indentless string, using substr
  string str;
  if (indent == 0)
    str = input;
  else
    str = input.substr (indent);

  // split the string by slashes
  vector<string> parts = splitString(str,'/');
  if (parts.size() != 3)
    error("Improper string",0);

  // get the parts of the string and put them into variables
  string txt = parts[0];
  string b1 = parts[1];
  string b2 = parts[2];
 
  // initialize a branch based apon the input
  branch *br = 0;
  if (b1 == BR_DEAD_END && b2 == BR_DEAD_END)
    br = new branch(txt);
  else
    br = new branch(b1,b2,txt);
  return br; 
}

/* 
this is a recursive algorithm to take a list of branches and organize a single tree

Basic Explanation:
this takes a list of nodes, indents, and an indent to start at. It finds two nodes that have the target indent, which is the starting indent plus one. It then splits the lists into two different lists, one for each node, and recurses the function with those two lists. However, if the list consists of only one node, it just returns that node, ending the recursion.
*/
branch *constructTree(vector<branch *> br_v, vector<int> indent_v, int indent) {
  // get the indent we want to find and the base node
  int targetIndent = indent + 1;
  branch *target = br_v[0];

  // if the list only has one element, return that element
  if (br_v.size() == 1) {
    return target;
  }

  branch *br1 = NULL;
  branch *br2 = NULL;
  int br1_index = -1;
  int br2_index = -1;

  // loop through the lists, try and find two nodes with a matching target indent
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

  // if we can't find one node with the target indent, the list is most likely improperly formatted- just return the base node
  if (br1_index == -1 || br2_index == -1) {
    return target;
  }

  // This code determines two iterators (first and last) by using the indexes we declared above, then copies that section of the node list using those iterators and puts it into the sec1 variable
  vector<branch *>::const_iterator first = br_v.begin() + br1_index;
  vector<branch *>::const_iterator last = br_v.begin() + br2_index;
  vector<branch *> sec1(first,last);
  
  // same thing, but for sec2
  vector<branch *> sec2;
  first = br_v.begin() + br2_index;
  last = br_v.begin() + br_v.size();
  sec2 = vector<branch *>(first,last);

  // this now creates a sublist with the indents, using the same technique as above
  vector<int>::const_iterator i_first = indent_v.begin() + br1_index;
  vector<int>::const_iterator i_last = indent_v.begin() + br2_index;
  vector<int> i_sec1(i_first,i_last);

  // same thing, but for the second indent list
  vector<int> i_sec2(0);
    i_first = indent_v.begin() + br2_index;
    i_last = indent_v.begin() + br_v.size();
    i_sec2 = vector<int>(i_first,i_last);

  // we now use these lists the recurse the function, thus creating a node tree
  br1 = constructTree(sec1,i_sec1,targetIndent);
  br2 = constructTree(sec2,i_sec2,targetIndent);

  // determine if the trees begin with dead ends  
  int br1_isDeadEnd = brIsDeadEnd(*(sec1[0]));
  int br2_isDeadEnd = brIsDeadEnd(*(sec2[0]));

  // if the new branches aren't dead ends, we add them to our root banch
  if (br1_isDeadEnd == 0) target->setBranch1(br1);
  if (br2_isDeadEnd == 0) target->setBranch2(br2);

  // return the target, finishing the recursion
  return target;
}

// convert a string to a branch
branch *brFromString(string str) {
  // declare some variables
  istringstream f(str);
  string line;
  vector<branch *> branches(0);
  vector<int> indents(0);
  
  // use the stringstream we just made to get a line-by-line representation of the string
  while (getline(f,line)) {
    // convert each line to a string, then put the string and the indent in their lists
    int indent = getLineIndent(line);
    branches.push_back(rawFromString(line,indent));
    indents.push_back(indent);
  }

  // create the tree
  branch *root = constructTree(branches,indents,0);

  return root;
}

// basic recursive function for converting a branch to the string
string brToStringInternal(branch *br, int indent) {
  // add indent
  string str;
  for (int i = 0; i < indent; i++)
    str += " ";

  // set text1 and text2 (set both to dead ends if the branch is an ending)
  string text1 = br->getText1();
  string text2 = br->getText2();
  if (br->isEnding()) {
    text1 = BR_DEAD_END;
    text2 = BR_DEAD_END;
  }
  
  // append all the node's properties onto the string
  str += br->getMainText();
  str += "/";
  str += text1;
  str += "/";
  str += text2;
  str += "\n";

  // if the branch is isolated, return the string right now
  if (br->hasBranch1() == 0 && br->hasBranch2() == 0)
    return str;

  branch dead_end (BR_DEAD_END,BR_DEAD_END,BR_DEAD_END);

  // append the first branch onto the string
  if (br->hasBranch1())
    str += brToStringInternal(br->getBranch1(),indent + 1);
  else if (br->hasBranch2())
    str += brToStringInternal(&(dead_end),indent + 1);

  // append the second branch onto the string
  if (br->hasBranch2())
    str += brToStringInternal(br->getBranch2(),indent + 1);
  else if (br->hasBranch1())
    str += brToStringInternal(&(dead_end),indent + 1);
  
 // return the string
  return str;
}

// convert a branch to a string
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
