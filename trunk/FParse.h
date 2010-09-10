/**
 * FParse.h - Generic file parsing routines.
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

#ifndef FPARSE_H
#define FPARSE_H

// Standard includes
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

// STL includes
using namespace std;
#include <map>
#include <ext/hash_map>
#include <list>
#include <string>


namespace __gnu_cxx
{
struct fparsedeq 
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) == 0;
    };
};

// StringDict is our basic lookup hash.
//typedef hash_map<const char *, string, hash<const char *>, fparsedeq, single_client_alloc> FPStringDict;
typedef hash_map<const char *, string, hash<const char *>, fparsedeq> FPStringDict;
typedef list<FPStringDict> FPStringList;
typedef hash_map<const char *, FPStringList, hash<const char *>, fparsedeq> FPStringListList;
typedef hash_map<int, string, hash<int> >  FPIntDict;
}

class FParser {
public:
    FParser();
    ~FParser();

    // Utility functions
    void        reset();
    void        setVariableMarkers(const char *newOpen, const char *newClose);
    void        setStripComments(bool newVal);
    
    // Parsing functions
    void        setPath(const char *newPath);
    int         dumpFile(const char *fName, FILE *outfp = stdout);
    void        parseFile(const char *fName, FILE *outfp = stdout);
    char       *parseFileToMem(const char *fName);
    void        set(const char *, const char *, bool escQuotes = true);
    const char *get(const char *);

    // List Functions
    // newList is not needed as insertion is automatic.
    void        addRow(const char *listName);
    void        addColumn(const char *key, const char *val);

    void        _dumpDebugInfo();

protected:
    void        parseBlock(string &block);
    void        parseListBlock(string &sourceblock, const char *listName);
    int         loadFile(const char *fName, string &dest);

    int         _FPSplitString(const char *src, const char *delim, __gnu_cxx::FPIntDict &map);

    void        storeVar(__gnu_cxx::FPStringDict &dict, const char *key, const char *val);

    char                fPath[1024];
    char                openStr[1024];
    char                closeStr[1024];
    int                 openStrLen;
    int                 closeStrLen;
    bool                stripComments;
    pid_t               myPID;
    __gnu_cxx::FPStringDict        simpleVars;
    __gnu_cxx::FPStringListList    lists;
    char                curListName[1024];
};


#endif  // FPARSE_H


