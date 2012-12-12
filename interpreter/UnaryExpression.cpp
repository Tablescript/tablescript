/* UnaryExpression.cpp

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

#include "UnaryExpression.h"
#include "Object.h"
#include "Integer.h"

namespace TS
{

	// Constructor
	//
	UnaryExpression::UnaryExpression( int lineNumber, enum PExprTag tag, Expression *expression )
		: Expression( lineNumber ),
		tag_( tag ),
		expression_( expression )
	{
	}

	// Copy Constructor
	//
	UnaryExpression::UnaryExpression( const UnaryExpression &ue )
		: Expression( ue ),
		tag_( ue.tag_ )
	{

		expression_ = ue.expression_->clone();
	}

	// Destructor
	//
	UnaryExpression::~UnaryExpression()
	{

		delete expression_;
	}

	// clone()
	//
	Expression *UnaryExpression::clone() const
	{

		return new UnaryExpression( *this );
	}

	// evaluate()
	//
	Object *UnaryExpression::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		Object *value = expression_->evaluate( interpreter, scope ); // new reference
		if ( !value )
			return 0;

		Object *result = 0;
		switch ( tag_ )
		{

		case ET_POS:
			result = value->toPositive(); // new reference
			break;

		case ET_NEG:
			result = value->toNegative(); // new reference
			break;

		case ET_NOT:
			if ( value->isTrue() )
				result = new Integer( 0 ); // new reference
			else
				result = new Integer( 1 ); // new reference
			break;

		default:
			break;
		}

		value->decRef();

		return result;
	}
}

