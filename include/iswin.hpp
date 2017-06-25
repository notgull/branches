/*
 * =====================================================================================
 *
 *       Filename:  iswin.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/22/2017 04:17:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#ifndef IS_WIN_H
#define IS_WIN_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#define USING_WIN

#endif
#endif
