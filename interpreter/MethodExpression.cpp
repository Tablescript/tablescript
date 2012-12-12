/* MethodExpression.cpp

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

#include "MethodExpression.h"
#include "List.h"
#include "Instance.h"
#include "Function.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	MethodExpression::MethodExpression( int lineNumber, Expression *base, const std::string &methodName, ExpressionList *parameters )
		: Expression( lineNumber ),
		base_( base ),
		methodName_( methodName ),
		parameters_( parameters )
	{
	}

	// Copy Constructor
	//
	MethodExpression::MethodExpression( const MethodExpression &ce )
		: Expression( ce )
	{

		base_ = ce.base_->clone();
		methodName_ = ce.methodName_;
		parameters_ = ce.parameters_->clone();
	}

	// Destructor
	//
	MethodExpression::~MethodExpression()
	{

		delete base_;
		delete parameters_;
	}

	// clone()
	//
	Expression *MethodExpression::clone() const
	{

		return new MethodExpression( *this );
	}

	// evaluate()
	//
	Object *MethodExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// evaluate the expression to be called
		Object *baseValue = base_->evaluate( interpreter, scope ); // new reference
		if ( !baseValue )
			return 0; // error already set

		// make sure it's actually an instance
		Instance *instance = dynamic_cast< Instance * >( baseValue );
		if ( !instance )
        {

            setRuntimeError( ERROR_EXPRESSION_NOT_INSTANCE );
			return 0;
        }

		// evaluate the parameter expressions
		List *parameters = new List;
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

		// make the call - if an error occurs, result will be 0
        Object *result = instance->callMethod( interpreter, methodName_, parameters );

		// clean up
		baseValue->decRef();
		parameters->decRef();

		return result;
	}
}

