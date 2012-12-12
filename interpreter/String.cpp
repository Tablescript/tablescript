/* String.cpp

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

#include "String.h"
#include "Integer.h"
#include "Error.h"
#include <sstream>
#include "Float.h"

namespace TS
{

	// Default Constructor
	//
	String::String()
	{
	}

	// Constructor
	//
	String::String( const std::string &value )
		: value_( value )
	{
	}

	// Constructor
	//
	String::String( char c )
		: value_( 1, c )
	{
	}

	// Destructor
	//
	String::~String()
	{
	}

	// getValue()
	//
	std::string String::getValue() const
	{

		return value_;
	}

	// isTrue()
	//
	bool String::isTrue() const
	{

		return !value_.empty();
	}

	// add()
	//
	Object *String::add( Object *value )
	{

		return value->stringAdd( this ); // new reference
	}

	// integerAdd()
	//
	Object *String::integerAdd( Integer *i )
	{

		std::ostringstream ss;
		ss << i->getValue() << value_;
		return new String( ss.str() ); // new reference
	}

	// floatAdd()
	//
	Object *String::floatAdd( Float *f )
	{

		std::ostringstream ss;
		ss << f->getValue() << value_;
		return new String( ss.str() ); // new reference
	}

	// stringAdd()
	//
	Object *String::stringAdd( String *s )
	{

		return new String( s->getValue() + value_ ); // new reference
	}

	// toInteger()
	//
	Integer *String::toInteger() const
	{

		return new Integer( atoi( value_.c_str() ) );
	}

	// toFloat()
	//
	Float *String::toFloat() const
	{

		return new Float( atof( value_.c_str() ) );
	}

	// toString()
	//
	String *String::toString() const
	{

		return new String( value_ ); // new reference
	}

	// append()
	//
	bool String::append( Object *o )
	{

		String *s = o->toString(); // new reference
		if ( !s )
			return false;

		value_ += s->getValue();

		s->decRef();

		return true;
	}

	// getElement()
	//
	Object *String::getElement( Object *key )
	{

		Integer *intKey = dynamic_cast< Integer * >( key );
		if ( !intKey )
		{

			setRuntimeError( ERROR_INDEX_MUST_BE_INTEGER );
			return 0;
		}

		int keyValue = intKey->getValue();
		if ( keyValue < 0 )
		{

			if ( keyValue < ( 0 - static_cast< int >( value_.size() ) ) )
			{

				setRuntimeError( ERROR_INDEX_X_OUT_OF_BOUNDS, keyValue );
				return 0;
			}

			return new String( value_[ value_.size() - keyValue ] ); // new reference
		}

		if ( keyValue >= static_cast< int >( value_.size() ) )
		{

			setRuntimeError( ERROR_INDEX_X_OUT_OF_BOUNDS, keyValue );
			return 0;
		}

		return new String( value_[ keyValue ] ); // new reference
	}

	// compare()
	//
	int String::compare( const Object *o ) const
	{

		return o->stringCompare( this );
	}

	// integerCompare()
	//
    // TODO
	int String::integerCompare( const Integer *i ) const
	{

		setRuntimeError( 0, ERROR_FEATURE_X_NOT_IMPLEMENTED, "String::integerCompare()" );
		return -2;
	}

	// floatCompare()
	//
    // TODO
	int String::floatCompare( const Float *f ) const
	{

		setRuntimeError( 0, ERROR_FEATURE_X_NOT_IMPLEMENTED, "String::floatCompare()" );
		return -2;
	}

	// stringCompare()
	//
	int String::stringCompare( const String *s ) const
	{

		int compareVal = strcmp( value_.c_str(), ( s->getValue() ).c_str() );
		if ( compareVal < 0 )
			return -1;
		if ( compareVal > 0 )
			return 1;
		return 0;
	}

	// getLength()
	//
	unsigned int String::getLength() const
	{

		return value_.size();
	}
}

