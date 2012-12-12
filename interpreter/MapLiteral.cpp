/* MapLiteral.cpp

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

#include "MapLiteral.h"
#include "Map.h"

namespace TS
{

	// Constructor
	//
	Pair::Pair( Expression *key, Expression *value )
		: key_( key ),
		value_( value )
	{
	}

	// Copy Constructor
	//
	Pair::Pair( const Pair &p )
	{

		key_ = p.key_->clone();
		value_ = p.value_->clone();
	}

	// Destructor
	//
	Pair::~Pair()
	{

		delete key_;
		delete value_;
	}

	// clone()
	//
	Pair *Pair::clone() const
	{

		return new Pair( *this );
	}

	// getKey()
	//
	Expression *Pair::getKey() const
	{

		return key_;
	}

	// getValue()
	//
	Expression *Pair::getValue() const
	{

		return value_;
	}


	// Constructor
	//
	MapLiteral::MapLiteral( int lineNumber, PairList *elements )
		: Expression( lineNumber ),
		elements_( elements )
	{
	}

	// Copy Constructor
	//
	MapLiteral::MapLiteral( const MapLiteral &ml )
		: Expression( ml )
	{

		elements_ = ml.elements_->clone();
	}

	// Destructor
	//
	MapLiteral::~MapLiteral()
	{

		delete elements_;
	}

	// clone()
	//
	Expression *MapLiteral::clone() const
	{

		return new MapLiteral( *this );
	}

	// evaluate()
	//
	Object *MapLiteral::evaluate_( Interpreter *interpreter, Scope *scope )
	{

		Map *result = new Map; // new reference
		PairList::iterator i, iEnd = elements_->end();
		for ( i = elements_->begin(); i != iEnd; ++i )
		{

			Pair *pair = ( *i );
			Object *key = ( pair->getKey() )->evaluate( interpreter, scope ); // new reference
			if ( !key )
			{

                // clean up
				result->decRef();

				return 0; // error already set
			}

			Object *value = ( pair->getValue() )->evaluate( interpreter, scope ); // new reference
			if ( !value )
			{

                // clean up
				result->decRef();
				key->decRef();

				return 0; // error already set
			}

			if ( !result->setElement( key, value ) ) // takes reference
			{

                // clean up
				result->decRef();
				key->decRef();
				value->decRef();

				return 0; // error already set
			}

			key->decRef();
			value->decRef();
		}

		return result;
	}
}

