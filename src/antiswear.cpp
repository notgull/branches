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
using namespace std;

vector<string> swears = {"fuck","shit","ass","bitch","cunt","damn","nigger","whore"};
vector<string> replac = {"duck","hit","brass","switch","stunt","darn","person","ur mom"};

vector<string> getSwears() { 
  return swears; 
}
vector<string> getReplacement() { return replac; }

string aswearFilter(string input) {
  string mod = input;
  for (int i = 0; i < swears.size(); i++) {
    string sw = swears[i];
    string rp = replac[i];
    size_t pos;
    while ((pos = mod.find(sw)) != string::npos) {
      mod.replace(pos, sw.length(), rp);
    }
  }
  return mod;
}
