/*
 * =====================================================================================
 *
 *       Filename:  branch.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:27:08 AM
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

// this file contains the branch class and its functions
#ifndef BRANCH_H
#define BRANCH_H

// import the string and vector classes
#include <string>
#include <vector>
using namespace std;

class branch {
  // inner variables
  private:
    // main text, then text
    string txt;
    string b1;
    string b2;
    // pointers to other branches
    branch *branch1;
    branch *branch2;
    branch *prev;
    // is an ending
    bool isEnd;
  // functions
  public:
    // constructors for regular and ending branches, respectively
    branch(string,string,string);
    branch(string);
    // functions to retreive inner variables
    bool hasBranch1();
    bool hasBranch2();
    string getMainText();
    string getText1();
    string getText2();
    bool isEnding();
   
    // functions to retrieve pointers
    branch *getBranch1();
    branch *getBranch2();
    branch *getPrevious();

    // count all elements in the branch
    int countElements();
  
    // set the pointers
    void setBranch1(branch *);
    void setBranch2(branch *);
    void nullifyPrevious();
    // note: i only allow the nullification of previous, so nobody can change its value
  
    // convert branch to string
    string toString();
   

    // convert branch to a nice format
    string printWorthy();
    // convert branch to a list
    vector<branch *> compileToList();
    // clone the branch
    branch clone();
    // get an isolated branch
    branch trim();
};

// misc functions
void brPrint(branch);
branch *brFromString(string);
void brDeleteBranch(branch *);
#endif
