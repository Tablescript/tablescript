/* Object.cpp

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

#include "Object.h"
#include "List.h"
#include "Error.h"
#include <sstream>
#include "String.h"

#include <iostream>

namespace TS
{

	// Default Constructor
	//
	Object::Object()
		: refCount_( 1 )
	{

		//std::cout << "Constructor: 0x" << std::hex << reinterpret_cast< unsigned int >( this ) << std::endl;
	}

	// Destructor
	//
	Object::~Object()
	{
		//std::cout << "Destructor: 0x" << std::hex << reinterpret_cast< unsigned int >( this ) << std::endl;
	}

	// addRef()
	//
	void Object::addRef()
	{

		++refCount_;
	}

	// decRef()
	//
	void Object::decRef()
	{

		--refCount_;
		if ( refCount_ == 0 )
			delete this;
	}

	// add()
	//
	Object *Object::add( Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "addition" );
		return 0;
	}

	// sub()
	//
	Object *Object::sub( Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "subtraction" );
		return 0;
	}

	// mul()
	//
	Object *Object::mul( Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "multiplication" );
		return 0;
	}

	// div()
	//
	Object *Object::div( Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "division" );
		return 0;
	}

	// mod()
	//
	Object *Object::mod( Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "modulo division" );
		return 0;
	}

	// integerAdd()
	//
	Object *Object::integerAdd( Integer *i )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer addition" );
		return 0;
	}

	// integerSub()
	//
	Object *Object::integerSub( Integer *i )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer subtraction" );
		return 0;
	}

	// integerMul()
	//
	Object *Object::integerMul( Integer *i )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer multiplication" );
		return 0;
	}

	// integerDiv()
	//
	Object *Object::integerDiv( Integer *i )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer division" );
		return 0;
	}

	// integerMod()
	//
	Object *Object::integerMod( Integer *i )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer modulo division" );
		return 0;
	}

	// floatAdd()
	//
	Object *Object::floatAdd( Float *f )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "float addition" );
		return 0;
	}

	// floatSub()
	//
	Object *Object::floatSub( Float *f )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "float subtraction" );
		return 0;
	}

	// floatMul()
	//
	Object *Object::floatMul( Float *f )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "float multiplication" );
		return 0;
	}

	// floatDiv()
	//
	Object *Object::floatDiv( Float *f )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "float division" );
		return 0;
	}

	// stringAdd()
	//
	Object *Object::stringAdd( String *s )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "string addition" );
		return 0;
	}

	// listMul()
	//
	Object *Object::listMul( List *l )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "list multiplication" );
		return 0;
	}

	// toNegative()
	//
	Object *Object::toNegative()
	{

		setRuntimeError( "Type '%s' cannot be negated", getTypeName() );
		return 0;
	}

	// toPositive()
	//
	Object *Object::toPositive()
	{

		setRuntimeError( "Type '%s' cannot be made positive", getTypeName() );
		return 0;
	}

	// getElement()
	//
	Object *Object::getElement( Scope *scope, Object *key )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "keyed values" );
		return 0;
	}

	// setElement()
	//
	bool Object::setElement( Object *key, Object *value )
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "keyed values" );
		return false;
	}

	// getLength()
	//
	unsigned int Object::getLength() const
	{

		setRuntimeError( "Type '%s' does not have a length", getTypeName() );
		return static_cast< unsigned int >( -1 );
	}

	// call()
	//
	Object *Object::call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope )
	{

		setRuntimeError( "Type '%s' is not callable", getTypeName() );
		return 0;
	}

	// toInteger()
	//
	Integer *Object::toInteger() const
	{

		setRuntimeError( "Type '%s' cannot be converted to an integer", getTypeName() );
		return 0;
	}

	// toFloat()
	//
	Float *Object::toFloat() const
	{

		setRuntimeError( "Type '%s' cannot be converted to a float", getTypeName() );
		return 0;
	}

	// toString()
	//
	String *Object::toString() const
	{

		std::ostringstream ss;
		ss << "<" << getTypeName() << ": 0x" << std::hex << this << ">";
		return new String( ss.str() ); // new reference
	}

	// compare()
	//
	int Object::compare( const Object *o ) const
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "comparison" );
		return -2; // TODO: ??!?!
	}

	// integerCompare()
	//
	int Object::integerCompare( const Integer *i ) const
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "integer comparison" );
		return -2; // TODO
	}

	// floatCompare()
	//
	int Object::floatCompare( const Float *f ) const
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "float comparison" );
		return -2; // TODO
	}

	// stringCompare()
	//
	int Object::stringCompare( const String *s ) const
	{

		setRuntimeError( ERROR_TYPE_X_DOES_NOT_SUPPORT_Y, getTypeName(), "string comparison" );
		return -2; // TODO
	}

	// includes()
	//
	int Object::includes( const Object *o ) const
	{

		setRuntimeError( "Type '%s' is not a container", getTypeName() );
		return -1; // TODO
	}
}

