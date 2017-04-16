/*
 * =====================================================================================
 *
 *       Filename:  saves.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2017 09:37:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef SAVES_H
#define SAVES_H

#include "brstring.h"

int brSaveToFile(branch *br, char *filename);

branch *brLoadFromFile(char *filename);

#endif
