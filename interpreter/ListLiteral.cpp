/* ListLiteral.cpp

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

#include "ListLiteral.h"
#include "List.h"

namespace TS
{

	// Constructor
	//
	ListLiteral::ListLiteral( int lineNumber, ExpressionList *elements )
		: Expression( lineNumber ),
		elements_( elements )
	{
	}

	// Copy Constructor
	//
	ListLiteral::ListLiteral( const ListLiteral &ll )
		: Expression( ll )
	{

		elements_ = ll.elements_->clone();
	}

	// Destructor
	//
	ListLiteral::~ListLiteral()
	{

		delete elements_;
		//ExpressionList::iterator i, iEnd = _elements->end();
		//for(i = _elements->begin(); i != iEnd; ++i)
		//	delete (*i);
		//delete _elements;
	}

	// clone()
	//
	Expression *ListLiteral::clone() const
	{

		return new ListLiteral( *this );
	}

	// evaluate()
	//
	Object *ListLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		List *result = new List; // new reference
		ExpressionList::iterator i, iEnd = elements_->end();
		for ( i = elements_->begin(); i != iEnd; ++i )
		{

			Object *elementValue = ( *i )->evaluate( interpreter, scope ); // new reference
			if ( !elementValue )
			{

                // clean up
				result->decRef();

				return 0; // error already set
			}

			result->append( elementValue ); // takes reference
			elementValue->decRef();
		}

		return result;
	}
}

