/*

   WhileStatement.h

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

#include "Statement.h"

namespace TS
{

	class Expression;
	class Block;
	class Interpreter;

	// WhileStatement
	//
	class WhileStatement : public Statement
	{

		// Test Expression
		//
		Expression *test_;

		// Loop Block
		//
		Block *block_;

	public:
		WhileStatement( int lineNumber, Expression *test, Block *block );
		WhileStatement( const WhileStatement &ws );
		virtual ~WhileStatement();

		// clone()
		//
		virtual Statement *clone() const;

		// execute()
		//
		virtual int execute( Interpreter *interpreter, Scope *scope );
	};
}
