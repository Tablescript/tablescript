/* Statement.cpp

   TableScript
   Copyright (C) 2003 Jamie Hale

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "Statement.h"

namespace TS
{

	// Constructor
	//
	Statement::Statement( int lineNumber )
		: lineNumber_( lineNumber )
	{
	}

	// Copy Constructor
	//
	Statement::Statement( const Statement &s )
		: lineNumber_( s.lineNumber_ )
	{
	}

	// Destructor
	//
	Statement::~Statement()
	{
	}

	// getLineNumber()
	//
	int Statement::getLineNumber() const
	{

		return lineNumber_;
	}

    // isExecutionError()
    //
    bool Statement::isExecutionError( int ret )
    {

        if ( ret == EXEC_SUCCESS || ret == EXEC_EXIT )
            return false;

        return true;
    }
}

