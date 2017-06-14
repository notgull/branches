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
    branch(string);
    bool hasBranch1();
    bool hasBranch2();
    string getMainText();
    string getText1();
    string getText2();
   
    branch *getBranch1();
    branch *getBranch2();
  
    void setBranch1(branch *);
    void setBranch2(branch *);
  
    string toString();
    string printWorthy();
    branch clone();
    branch trim();
};

void brPrint(branch);
#endif
