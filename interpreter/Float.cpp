/* Float.cpp

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

#include "Float.h"
#include "Integer.h"
#include "String.h"
#include "Error.h"

#include <sstream>

namespace TS
{

	// Constructor
	//
	Float::Float( float value )
		: value_( value )
	{
	}

	// Destructor
	//
	Float::~Float()
	{
	}

	// getValue()
	//
	float Float::getValue() const
	{

		return value_;
	}

	// isTrue()
	//
	bool Float::isTrue() const
	{

		return ( value_ != 0.0f ) ? true : false;
	}

	// add()
	//
	Object *Float::add( Object *value )
	{

		return value->floatAdd( this ); // new reference
	}

	// sub()
	//
	Object *Float::sub( Object *value )
	{

		return value->floatSub( this ); // new reference
	}

	// mul()
	//
	Object *Float::mul( Object *value )
	{

		return value->floatMul( this ); // new reference
	}

	// div()
	//
	Object *Float::div( Object *value )
	{

		return value->floatDiv( this ); // new reference
	}

	// integerAdd()
	//
	Object *Float::integerAdd( Integer *i )
	{

		return new Float( i->getValue() + value_); // new reference
	}

	// integerSub()
	//
	Object *Float::integerSub( Integer *i )
	{

		return new Float( i->getValue() - value_); // new reference
	}

	// integerMul()
	//
	Object *Float::integerMul(Integer *i)
	{

		return new Float( i->getValue() * value_); // new reference
	}

	// integerDiv()
	//
	Object *Float::integerDiv( Integer *i )
	{

		if ( value_ == 0.0f )
		{

			setRuntimeError( 0, ERROR_DIVIDE_BY_ZERO );
			return 0;
		}

		return new Float( i->getValue() / value_ ); // new reference
	}

	// floatAdd()
	//
	Object *Float::floatAdd( Float *f )
	{

		return new Float( f->getValue() + value_ ); // new reference
	}

	// floatSub()
	//
	Object *Float::floatSub( Float *f)
	{

		return new Float( f->getValue() - value_ ); // new reference
	}

	// floatMul()
	//
	Object *Float::floatMul( Float *f )
	{

		return new Float( f->getValue() * value_ ); // new reference
	}

	// floatDiv()
	//
	Object *Float::floatDiv( Float *f )
	{

		if ( value_ == 0.0f )
		{

			setRuntimeError( 0, ERROR_DIVIDE_BY_ZERO );
			return 0;
		}

		return new Float( f->getValue() / value_ ); // new reference
	}

	// toInteger()
	//
	Integer *Float::toInteger() const
	{

		return new Integer( static_cast< int >( value_ ) ); // new reference
	}

	// toFloat()
	//
	Float *Float::toFloat() const
	{

		return new Float( value_ ); // new reference
	}

	// toString()
	//
	String *Float::toString() const
	{

		std::ostringstream ss;
		ss << value_;
		return new String( ss.str() ); // new reference
	}

	// compare()
	//
	int Float::compare( const Object *o ) const
	{

		return o->floatCompare( this );
	}

	// integerCompare()
	//
	int Float::integerCompare( const Integer *i ) const
	{

		float compareVal = value_ - ( float ) i->getValue();
		if ( compareVal < 0.0f )
			return -1;
		if ( compareVal > 0.0f )
			return 1;
		return 0;
	}

	// floatCompare()
	//
	int Float::floatCompare( const Float *f ) const
	{

		float compareVal = value_ - f->getValue();
		if ( compareVal < 0.0f )
			return -1;
		if ( compareVal > 0.0f )
			return 1;
		return 0;
	}
}

