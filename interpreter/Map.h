/* Map.h

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

#ifndef _TS_MAP_H_
#define _TS_MAP_H_

#include "Object.h"
#include <map>
#include <string>

namespace TS
{

	class List;

	// Map Class
	//
	class Map : public Object
	{

		std::map< std::string, Object * > elements_;

	protected:
		virtual ~Map();

	public:
		Map();

		Object *getElementStr( const std::string &name ) const;
		void setElementStr( const std::string &name, Object *value );

		bool hasKey( const std::string &name ) const;

		// getKeys()
		//
		List *getKeys() const;

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "Map"; }

		// isTrue()
		//
		virtual bool isTrue() const;

		// getElement()
		//
		virtual Object *getElement( Object *key );

		// setElement()
		//
		virtual bool setElement( Object *key, Object *value );

		// getLength()
		//
		virtual unsigned int getLength() const;
	};
}

#endif
