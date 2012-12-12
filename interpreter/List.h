/* List.h

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

#ifndef _TS_LIST_H_
#define _TS_LIST_H_

#include "Object.h"
#include <vector>

namespace TS
{

	// List Class
	//
	class List : public Object
	{

		// List Elements
		//
		std::vector< Object * > elements_;

	protected:
		virtual ~List();

	public:
		List( int length = 0 );

		// getElementInt()
		//
		// This method returns the element at the given index. If the index is
		//  invalid, it returns 0. Otherwise, it returns a new reference to
		//  the element.
		Object *getElementInt( unsigned int index );

		// setElementInt()
		//
		// This method sets the element at the given index to the given value.
		//  The existing value at the given index is decRef'd and replaced
		//  with the new value. If the index is invalid, it returns false. A
		//  reference is taken when successfully set.
		bool setElementInt( unsigned int index, Object *value );

		// append()
		//
		// This method adds the give value to the end of the list. The list is
		//  grown to accommodate it. A reference is taken.
		void append( Object *value );

		// Object Interface
		//
		inline virtual const char *getTypeName() const { return "List"; }
		virtual bool isTrue() const;
		virtual Object *getElement( Scope *scope, Object *key );
		virtual bool setElement( Object *key, Object *value );

		virtual Object *mul( Object *value );
		virtual Object *integerMul( Integer *i );

		// getLength()
		//
		// This method returns the number of elements in the list.
		virtual unsigned int getLength() const;

        // toString()
        //
        virtual String *toString() const;

		// includes()
		//
		virtual int includes( const Object *o ) const;
	};
}

#endif
