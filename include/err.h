/*
 * =====================================================================================
 *
 *       Filename:  err.h
 *
 *    Description:  For throwing errors
 *
 *        Version:  1.0
 *        Created:  03/15/2017 10:00:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef ERR_H
#define ERR_H

#ifdef __cplusplus
extern "C" {
#endif

void error(char *msg, int showErrno);

#ifdef __cplusplus
}
#endif

#endif
