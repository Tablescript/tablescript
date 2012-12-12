/* ExpressionStatement.cpp

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

#include "ExpressionStatement.h"
#include "Expression.h"
#include "Interpreter.h"
#include "Object.h"

namespace TS
{

	// Constructor
	//
	ExpressionStatement::ExpressionStatement( int lineNumber, Expression *expression )
		: Statement( lineNumber ),
		expression_( expression )
	{
	}

	// Copy Constructor
	//
	ExpressionStatement::ExpressionStatement( const ExpressionStatement &es )
		: Statement( es )
	{

		expression_ = es.expression_->clone();
	}

	// Destructor
	//
	ExpressionStatement::~ExpressionStatement()
	{

		delete expression_;
	}

	// clone()
	//
	Statement *ExpressionStatement::clone() const
	{

		return new ExpressionStatement( *this );
	}

	// execute()
	//
	int ExpressionStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Object *result = expression_->evaluate( interpreter, scope ); // new reference
		if ( !result )
			return EXEC_FAIL;

		// clean up
		result->decRef();

		return EXEC_SUCCESS;
	}
}
