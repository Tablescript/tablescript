/* TableEntry.h

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

#ifndef _TS_TABLEENTRY_H_
#define _TS_TABLEENTRY_H_

namespace TS
{

	class Expression;
	class Block;
	class Object;
	class Interpreter;
	class Scope;

	// TableEntry Class
	//
	class TableEntry
	{

		unsigned int low_;
		unsigned int high_;

		Block *pre_;
		Expression *expr_;
		Block *post_;

	public:
		TableEntry( unsigned int high, unsigned int low, Block *pre, Expression *expr, Block *post );
		TableEntry( const TableEntry &te );
		virtual ~TableEntry();

		// clone()
		//
		TableEntry *clone() const;

		// applies()
		//
		bool applies( unsigned int roll );

		// getUpper()
		//
		unsigned int getUpper() const;

		// evaluate()
		//
		Object *evaluate( Interpreter *interpreter, Scope *scope );
	};
}

#endif
