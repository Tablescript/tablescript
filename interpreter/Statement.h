/* Statement.h

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

#ifndef _TS_STATEMENT_H_
#define _TS_STATEMENT_H_

namespace TS
{

	class Interpreter;
	class Scope;

	enum
	{

		EXEC_SUCCESS = 0,
		EXEC_FAIL,
		EXEC_RETURN,
		EXEC_BREAK,
		EXEC_CONTINUE,
        EXEC_EXIT
	};

	class Statement
	{

		int lineNumber_;

	public:
		Statement( int lineNumber );
		Statement( const Statement &s );
		virtual ~Statement();

		// clone()
		//
		virtual Statement *clone() const = 0;

		// getLineNumber()
		//
		int getLineNumber() const;

		virtual int execute( Interpreter *interpreter, Scope *scope ) = 0;

        // succeeds()
        //
        static bool isExecutionError( int ret );
	};
}

#endif
