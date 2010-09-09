/**
 * StrTools.h - String manipulation tools.
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

#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <defalloc.h>
// #include <stl.h>
//#include <complex>
// #include <strstream>
#include <iostream>
using namespace std;
#include <ext/hash_map>
#include <string>


namespace __gnu_cxx
{
    /*
    template<> struct hash< std::string >
    {
        size_t operator()( const std::string& x ) const
        {
            return hash< const char* >()( x.c_str() );
        }
    };
    */

// String Map Dictionary comparison
struct _StrDictEQ
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) == 0;
    };
};

typedef hash_map<const char *, string, hash<const char *>, _StrDictEQ> StringMap;

typedef hash_map<int, string, hash<int> > StrSplitMap;
} 

void        StripWhiteSpace(string &src);
void        SimplifyWhiteSpace(string &src);
int         StrSplit(const char *src, const char *delim, __gnu_cxx::StrSplitMap &map, int maxParts = 0);
int         StringSplit(string &src, const char *delim, __gnu_cxx::StrSplitMap &map, int maxParts = 0);
const char *WordWrap(const char *src, size_t cols = 72);

void    StringMapAdd(__gnu_cxx::StringMap &map, const char *key, const char *val);

bool        normalizeDate(const char *src, char *tgt, const char *fmt = "Y-M-D");

#endif // STRTOOLS_H

