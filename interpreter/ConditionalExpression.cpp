/* ConditionalExpression.cpp

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

#include "ConditionalExpression.h"
#include "Object.h"

namespace TS
{

	// Constructor
	//
	ConditionalExpression::ConditionalExpression(
			int lineNumber,
			Expression *test,
			Expression *trueValue,
			Expression *falseValue)
		: Expression( lineNumber ),
		test_( test ),
		trueValue_( trueValue ),
		falseValue_( falseValue )
	{
	}

	// Copy Constructor
	//
	ConditionalExpression::ConditionalExpression( const ConditionalExpression &ce )
		: Expression( ce )
	{

		test_ = ce.test_->clone();
		trueValue_ = ce.trueValue_->clone();
		falseValue_ = ce.falseValue_->clone();
	}

	// Destructor
	//
	ConditionalExpression::~ConditionalExpression()
	{

		delete test_;
		delete trueValue_;
		delete falseValue_;
	}

	// clone()
	//
	Expression *ConditionalExpression::clone() const
	{

		return new ConditionalExpression( *this );
	}

	// evaluate()
	//
	Object *ConditionalExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		Object *testResult = test_->evaluate( interpreter, scope ); // new reference
		if ( !testResult )
			return 0; // error already set

		Object *result;
		if ( testResult->isTrue() )
		{

			result = trueValue_->evaluate( interpreter, scope ); // new reference
			if ( !result )
			{

                // clean up
				testResult->decRef();

				return 0; // error already set
			}
		}
		else
		{

			result = falseValue_->evaluate( interpreter, scope ); // new reference
			if ( !result )
			{

                // clean up
				testResult->decRef();

				return 0; // error already set
			}
		}

		// clean up
		testResult->decRef();

		return result;
	}
}

