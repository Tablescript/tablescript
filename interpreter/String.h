/* String.h

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

#ifndef _TS_STRING_H_
#define _TS_STRING_H_

#include "Object.h"
#include <string>

namespace TS
{

	class String : public Object
	{

		std::string value_;

	protected:
		virtual ~String();

	public:
		String();
		String( const std::string &value );
		String( char c);

		// getValue()
		//
		std::string getValue() const;

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "String"; }

		// isTrue()
		//
		virtual bool isTrue() const;

		// add()
		//
		virtual Object *add( Object *value );

		// integerAdd()
		//
		virtual Object *integerAdd( Integer *i );

		// floatAdd()
		//
		virtual Object *floatAdd( Float *f );

		// stringAdd()
		//
		virtual Object *stringAdd( String *s );

		// toInteger()
		//
		virtual Integer *toInteger() const;

		// toFloat()
		//
		virtual Float *toFloat() const;

		// toString()
		//
		virtual String *toString() const;

		// append()
		//
		bool append( Object *o );

		// getElement()
		//
		virtual Object *getElement( Object *key );

		// compare()
		//
		virtual int compare( const Object *o ) const;
		virtual int integerCompare( const Integer *i ) const;
		virtual int floatCompare( const Float *f ) const;
		virtual int stringCompare( const String *s ) const;

		// getLength()
		//
		virtual unsigned int getLength() const;
	};
}

#endif
