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

#ifndef BRANCH_H
#define BRANCH_H

#include <string>
#include <vector>
using namespace std;

class branch {
  private:
    string txt;
    string b1;
    string b2;
    branch *branch1;
    branch *branch2;
    branch *prev;
  public:
    branch(string,string,string);
    bool hasBranch1();
    bool hasBranch2();
    string getMainText();
    string getText1();
    string getText2();
   
    branch *getBranch1();
    branch *getBranch2();
    branch *getPrevious();
    int countElements();
  
    void setBranch1(branch *);
    void setBranch2(branch *);
    void nullifyPrevious();
  
    string toString();
    string printWorthy();
    vector<branch *> compileToList();
    branch clone();
    branch trim();
};

void brPrint(branch);
branch *brFromString(string);
void brDeleteBranch(branch *);
#endif
