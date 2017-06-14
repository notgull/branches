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
