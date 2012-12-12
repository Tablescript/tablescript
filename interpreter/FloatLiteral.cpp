/* FloatLiteral.cpp

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

#include "FloatLiteral.h"
#include "Float.h"

namespace TS
{

	// Constructor
	//
	FloatLiteral::FloatLiteral( int lineNumber, float value )
		: Expression( lineNumber ),
		value_( value )
	{
	}

	// Copy Constructor
	//
	FloatLiteral::FloatLiteral( const FloatLiteral &fl )
		: Expression( fl ),
		value_( fl.value_ )
	{
	}

	// Destructor
	//
	FloatLiteral::~FloatLiteral()
	{
	}

	// clone()
	//
	Expression *FloatLiteral::clone() const
	{

		return new FloatLiteral( *this );
	}

	// evaluate()
	//
	Object *FloatLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		return new Float( value_ ); // new reference
	}

}
