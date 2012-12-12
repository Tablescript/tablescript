/* DiceLiteral.cpp

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

#include "DiceLiteral.h"
#include "Integer.h"
#include "Dice.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	DiceLiteral::DiceLiteral( int lineNumber, const std::string &value )
		: Expression( lineNumber ),
		value_( value )
	{
	}

	// Copy Constructor
	//
	DiceLiteral::DiceLiteral( const DiceLiteral &dl )
		: Expression( dl ),
		value_(dl.value_)
	{
	}

	// Destructor
	//
	DiceLiteral::~DiceLiteral()
	{
	}

	// clone()
	//
	Expression *DiceLiteral::clone() const
	{

		return new DiceLiteral( *this );
	}

	// evaluate()
	//
	Object *DiceLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		unsigned int result = rollDice( value_);
		if ( result == ROLLERROR )
		{

			setRuntimeError( ERROR_INVALID_DICE_LITERAL_X, value_.c_str() );
			return 0;
		}

		return new Integer( result ); // new reference
	}
}
