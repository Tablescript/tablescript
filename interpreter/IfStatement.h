/* IfStatement.h

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

#ifndef _TS_IFSTATEMENT_H_
#define _TS_IFSTATEMENT_H_

#include "Statement.h"
#include <list>
#include "TList.h"

namespace TS
{

	class Expression;
	class Block;

	// ElseIf Class
	//
	class ElseIf
	{

		Expression *test_;
		Block *block_;

	public:
		ElseIf( Expression *test, Block *block );
		ElseIf( const ElseIf &ei );
		virtual ~ElseIf();

		// clone()
		//
		ElseIf *clone() const;

		// getTest()
		//
		Expression *getTest() const;

		// getBlock()
		//
		Block *getBlock() const;
	};

	// IfStatement Class
	//
	class IfStatement : public Statement
	{

		Expression *ifTest_;
		Block *ifBlock_;
		ElseIfList *elseifs_;
		Block *elseBlock_;

	public:
		IfStatement( int lineNumber, Expression *ifTest, Block *ifBlock, ElseIfList *elseifs, Block *elseBlock );
		IfStatement( const IfStatement &is );
		virtual ~IfStatement();

		// clone()
		//
		virtual Statement *clone() const;

		// execute()
		//
		virtual int execute( Interpreter *interpreter, Scope *scope );
	};
}

#endif
