/* Float.h

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

#ifndef _TS_FLOAT_H_
#define _TS_FLOAT_H_

#include "Object.h"

namespace TS
{

	class Float : public Object
	{

		float value_;

	protected:
		virtual ~Float();

	public:
		Float( float value );

		float getValue() const;

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "Float"; }

		// isTrue()
		//
		virtual bool isTrue() const;

		virtual Object *add( Object *value );
		virtual Object *sub( Object *value );
		virtual Object *mul( Object *value );
		virtual Object *div( Object *value );

		virtual Object *integerAdd( Integer *i );
		virtual Object *integerSub( Integer *i );
		virtual Object *integerMul( Integer *i );
		virtual Object *integerDiv( Integer *i );

		virtual Object *floatAdd( Float *f );
		virtual Object *floatSub( Float *f );
		virtual Object *floatMul( Float *f );
		virtual Object *floatDiv( Float *f );

		virtual Integer *toInteger() const;
		virtual Float *toFloat() const;
		virtual String *toString() const;

		virtual int compare( const Object *o ) const;
		virtual int integerCompare( const Integer *i ) const;
		virtual int floatCompare( const Float *f ) const;
	};
}

#endif
