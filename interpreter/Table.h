/* Table.h

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

#ifndef _TS_TABLE_H_
#define _TS_TABLE_H_

#include "Object.h"
#include <vector>
#include <string>
#include <list>

namespace TS
{

	class Block;
	class TableEntry;
	class Interpreter;
	class List;

	// Table Class
	//
	class Table : public Object
	{

        std::string name_;
		std::vector< std::string > *args_;
		std::string dice_;
		Block *block_;
		std::list< TableEntry * > *elements_;

		unsigned int maxEntry() const;

	protected:
		virtual ~Table();

	public:
		Table( const std::string &name, std::vector< std::string > *args, const std::string &dice, Block *block, std::list< TableEntry * > *elements );

		// getTypeName()
		//
		inline virtual const char *getTypeName() const { return "Table"; }

		// isTrue()
		//
		inline virtual bool isTrue() const { return true; }

		// call()
		//
		virtual Object *call( Interpreter *interpreter, Scope *scope, List *parameters, const std::string &callScope );

		// getElement()
		//
		virtual Object *getElement( Interpreter *interpreter, Scope *scope, Object *key );
	};
}

#endif
