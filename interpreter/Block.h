/* Block.h

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

#include <list>

namespace TS
{

	class Statement;
	class Interpreter;
	class Scope;

	// Block Class
	//
	class Block
	{

		// Statement List
		//
		std::list< Statement * > statements_;

	public:
		Block();
		Block( const Block &b );
		virtual ~Block();

		// clone()
		//
		Block *clone() const;

		// addStatement()
		//
		void addStatement( Statement *s );

		// execute()
		//
		int execute( Interpreter *interpreter, Scope *scope );
	};
}
