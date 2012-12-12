/* IntegerLiteral.cpp

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

#include "IntegerLiteral.h"
#include "Integer.h"

namespace TS
{

	// Constructor
	//
	IntegerLiteral::IntegerLiteral( int lineNumber, int value )
		: Expression( lineNumber ),
		value_( value )
	{
	}

	// Copy Constructor
	//
	IntegerLiteral::IntegerLiteral( const IntegerLiteral &il )
		: Expression( il ),
		value_( il.value_ )
	{
	}

	// Destructor
	//
	IntegerLiteral::~IntegerLiteral()
	{
	}

	// clone()
	//
	Expression *IntegerLiteral::clone() const
	{

		return new IntegerLiteral( *this );
	}

	// evaluate()
	//
	Object *IntegerLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		return new Integer( value_ ); // new reference
	}

}
