/* CallExpression.cpp

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

#include "CallExpression.h"
#include "List.h"
#include "Scope.h"
#include "Interpreter.h"

namespace TS
{

	// Constructor
	//
	CallExpression::CallExpression( int lineNumber, Expression *base, ExpressionList *parameters )
		: Expression( lineNumber ),
		base_( base ),
		parameters_( parameters )
	{
	}

	// Copy Constructor
	//
	CallExpression::CallExpression( const CallExpression &ce )
		: Expression( ce )
	{

		base_ = ce.base_->clone();
		parameters_ = ce.parameters_->clone();
	}

	// Destructor
	//
	CallExpression::~CallExpression()
	{

		delete base_;
		delete parameters_;
	}

	// clone()
	//
	Expression *CallExpression::clone() const
	{

		return new CallExpression( *this );
	}

	// evaluate()
	//
	Object *CallExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// evaluate the expression to be called
		Object *baseValue = base_->evaluate( interpreter, scope ); // new reference
		if ( !baseValue )
			return 0; // error already set

        // evaluate parameters
		List *parameters = new List; // new reference
		ExpressionList::iterator i, iEnd = parameters_->end();
		for ( i = parameters_->begin(); i != iEnd; ++i )
		{

			Object *parameterValue = ( *i )->evaluate( interpreter, scope ); // new reference
			if ( !parameterValue )
			{

                // clean up
				baseValue->decRef();
				parameters->decRef();

				return 0; // error already set
			}

			parameters->append( parameterValue ); // takes reference
			parameterValue->decRef();
		}

        // function calls happen in their own scope
        Scope functionScope( interpreter->getGlobalScope() );

		// make the call - if an error occurs, result will be 0
		Object *result = baseValue->call( interpreter, &functionScope, parameters, "" ); // new reference

		// clean up
		baseValue->decRef();
		parameters->decRef();

		return result;
	}
}

