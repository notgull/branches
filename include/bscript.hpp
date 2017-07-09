/*
 * =====================================================================================
 *
 *       Filename:  bscript.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2017 07:24:11 AM
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

#ifndef BSCRIPT_H
#define BSCRIPT_H

#include <vector>
#include <string>
#include "branch.hpp"
#include "iswin.hpp"
#ifdef USING_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#endif 

using namespace std;

void bscrWrite(vector<int>,string);
vector<int> bscrRead(string);
#ifdef USING_WIN
branch *bscrFollow(vector<int>,branch *,branch *,SOCKET);
#else
branch *bscrFollow(vector<int>,branch *,branch *,int);
#endif

#endif
