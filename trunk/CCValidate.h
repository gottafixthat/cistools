/**
 * CCValidate - Credit card validation functions.
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


#ifndef CCVALIDATE_H
#define CCVALIDATE_H

// Credit card response codes.
#define CCARD_UNK        0          // Unknown error
#define CCARD_OK         1          // All is fine
#define CCARD_INVPRE    -1          // Invalid card number (prefix error)
#define CCARD_INVNUM    -2          // Invalid card number (length)
#define CCARD_INVMOD    -3          // Failed the MOD10 test.
#define CCARD_EXP       -4          // Card has expired
#define CCARD_INVEXP    -5          // Card has an invalid expiration date.

// Credit card types
#define CCTYPE_UNKNOWN  -1          // Don't do specific validation
#define CCTYPE_MC       0           // MasterCard
#define CCTYPE_VISA     1           // Visa
#define CCTYPE_AMEX     2           // American Express
#define CCTYPE_DINERS   3           // Diners Club
#define CCTYPE_DISC     4           // Discover


int  creditCardValid(int cardType, const char *cardNo, const char *expDate);
const char *cardTypeString(int cardType);


#endif  // CCVALIDATE_H
