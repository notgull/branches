/*
 * =====================================================================================
 *
 *       Filename:  antiswear.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/2017 01:52:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef ANTISWEAR_HPP
#define ANTISWEAR_HPP

#include <vector>
#include <string>
using namespace std;

vector<string> getSwears();
vector<string> getReplacement();
string aswearFilter(string input);

#endif
