/* Identifier.cpp

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

#include "Identifier.h"
#include "Scope.h"
#include "Interpreter.h"
#include "LHSObject.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	Identifier::Identifier( int lineNumber, const std::string &name )
		: Expression( lineNumber ),
		name_( name )
	{
	}

	// Copy Constructor
	//
	Identifier::Identifier( const Identifier &i )
		: Expression( i ),
		name_( i.name_ )
	{
	}

	// Destructor
	//
	Identifier::~Identifier()
	{
	}

	// clone()
	//
	Expression *Identifier::clone() const
	{

		return new Identifier( *this );
	}

	// evaluate()
	//
	Object *Identifier::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		Object *result = scope->getSymbol( name_ ); // new reference
		if ( !result )
		{

			setRuntimeError( "Symbol '%s' not defined.", name_.c_str() );
			return 0;
		}

		return result;
	}

	// evaluateAsLHS()
	//
	LHSObject *Identifier::evaluateAsLHS( Interpreter *interpreter, Scope *scope )
	{

		return new LHSIdentifier( name_ );
	}
}

