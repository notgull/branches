/*
 * =====================================================================================
 *
 *       Filename:  shortcuts.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/16/2017 08:49:36 AM
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

#ifndef SHORTCUTS_H
#define SHORTCUTS_H
#include <string>
using namespace std;

void newline();

void shell_tx();

int yesno(int nullfirst,string question);

int check_file(string filename);
#endif
