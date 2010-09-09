/**
 * ADBList.cpp - An ADBTable hybrid class that simulates a linked list.
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ADB.h>
#include "bdes.h"




ADBList::ADBList(
  const char *Table,
  const char *Name,
  const char *User,
  const char *Pass,
  const char *Host
) : ADBTable (Table, Name, User, Pass, Host)
{
    keyList  = NULL;
    totKeys  = 0;
    curKeyNo = 0;
}

ADBList::~ADBList()
{
    if (keyList) {
        free(keyList);
        keyList = NULL;
    }
}

/*
** ADBList::getList()  - Performs a query on the specified table and gets the
**                       list of primary keys for it.
*/

long ADBList::getList(const char *listQuery)
{
    long    retVal = 0;
    
    if (keyList) {
        free(keyList);
        keyList = NULL;
    }
    
    totKeys  = 0;
    curKeyNo = 0;

    if (numColumns) {
        char *myListQuery = NULL;
        if (listQuery) {
            myListQuery = (char *) calloc(strlen(listQuery)+512, sizeof(char));
            strcpy(myListQuery, listQuery);
        } else {
            myListQuery = (char *) calloc(256, sizeof(char));
        }
        query("SELECT %s FROM %s %s", 
          columnDefs[primaryKeyColumn]->ColumnName(),
          TableName,
          myListQuery
        );
        
        if (rowCount) {
            totKeys = rowCount;
            retVal  = rowCount;

            keyList = (long *) calloc(totKeys+1, sizeof(long));
            while (getrow()) {
                keyList[curKeyNo] = atol(curRow[0]);
                curKeyNo++;
            }
            first();
        }

        free(myListQuery);
    }
    
    return retVal;
}

/*
** ADBList::first() - Loads the first row from the database and adjusts 
**                    our pointer.
**
**                    Returns the primary key value for the row if 
**                    successful, or 0 if we weren't.
*/

long ADBList::first(void)
{
    long    retVal = 0;
    if (totKeys) {
        curKeyNo = 0;
        retVal   = keyList[curKeyNo];
        get(keyList[retVal]);
    }
    return retVal;
}

/*
** ADBList::last() - Loads the the last row from the database and adjusts 
**                   our pointer.
**
**                   Returns the primary key value for the row if 
**                   successful, or 0 if we weren't.
*/

long ADBList::last(void)
{
    long    retVal = 0;
    if (totKeys) {
        curKeyNo = totKeys - 1;
        retVal   = keyList[curKeyNo];
        get(keyList[retVal]);
    }
    return retVal;
}

/*
** ADBList::prev() - Loads the the previous row from the database and adjusts 
**                   our pointer.
**
**                   Returns the primary key value for the row if 
**                   successful, or 0 if we weren't.
*/

long ADBList::prev(void)
{
    long    retVal = 0;
    if (totKeys) {
        if (curKeyNo > 0) {
            curKeyNo--;
            retVal   = keyList[curKeyNo];
            get(keyList[retVal]);
        }
    }
    return retVal;
}

/*
** ADBList::next() - Loads the the next row from the database and adjusts 
**                   our pointer.
**
**                   Returns the primary key value for the row if 
**                   successful, or 0 if we weren't.
*/

long ADBList::next(void)
{
    long    retVal = 0;
    if (totKeys) {
        if (curKeyNo < totKeys - 1) {
            curKeyNo++;
            retVal   = keyList[curKeyNo];
            get(keyList[retVal]);
        }
    }
    return retVal;
}



