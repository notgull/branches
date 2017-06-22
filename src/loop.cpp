/*
 * =====================================================================================
 *
 *       Filename:  loop.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2017 10:41:25 AM
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

#include "loop.hpp"

int _looping = 0;

void beginLoop() {
  _looping = 1;
}

int isLooping() {
  return _looping;
}

void stopLoop() {
  _looping = 0;
}
