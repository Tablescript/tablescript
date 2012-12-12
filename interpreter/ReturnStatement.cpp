/* ReturnStatement.cpp

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

#include "ReturnStatement.h"
#include "Object.h"
#include "Expression.h"
#include "Scope.h"
#include "Interpreter.h"
#include "None.h"

namespace TS
{

	// Constructor
	//
	ReturnStatement::ReturnStatement( int lineNumber, Expression *expression )
		: Statement( lineNumber ),
		expression_( expression )
	{
	}

	// Copy Constructor
	//
	ReturnStatement::ReturnStatement( const ReturnStatement &rs )
		: Statement( rs )
	{

		expression_ = rs.expression_->clone();
	}

	// Destructor
	//
	ReturnStatement::~ReturnStatement()
	{

		delete expression_;
	}

	// clone()
	//
	Statement *ReturnStatement::clone() const
	{

		return new ReturnStatement( *this );
	}

	// execute()
	//
	int ReturnStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Object *result;

		if ( expression_ )
		{

			result = expression_->evaluate( interpreter, scope );
			if ( !result )
				return EXEC_FAIL; // error already set
		}
		else
		{

			none->addRef();
			result = none;
		}

		scope->setReturnValue( result );

		return EXEC_RETURN;
	}
}

