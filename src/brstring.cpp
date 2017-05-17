/*
 * =====================================================================================
 *
 *       Filename:  brstring.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/02/2017 04:30:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "brstring.hpp"
#include "splitstr.hpp"
#include "string_helper.hpp"
#include "err.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define BR_DEAD_END "BR_DEAD_END"

int brIsDeadEnd(branch *br) {
  string txt = getStringFrom(brGetText(br));
  string b1 = getStringFrom(brGetBranch1Text(br));
  string b2 = getStringFrom(brGetBranch2Text(br));

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
 
  return brCreate(getPointerFrom(b1),getPointerFrom(b2),getPointerFrom(txt));
}

branch *constructTree(vector<branch *> br_v, vector<int> indent_v, int indent) {
#ifdef DEBUG
  cout << "-- Entering constructTree --" << endl;
  cout << "The branches used are:" << endl;
  for (branch *br : br_v)
    brPrint(br);
  cout << "The indents used are: ";
  for (int i : indent_v)
    cout << i;
  cout << endl;
  cout << "The indent var is " << indent << endl << "---------------------" << endl;
#endif
  int targetIndent = indent + 1;
  branch *target = br_v[0];
#ifdef DEBUG
  cout << "TargetIndent is " << targetIndent << " and target has been determined as:" << endl;
  brPrint(target);
#endif

  if (br_v.size() == 1) {
#ifdef DEBUG
    cout << "br_v size is 1, returning..." << endl;
#endif
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

#ifdef DEBUG
  cout << "Section 1 determined as:" << endl;
  for (branch *br : sec1)
    brPrint(br);
#endif
  
  vector<branch *> sec2;
    first = br_v.begin() + br2_index;
    last = br_v.begin() + br_v.size();
    sec2 = vector<branch *>(first,last);
#ifdef DEBUG
    cout << "Section 2 determined as:" << endl;
    for (branch *br : sec2)
      brPrint(br);
#endif

  vector<int>::const_iterator i_first = indent_v.begin() + br1_index;
  vector<int>::const_iterator i_last = indent_v.begin() + br2_index;
  vector<int> i_sec1(i_first,i_last);
#ifdef DEBUG
  cout << "Indent Section 1 determined as: ";
  for (int i : i_sec1)
    cout << i << " ";
  cout << endl;
#endif

  vector<int> i_sec2(0);
    i_first = indent_v.begin() + br2_index;
    i_last = indent_v.begin() + br_v.size();
    i_sec2 = vector<int>(i_first,i_last);
#ifdef DEBUG
    cout << "Indent Section 2 determined as: ";
    for (int i : i_sec2)
      cout << i;
    cout << endl;
#endif

#ifdef DEBUG

  cout << "Recursing constructTree..." << endl;
#endif

  br1 = constructTree(sec1,i_sec1,targetIndent);
  br2 = constructTree(sec2,i_sec2,targetIndent);
  
  int br1_isDeadEnd = brIsDeadEnd(sec1[0]);
  int br2_isDeadEnd = brIsDeadEnd(sec2[0]);

#ifdef DEBUG
  cout << "br1_isDeadEnd is " << br1_isDeadEnd << " and br2_isDeadEnd is " << br2_isDeadEnd << endl;
#endif

#ifdef DEBUG
  cout << "Setting branches..." << endl;
#endif
  if (br1_isDeadEnd == 0) brSetBranch1(target,br1);
  if (br1_isDeadEnd == 0) brSetBranch2(target,br2);

#ifdef DEBUG
  cout << "constructTree at indent " << indent << " finished successfully" << endl;
#endif

  return brDup(target);
}

branch *brFromString(char *input) {
  if (input == 0 || input == NULL)
    error("String cannot be null",0);

  string str(input);

 vector<string> newlines = splitString(str,'\n');
 vector<branch *> branches(0);
  vector<int> indents(0);
  
  for (string line : newlines) {
     int indent = getLineIndent(line);
     branches.push_back(rawFromString(line,indent));
     indents.push_back(indent);
  }

  branch *root = constructTree(branches,indents,0);

  return root;
}

char *brToStringInternal(branch *br, int indent) {
  string str;
  for (int i = 0; i < indent; i++)
    str += " ";

  str += brGetText(br);
  str += "/";
  str += brGetBranch1Text(br);
  str += "/";
  str += brGetBranch2Text(br);
  str += "\n";

  if (brHasBranch1(br) == 0 && brHasBranch2(br) == 0)
    return getPointerFrom(str);

  branch *dead_end = brCreate(BR_DEAD_END,BR_DEAD_END,BR_DEAD_END);

  if (brHasBranch1(br) != 0)
    str += brToStringInternal(brGetBranch1(br),indent + 1);
  else if (brHasBranch2(br) != 0)
    str += brToStringInternal(dead_end,indent + 1);

  if (brHasBranch2(br) != 0)
    str += brToStringInternal(brGetBranch2(br),indent + 1);
  else if (brHasBranch1(br) != 0)
    str += brToStringInternal(dead_end,indent + 1);
  
  return getPointerFrom(str);
}

char *brToString(branch *br) {
  brToStringInternal(br,0);
}

