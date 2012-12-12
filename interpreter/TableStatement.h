/* TableStatement.h

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

#ifndef _TS_TABLESTATEMENT_H_
#define _TS_TABLESTATEMENT_H_

#include "Statement.h"
#include <string>
#include "TList.h"

namespace TS
{

	class Block;
	class Interpreter;
	class TableEntry;

	// TableStatement Class
	//
	class TableStatement : public Statement
	{

		std::string name_;
		StringList *args_;
		std::string dice_;
		Block *block_;
		TableEntryList *elements_;

	public:
		TableStatement( int lineNumber, const std::string name, StringList *args, const std::string dice, Block *block, TableEntryList *elements );
		TableStatement( const TableStatement &ts );
		virtual ~TableStatement();

		// clone()
		//
		virtual Statement *clone() const;

		// execute()
		//
		virtual int execute( Interpreter *interpreter, Scope *scope );
	};
}

#endif
