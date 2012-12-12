/* Object.h

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

#ifndef _TS_OBJECT_H_
#define _TS_OBJECT_H_

#include <string>

namespace TS
{

	class List;
	class Integer;
	class Float;
	class String;
	class Interpreter;
	class Scope;

	// Object Class
	//
	class Object
	{

		// Object Reference Count
		//
		int refCount_;

	protected:
		virtual ~Object();

	public:
		Object();

		// Reference Counting
		//
		void addRef();
		void decRef();

		// getTypeName()
		//
		virtual const char *getTypeName() const = 0;

		// True-ness Test
		//
		virtual bool isTrue() const = 0;

		// Math Operators
		//
		virtual Object *add( Object *value );
		virtual Object *sub( Object *value );
		virtual Object *mul( Object *value );
		virtual Object *div( Object *value );
		virtual Object *mod( Object *value );

		virtual Object *integerAdd( Integer *i );
		virtual Object *integerSub( Integer *i );
		virtual Object *integerMul( Integer *i );
		virtual Object *integerDiv( Integer *i );
		virtual Object *integerMod( Integer *i );

		virtual Object *floatAdd( Float *f );
		virtual Object *floatSub( Float *f );
		virtual Object *floatMul( Float *f );
		virtual Object *floatDiv( Float *f );

		virtual Object *stringAdd( String *s );

		virtual Object *listMul( List *l );

		virtual Object *toNegative();
		virtual Object *toPositive();

		virtual Object *getElement( Scope *scope, Object *key );
		virtual bool setElement( Object *key, Object *value );

		virtual unsigned int getLength() const;

		virtual Object *call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope );

		// toInteger()
		//
		virtual Integer *toInteger() const;

		// toFloat()
		//
		virtual Float *toFloat() const;

		// toString()
		//
		virtual String *toString() const;

		// compare()
		//
		virtual int compare( const Object *o ) const;
		virtual int integerCompare( const Integer *i ) const;
		virtual int floatCompare( const Float *f ) const;
		virtual int stringCompare( const String *s ) const;

		// includes()
		//
		virtual int includes( const Object *o ) const;
	};
}

#endif
