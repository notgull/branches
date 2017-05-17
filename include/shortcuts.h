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

#ifdef __cplusplus
extern "C" {
#endif

void newline();

void shell_tx();

int yesno(char *question);

void getInput(char *inputGet, char *output);

int check_file(char *filename);

#ifdef __cplusplus
}
#endif

#endif
