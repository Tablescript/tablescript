/* Map.cpp

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

#include "Map.h"
#include "String.h"
#include "Error.h"
#include "List.h"

namespace TS
{

	// Constructor
	//
	Map::Map()
	{
	}

	// Destructor
	//
	Map::~Map()
	{

		std::map< std::string, Object * >::iterator i, iEnd = elements_.end();
		for ( i = elements_.begin(); i != iEnd; ++i )
			( i->second )->decRef();
	}

	// getElementStr()
	//
	Object *Map::getElementStr( const std::string &name ) const
	{

		std::map< std::string, Object * >::const_iterator i = elements_.find( name );
		if ( i == elements_.end())
		{

			setRuntimeError( 0, ERROR_INVALID_KEY_X, name.c_str() );
			return 0;
		}

		Object *result = i->second;
		result->addRef(); // new reference

		return result;
	}

	// setElementStr()
	//
	void Map::setElementStr( const std::string &name, Object *value )
	{

		// if the name already exists in the map...
		std::map< std::string, Object * >::iterator i = elements_.find( name );
		if ( i != elements_.end() )
		{

			// clear the old
			( i->second )->decRef();

			// set the new
			value->addRef();
			i->second = value;

			return;
		}

		value->addRef();
		elements_.insert( std::make_pair( name, value ) );
	}

	// hasKey()
	//
	bool Map::hasKey( const std::string &name ) const
	{

		std::map< std::string, Object * >::const_iterator i = elements_.find( name );
		if ( i == elements_.end() )
			return false;

		return true;
	}

	// getKeys()
	//
	List *Map::getKeys() const
	{

		List *list = new List; // new reference
		std::map< std::string, Object * >::const_iterator i, iEnd = elements_.end();
		for ( i = elements_.begin(); i != iEnd; ++i )
		{

			String *key = new String( i->first ); // new reference
			list->append( key ); // takes reference
			key->decRef();
		}

		return list;
	}

	// isTrue()
	//
	bool Map::isTrue() const
	{

		return elements_.size() ? true : false;
	}

	// getElement()
	//
	Object *Map::getElement( Object *key )
	{

		String *stringKey = dynamic_cast< String * >( key );
		if ( !stringKey )
		{

			setRuntimeError( ERROR_MAP_KEY_MUST_BE_STRING );
			return 0;
		}

		return getElementStr( stringKey->getValue() );
	}

	// setElement()
	//
	bool Map::setElement( Object *key, Object *value )
	{

		String *stringKey = dynamic_cast< String * >( key );
		if ( !stringKey )
		{

			setRuntimeError( ERROR_MAP_KEY_MUST_BE_STRING );
			return false;
		}

		setElementStr( stringKey->getValue(), value );

		return true;
	}

	// getLength()
	//
	unsigned int Map::getLength() const
	{

		return elements_.size();
	}
}

