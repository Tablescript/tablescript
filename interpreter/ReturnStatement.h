/* ReturnStatement.h

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

#ifndef _TS_RETURNSTATEMENT_H_
#define _TS_RETURNSTATEMENT_H_

#include "Statement.h"

namespace TS
{

	class Expression;
	class Interpreter;

	class ReturnStatement : public Statement
	{

		Expression *expression_;

	public:
		ReturnStatement( int lineNumber, Expression *expression );
		ReturnStatement( const ReturnStatement &rs );
		virtual ~ReturnStatement();

		// clone()
		//
		virtual Statement *clone() const;

		// execute()
		//
		virtual int execute( Interpreter *interpreter, Scope *scope );
	};
}

#endif
