/* TList.h

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

#ifndef _TS_TLIST_H_
#define _TS_TLIST_H_

#include <string>
#include <list>
#include <vector>

namespace TS
{

	class StringList : public std::vector< std::string >
	{

	public:

		// clone()
		//
		StringList *clone() const
		{

			StringList *result = new StringList;

			const_iterator i, iEnd = end();
			for ( i = begin(); i != iEnd; ++i )
				result->push_back( *i );

			return result;
		}
	};

	template <class T>
	class TList : public T
	{

	public:

		// Destructor
		//
		~TList()
		{

			typename T::iterator i, iEnd = T::end();
			for ( i = T::begin(); i != iEnd; ++i )
				delete ( *i );
			T::clear();
		}

		// clone()
		//
		TList *clone() const
		{

			// create new collection
			TList *result = new TList;

			// clone existing elements
			typename T::const_iterator i, iEnd = T::end();
			for( i = T::begin(); i != iEnd; ++i )
				result->push_back( ( *i )->clone() );

			return result;
		}
	};

	class ElseIf;
	typedef TList< std::list< ElseIf * > > ElseIfList;

	class Expression;
	typedef TList< std::vector< Expression * > > ExpressionList;

	class TableEntry;
	typedef TList< std::list< TableEntry * > > TableEntryList;

	class Pair;
	typedef TList< std::list< Pair * > > PairList;
}

#endif
