/* MethodMap.h

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

#ifndef _TS_METHODMAP_H_
#define _TS_METHODMAP_H_

#include "FunctionStatement.h"

#include <string>
#include <map>

namespace TS
{

	class MethodMap : public std::map< std::string, FunctionStatement * >
	{

	public:

		// Destructor
		//
		~MethodMap()
		{

			iterator i, iEnd = end();
			for ( i = begin(); i != iEnd; ++i )
				delete ( i->second );
			clear();
		}

		// clone()
		//
		MethodMap *clone() const
		{

			MethodMap *result = new MethodMap;

			const_iterator i, iEnd = end();
			for ( i = begin(); i != iEnd; ++i )
				result->insert( std::make_pair( i->first, dynamic_cast< FunctionStatement * >( i->second->clone() ) ) );

			return result;
		}
	};
}

#endif
