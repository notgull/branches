/*
 * =====================================================================================
 *
 *       Filename:  antiswear.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/2017 01:54:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "antiswear.hpp"
#include <sstream>
#include <algorithm>
using namespace std;

vector<string> swears = {"fuck","shit","ass","bitch","cunt","damn","nigger","whore"};
vector<string> replac = {"duck","hit","brass","switch","stunt","darn","person","ur mom"};

vector<string> getSwears() { 
  return swears; 
}
vector<string> getReplacement() { return replac; }

string capitalLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
vector<int> getCapitalization(string s) {
  vector<int> base (0);
  for (char c : s) {
    int pos;
    stringstream st;
    st << c;
    if ((pos = capitalLetters.find(st.str())) != string::npos) {
      base.push_back(pos);
    }
  }
  return base;
}

string uncapitalize(string s) {
  stringstream st;
  for (char c : s) {
    st << tolower(c);
  }
  return st.str();
}

string recapitalize(string s, vector<int> caps) {
  stringstream result;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (std::find(caps.begin(), caps.end(), i) != caps.end()) {
      result << toupper(c);
    }
    else {
      result << c;
    }
  }
  return result.str();
}

string aswearFilter(string input) {
//  cout << "Input: " << input << endl;
  vector<int> capitals = getCapitalization(input);
  string mod = uncapitalize(input);
//  cout << "Uncapitalized: " << mod << endl;
  for (int i = 0; i < swears.size(); i++) {
    string sw = swears[i];
    string rp = replac[i];
    size_t pos;
    while ((pos = mod.find(sw)) != string::npos) {
      mod.replace(pos, sw.length(), rp);
    }
  }
//  cout << "Modded: " << mod << endl;
//  cout << "Recapitalized: " << recapitalize(mod,capitals) << endl;
  return recapitalize(mod,capitals);
}
