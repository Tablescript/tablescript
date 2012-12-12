/* IncDecExpression.cpp

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

#include "IncDecExpression.h"
#include "LHSObject.h"
#include "Integer.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	IncDecExpression::IncDecExpression( int lineNumber, enum PExprTag tag, Expression *base )
		: Expression( lineNumber ),
		tag_( tag ),
		base_( base )
	{
	}

	// Copy Constructor
	//
	IncDecExpression::IncDecExpression( const IncDecExpression &ide )
		: Expression( ide ),
		tag_( ide.tag_ )
	{

		base_ = ide.base_->clone();
	}

	// Destructor
	//
	IncDecExpression::~IncDecExpression()
	{

		delete base_;
	}

	// clone()
	//
	Expression *IncDecExpression::clone() const
	{

		return new IncDecExpression( *this );
	}

	// evaluate()
	//
	Object *IncDecExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// evaluate base as a left-hand side
		LHSObject *lhs = base_->evaluateAsLHS( interpreter, scope );
		if ( !lhs )
			return 0; // error already set

		// get the actual value of the base
		Object *value = lhs->evaluate( interpreter, scope ); // new reference
		if ( !value )
		{

            // clean up
			delete lhs;

			return 0; // error already set
		}

		// make sure we're working with an integer
		Integer *integer = dynamic_cast< Integer * >( value ); // steals reference
		if ( !integer )
		{

            // clean up
			delete lhs;
			value->decRef();

			setRuntimeError( ERROR_INCDEC_ONLY_FOR_INTEGERS );
			return 0;
		}

		Object *newValue;
		Object *result;

		switch ( tag_ )
		{

		case ET_PRE_INC:
			newValue = new Integer( integer->getValue() + 1 ); // new reference

			// take a new reference to the new value
			newValue->addRef();
			result = newValue;

			break;

		case ET_PRE_DEC:
			newValue = new Integer( integer->getValue() - 1 ); // new reference

			// take a new reference to the new value
			newValue->addRef();
			result = newValue;

			break;

		case ET_POST_INC:
			newValue = new Integer( integer->getValue() + 1 ); // new reference

			// take a new reference to the old value
			integer->addRef();
			result = integer;

			break;

		case ET_POST_DEC:
			newValue = new Integer( integer->getValue() - 1 ); // new reference

			// take a new reference to the old value
			integer->addRef();
			result = integer;

			break;

		default:
			setRuntimeError( ERROR_INVALID_EXPRESSION_TAG, tag_ );
			break;
		}

		// assign the new value
		if ( !lhs->assign( interpreter, scope, newValue ) )
		{

			result->decRef();
			result = 0;
		}

		// clean up
		delete lhs;
		integer->decRef();
		newValue->decRef();

		return result;
	}
}

