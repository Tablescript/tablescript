/* ElementExpression.cpp

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

#include "ElementExpression.h"
#include "Object.h"
#include "LHSObject.h"

namespace TS
{

	// Constructor
	//
	ElementExpression::ElementExpression( int lineNumber, Expression *subject, Expression *key )
		: Expression( lineNumber ),
		subject_( subject ),
		key_( key )
	{
	}

	// Copy Constructor
	//
	ElementExpression::ElementExpression( const ElementExpression &ee )
		: Expression( ee )
	{

		subject_ = ee.subject_->clone();
		key_ = ee.key_->clone();
	}

	// Destructor
	//
	ElementExpression::~ElementExpression()
	{

		delete subject_;
		delete key_;
	}

	// clone()
	//
	Expression *ElementExpression::clone() const
	{

		return new ElementExpression( *this );
	}

	// evaluate()
	//
	Object *ElementExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		Object *subject = subject_->evaluate( interpreter, scope ); // new reference
		if ( !subject )
			return 0; // error already set

		Object *key = key_->evaluate( interpreter, scope ); // new reference
		if ( !key )
		{

            // clean up
			subject->decRef();

			return 0; // error already set
		}

		Object *result = subject->getElement( scope, key ); // new reference
		if ( !result )
		{

            // clean up
			subject->decRef();
			key->decRef();

			return 0; // error already set
		}

		// clean up
		subject->decRef();
		key->decRef();

		return result;
	}

	// evaluateLHS()
	//
	LHSObject *ElementExpression::evaluateLHS( Interpreter *interpreter, Scope *scope )
	{

		Object *subject = subject_->evaluate( interpreter, scope ); // new reference
		if ( !subject )
			return 0; // error already set

		Object *key = key_->evaluate( interpreter, scope ); // new reference
		if ( !key )
		{

            // clean up
			subject->decRef();

			return 0; // error already set
		}

		return new LHSElement( subject, key ); // steals both references
	}
}

