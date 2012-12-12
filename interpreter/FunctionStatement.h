/* FunctionStatement.h

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

#ifndef _TS_FUNCTIONSTATEMENT_H_
#define _TS_FUNCTIONSTATEMENT_H_

#include "Statement.h"
#include <string>
#include "TList.h"

namespace TS
{

	class Block;
	class Interpreter;
	class Scope;

	class FunctionStatement : public Statement
	{

		std::string name_;
		StringList *fargs_;
		Block *block_;

	public:
		FunctionStatement( int lineNumber, const std::string &name, StringList *fargs, Block *block );
		FunctionStatement( const FunctionStatement &fs );
		virtual ~FunctionStatement();

		// getName()
		//
		std::string getName() const;

		// clone()
		//
		virtual Statement *clone() const;

		// execute()
		//
		virtual int execute( Interpreter *interpreter, Scope *scope );
	};
}

#endif
