/* List.cpp

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

#include "List.h"
#include "None.h"
#include "Integer.h"
#include "Error.h"
#include "String.h"
#include <sstream>

namespace TS
{

	// Constructor
	//
	List::List( int length )
	{

		for ( int i = 0; i < length; ++i )
		{

			none->addRef();
			elements_.push_back( none );
		}
	}

	// Destructor
	//
	List::~List()
	{

		std::vector< Object * >::iterator i, iEnd = elements_.end();
		for ( i = elements_.begin(); i != iEnd; ++i )
			( *i )->decRef();
		elements_.clear();
	}

	// getElement()
	//
	Object *List::getElementInt( unsigned int index )
	{

		if ( index >= elements_.size() )
		{

			setRuntimeError( ERROR_INDEX_X_OUT_OF_BOUNDS, index );
			return false;
		}

		Object *result = elements_[ index ];
		result->addRef(); // take reference

		return result;
	}

	// setElement()
	//
	bool List::setElementInt( unsigned int index, Object *value )
	{

		if ( index >= elements_.size() )
		{

			setRuntimeError( ERROR_INDEX_X_OUT_OF_BOUNDS, index );
			return false;
		}

		// clear the old
		Object *old = elements_[ index ];
		old->decRef();

		// set the new
		value->addRef(); // take reference
		elements_[ index ] = value;

		return true;
	}

	// append()
	//
	void List::append( Object *item )
	{

		item->addRef(); // take reference

		elements_.push_back( item );
	}

	// isTrue()
	//
	bool List::isTrue() const
	{

		return elements_.size() ? true : false;
	}

	// getElement()
	//
	Object *List::getElement( Scope *scope, Object *key )
	{

		Integer *intKey = dynamic_cast< Integer * >( key );
		if ( !intKey )
		{

            setRuntimeError( ERROR_INDEX_MUST_BE_INTEGER );
			return 0;
		}

		return getElementInt( intKey->getValue() );
	}

	// setElement()
	//
	bool List::setElement( Object *key, Object *value )
	{

		Integer *intKey = dynamic_cast< Integer * >( key );
		if ( !intKey )
		{

			setRuntimeError( ERROR_INDEX_MUST_BE_INTEGER );
			return false;
		}

		return setElementInt( intKey->getValue(), value );
	}

	// mul()
	//
	Object *List::mul( Object *value )
	{

		return value->listMul( this );
	}

	// integerMul()
	//
	Object *List::integerMul( Integer *i )
	{

		List *result = new List; // new reference

		for ( int count = 0; count < i->getValue(); ++count )
			for ( unsigned int index = 0; index < elements_.size(); ++index )
				result->append(elements_[ index ] ); // takes reference

		return result;
	}

	// getLength()
	//
	unsigned int List::getLength() const
	{

		return elements_.size();
	}

    // toString()
    //
    String *List::toString() const
    {

        std::ostringstream ss;
        ss << "[ ";

        for ( unsigned int i = 0; i < elements_.size(); ++i )
        {

			if ( i != 0 )
				ss << ", ";

            String *s = elements_[ i ]->toString(); // new reference
            ss << s->getValue();
            s->decRef();
        }

        ss << " ]";
        return new String(ss.str().c_str()); // new reference
    }

	// includes
	//
	int List::includes( const Object *o ) const
	{

		std::vector< Object * >::const_iterator i, iEnd = elements_.end();
		for ( i = elements_.begin(); i != iEnd; ++i )
			if ( o->compare( *i ) == 0 )
				return 1;

		return 0;
	}
}

