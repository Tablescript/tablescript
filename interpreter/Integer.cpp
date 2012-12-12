/* Integer.cpp

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

#include "Integer.h"
#include "Float.h"
#include <sstream>
#include "String.h"
#include "Error.h"
#include "List.h"

namespace TS
{

	// Cosntructor
	//
	Integer::Integer( int value )
		: value_( value )
	{
	}

	// Destructor
	//
	Integer::~Integer()
	{
	}

	// getValue()
	//
	int Integer::getValue() const
	{

		return value_;
	}

	// isTrue()
	//
	bool Integer::isTrue() const
	{

		return value_ ? true : false;
	}

	// add()
	//
	Object *Integer::add( Object *value )
	{

		return value->integerAdd( this ); // new reference
	}

	// sub()
	//
	Object *Integer::sub( Object *value )
	{

		return value->integerSub( this ); // new reference
	}

	// mul()
	//
	Object *Integer::mul( Object *value )
	{

		return value->integerMul( this ); // new reference
	}

	// div()
	//
	Object *Integer::div( Object *value )
	{

		return value->integerDiv( this ); // new reference
	}

	// mod()
	//
	Object *Integer::mod( Object *value )
	{

		return value->integerMod( this ); // new reference
	}

	// integerAdd()
	//
	Object *Integer::integerAdd( Integer *i )
	{

		return new Integer( i->getValue() + value_ ); // new reference
	}

	// integerSub()
	//
	Object *Integer::integerSub( Integer *i )
	{

		return new Integer( i->getValue() - value_ ); // new reference
	}

	// integerMul()
	//
	Object *Integer::integerMul( Integer *i )
	{

		return new Integer( i->getValue() * value_ ); // new reference
	}

	// integerDiv()
	//
	Object *Integer::integerDiv( Integer *i )
	{

		if ( value_ == 0 )
		{

			setRuntimeError( 0, ERROR_DIVIDE_BY_ZERO );
			return 0;
		}

		return new Integer( i->getValue() / value_ ); // new reference
	}

	// integerMod()
	//
	Object *Integer::integerMod( Integer *i )
	{

		if ( value_ == 0 )
		{

			setRuntimeError( 0, ERROR_MODULO_DIVIDE_BY_ZERO );
			return 0;
		}

		return new Integer( i->getValue() % value_ ); // new reference
	}

	// floatAdd()
	//
	Object *Integer::floatAdd( Float *f )
	{

		return new Float( f->getValue() + value_ ); // new reference
	}

	// floatSub()
	//
	Object *Integer::floatSub( Float *f )
	{

		return new Float( f->getValue() - value_ ); // new reference
	}

	// floatMul()
	//
	Object *Integer::floatMul( Float *f )
	{

		return new Float( f->getValue() * value_ ); // new reference
	}

	// floatDiv()
	//
	Object *Integer::floatDiv( Float *f )
	{

		if ( value_ == 0 )
		{

			setRuntimeError( 0, ERROR_DIVIDE_BY_ZERO );
			return 0;
		}

		return new Float( f->getValue() / value_ ); // new reference
	}

	// stringAdd()
	//
	Object *Integer::stringAdd( String *s )
	{

		std::ostringstream ss;
		ss << s->getValue() << value_;
		return new String( ss.str() ); // new reference
	}

	// listMul()
	//
	Object *Integer::listMul( List *l )
	{

		// defer to list code
		return l->integerMul( this ); // new reference
	}

	// toNegative()
	//
	Object *Integer::toNegative()
	{

		return new Integer( -1 * abs( value_ ) ); // new reference
	}

	// toPositive()
	//
	Object *Integer::toPositive()
	{

		return new Integer( abs( value_ ) ); // new reference
	}


	// toInteger()
	//
	Integer *Integer::toInteger() const
	{

		return new Integer( value_ ); // new reference
	}

	// toFloat()
	//
	Float *Integer::toFloat() const
	{

		return new Float( static_cast< float >( value_ ) ); // new reference
	}

	// toString()
	//
	String *Integer::toString() const
	{

		std::ostringstream ss;
		ss << value_;
		return new String( ss.str() ); // new reference
	}

	// compare()
	//
	int Integer::compare( const Object *o ) const
	{

		return o->integerCompare( this );
	}

	// integerCompare()
	//
	int Integer::integerCompare( const Integer *i ) const
	{

		int compareVal = ( i->getValue() - value_ );
		if ( compareVal < 0 )
			return -1;
		if ( compareVal > 0 )
			return 1;
		return 0;
	}

	// floatCompare()
	//
	int Integer::floatCompare( const Float *f ) const
	{

		float compareVal = f->getValue() - value_;
		if ( compareVal < 0.0f )
			return -1;
		if ( compareVal > 0.0f )
			return 1;
		return 0;
	}
}

