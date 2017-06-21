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
  public:
    branch(string,string,string);
    bool hasBranch1();
    bool hasBranch2();
    string getMainText();
    string getText1();
    string getText2();
   
    branch *getBranch1();
    branch *getBranch2();
    int countElements();
  
    void setBranch1(branch *);
    void setBranch2(branch *);
  
    string toString();
    string printWorthy();
    vector<branch *> compileToList();
    branch clone();
    branch trim();
};

void brPrint(branch);
branch *brFromString(string);
#endif
