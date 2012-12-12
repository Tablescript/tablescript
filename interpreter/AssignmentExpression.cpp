/* AssignmentExpression.cpp

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

#include "AssignmentExpression.h"
#include "LHSObject.h"
#include "Object.h"

namespace TS
{

	// Constructor
	//
	AssignmentExpression::AssignmentExpression( int lineNumber, Expression *lhs, Expression *rhs )
		: Expression( lineNumber ),
		lhs_( lhs ),
		rhs_( rhs )
	{
	}

	// Copy Constructor
	//
	AssignmentExpression::AssignmentExpression( const AssignmentExpression &ae )
		: Expression( ae )
	{

		lhs_ = ae.lhs_->clone();
		rhs_ = ae.rhs_->clone();
	}

	// Destructor
	//
	AssignmentExpression::~AssignmentExpression()
	{

		delete lhs_;
		delete rhs_;
	}

	// clone()
	//
	Expression *AssignmentExpression::clone() const
	{

		return new AssignmentExpression( *this );
	}

	// evaluate()
	//
	Object *AssignmentExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// evaluate the left-hand side maintaining the context
		LHSObject *lhsValue = lhs_->evaluateAsLHS( interpreter, scope );
		if ( !lhsValue )
			return 0; // error already set

		// evaluate the right-hand side
		Object *rhsValue = rhs_->evaluate( interpreter, scope ); // new reference
		if ( !rhsValue )
		{

            // clean up
			delete lhsValue;

			return 0; // error already set
		}

		// dispatch the assignment
		if ( !lhsValue->assign( interpreter, scope, rhsValue ) )
		{

            // clean up
			delete lhsValue;
            rhsValue->decRef();

			return 0; // error already set
		}

		// clean up
		delete lhsValue;

		return rhsValue;
	}
}

