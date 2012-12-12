/* BinaryExpression.cpp

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

#include "BinaryExpression.h"
#include "Object.h"
#include "Integer.h"
#include "Error.h"

namespace TS
{

	// Constructor
	//
	BinaryExpression::BinaryExpression( int lineNumber, enum PExprTag tag, Expression *left, Expression *right )
		: Expression( lineNumber ),
		tag_( tag ),
		left_( left ),
		right_( right )
	{
	}

	// Copy Constructor
	//
	BinaryExpression::BinaryExpression( const BinaryExpression &be )
		: Expression( be ),
		tag_( be.tag_)
	{

		left_ = be.left_->clone();
		right_ = be.right_->clone();
	}

	// Destructor
	//
	BinaryExpression::~BinaryExpression()
	{

		delete left_;
		delete right_;
	}

	// clone()
	//
	Expression *BinaryExpression::clone() const
	{

		return new BinaryExpression( *this );
	}

	// evaluate()
	//
	Object *BinaryExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		// evaluate the left side of the operator
		Object *leftValue = left_->evaluate( interpreter, scope ); // new reference
		if ( !leftValue )
			return 0; // error already set

		// handle short-circuit logic
		if ( ( tag_ == ET_AND ) && ( !leftValue->isTrue() ) )
		{

            // clean up
			leftValue->decRef();

			return new Integer( 0 ); // new reference
		}
		if ( ( tag_ == ET_OR ) && ( leftValue->isTrue() ) )
		{

            // clean up
			leftValue->decRef();

			return new Integer( 1 ); // new reference
		}

		// evaluate the right side of the operator
		Object *rightValue = right_->evaluate( interpreter, scope ); // new reference
		if ( !rightValue )
		{

            // clean up
			leftValue->decRef();

			return 0; // error already set
		}

		// build the result based on the operator
		int ret;
		Object *result = 0;
		switch ( tag_ )
		{

		// "and"
		case ET_AND:
			if ( rightValue->isTrue() )
				result = new Integer( 1 ); // new reference
			else
				result = new Integer( 0 ); // new reference
			break;

		// "or"
		case ET_OR:
			if ( rightValue->isTrue() )
				result = new Integer( 1 ); // new reference
			else
				result = new Integer( 0 ); // new reference
			break;

		// "+"
		case ET_ADD:
			result = leftValue->add( rightValue ); // new reference
			break;

		// "-"
		case ET_SUB:
			result = leftValue->sub( rightValue ); // new reference
			break;

		// "*"
		case ET_MUL:
			result = leftValue->mul( rightValue ); // new reference
			break;

		// "/"
		case ET_DIV:
			result = leftValue->div( rightValue ); // new reference
			break;

		// "mod"
		case ET_MOD:
			result = leftValue->mod( rightValue ); // new reference
			break;

		// "=="
		case ET_EQ:
			ret = leftValue->compare( rightValue ); // new reference
			if ( ret != -2 )
			{

				if ( ret == 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// "!="
		case ET_NE:
			ret = leftValue->compare( rightValue );
			if ( ret != -2 )
			{

				if ( ret != 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// "<"
		case ET_LT:
			ret = leftValue->compare( rightValue );
			if ( ret != -2 )
			{

				if ( ret < 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// ">"
		case ET_GT:
			ret = leftValue->compare( rightValue );
			if ( ret != -2 )
			{

				if ( ret > 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// "<="
		case ET_LE:
			ret = leftValue->compare( rightValue );
			if ( ret != -2 )
			{

				if ( ret <= 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// ">="
		case ET_GE:
			ret = leftValue->compare( rightValue );
			if ( ret != -2 )
			{

				if ( ret >= 0 )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		// "in"
		case ET_IN:
			ret = rightValue->includes( leftValue );
			if ( ret != -1 )
			{

				if ( ret )
					result = new Integer( 1 ); // new reference
				else
					result = new Integer( 0 ); // new reference
			}
			break;

		default:
			setRuntimeError( ERROR_INTERNAL_INVALID_BINARYEXPRESSION_TAG_X, tag_ );
			break;
		}

		// clean up
		leftValue->decRef();
		rightValue->decRef();

		return result;
	}
}

