/**
 * bdes.h - Basic DES encryption functions.
 *
 **************************************************************************
 * Written by R. Marc Lewis, 
 *   Copyright 1998-2010, R. Marc Lewis (marc@CheetahIS.com)
 *   Copyright 2007-2010, Cheetah Information Systems Inc.
 **************************************************************************
 *
 * This file is part of cistools.
 *
 * cistools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cistools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cistools.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef BDES2_H
#define BDES2_H

#ifdef __cplusplus
extern "C" {
#endif

void set_user_key(unsigned char *UserKey);

void encrypt_string(unsigned char *source, unsigned char *dest, int UseUser);
int  decrypt_string(unsigned char *source, unsigned char *dest, int UseUser);

void encrypt_string2(unsigned char *source, unsigned char *dest);
int  decrypt_string2(unsigned char *source, unsigned char *dest);

void encrypt_string2user(unsigned char *source, unsigned char *dest);
int  decrypt_string2user(unsigned char *source, unsigned char *dest);


/* These are internal routines and should not be called directly. */
void encrypt2(unsigned char *source, unsigned char *dest, unsigned char *Key3);
int  decrypt2(unsigned char *source, unsigned char *dest, unsigned char *Key3);

#ifdef __cplusplus
}
#endif

#endif
