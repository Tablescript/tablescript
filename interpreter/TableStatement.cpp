/* TableStatement.cpp

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

#include "TableStatement.h"
#include "Interpreter.h"
#include "Scope.h"
#include "TableEntry.h"
#include "Table.h"
#include "Block.h"

namespace TS
{

	// Constructor
	//
	TableStatement::TableStatement(
			int lineNumber,
			const std::string name,
			StringList *args,
			const std::string dice,
			Block *block,
			TableEntryList *elements )
		: Statement( lineNumber ),
		name_( name ),
		args_( args ),
		dice_( dice ),
		block_( block ),
		elements_( elements )
	{
	}

	// Copy Constructor
	//
	TableStatement::TableStatement( const TableStatement &ts )
		: Statement( ts ),
		name_( ts.name_ ),
		dice_( ts.dice_ )
	{

		args_ = ts.args_->clone();
		block_ = ts.block_->clone();
		elements_ = ts.elements_->clone();
	}

	// Destructor
	//
	TableStatement::~TableStatement()
	{

		delete args_;
		delete block_;
		delete elements_;
	}

	// clone()
	//
	Statement *TableStatement::clone() const
	{

		return new TableStatement( *this );
	}

	// execute()
	//
	int TableStatement::execute( Interpreter *interpreter, Scope *scope )
	{

		Table *table = new Table( name_, args_->clone(), dice_, block_->clone(), elements_->clone() ); // new reference
		scope->setLocalSymbol( name_, table ); // takes reference

        // clean up
		table->decRef();

		return EXEC_SUCCESS;
	}
}

