/* None.cpp

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

#include "None.h"

namespace TS
{

	None *none = 0;

	// Default Constructor
	//
	None::None()
	{
	}

	// Destructor
	//
	None::~None()
	{
	}

	// initialize()
	//
	void None::initialize()
	{

        if ( !none )
    		none = new None;
	}

	// shutdown()
	//
	void None::shutdown()
	{

		delete none;
	}

	// isTrue()
	//
	bool None::isTrue() const
	{

		return false;
	}

	// compare()
	//
	int None::compare( Object *o ) const
	{

		Object *unconst = const_cast< None * >(this);
		return ( reinterpret_cast< void * >( o ) == reinterpret_cast< void * >( unconst ) ) ? 0 : 1;
	}
}

