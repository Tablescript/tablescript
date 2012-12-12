/* string.cpp

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

#include "Object.h"
#include "Interpreter.h"
#include "List.h"
#include "String.h"
#include "Error.h"
#include "Frame.h"
#include "Builtins.h"

#include <iostream>

bool extractParameters(TS::List *parameters, std::string name, std::string &source, std::string &delim)
{

	TS::Object *parameter;
	TS::String *string;

	// check parameters
	unsigned int count = parameters->getLength();
	if(count < 1 || count > 2)
	{

		TS::formatError("%s() function takes 2 parameters", name.c_str());
		return false;
	}

	parameter = parameters->getElementInt(0); // new reference
	string = dynamic_cast<TS::String *>(parameter);
	if(!string)
	{

		parameter->decRef();

		TS::formatError("%s() function: first parameter must be a string", name.c_str());
		return false;
	}
	source = string->getValue();
	parameter->decRef();

	if(count == 2)
	{

		parameter = parameters->getElementInt(1); // new reference
		string = dynamic_cast<TS::String *>(parameter);
		if(!string)
		{

			parameter->decRef();

			TS::formatError("%s() function: second parameter must be a string", name.c_str());
			return false;
		}
		delim = string->getValue();
		parameter->decRef();
	}

	return true;
}

// split()
//
TS::Object *split(TS::Interpreter *interpreter, TS::List *parameters)
{

	std::string source;
	std::string delim = " \t\n";

	// check parameters
	if(!extractParameters(parameters, "split", source, delim))
		return 0;

	TS::List *result = new TS::List;

	std::string::size_type begIdx = source.find_first_not_of(delim);
	while(begIdx != std::string::npos)
	{

		std::string::size_type endIdx = source.find_first_of(delim, begIdx);
		if(endIdx == std::string::npos)
			endIdx = source.length();

		result->append(new TS::String(std::string(source, begIdx, endIdx - begIdx)));

		begIdx = source.find_first_not_of(delim, endIdx);
	}

	return result;
}

TS::Object *trim(TS::Interpreter *interpreter, TS::List *parameters)
{

	std::string source;
	std::string delim = " \t\n";

	if(!extractParameters(parameters, "trim", source, delim))
		return 0;

	std::string::size_type begIdx = source.find_first_not_of(delim);
	std::string::size_type endIdx = source.find_last_not_of(delim);
	if(begIdx == std::string::npos)
		return new TS::String;

	return new TS::String(source.substr(begIdx, endIdx - begIdx + 1));
}

// ltrim()
//
TS::Object *ltrim(TS::Interpreter *interpreter, TS::List *parameters)
{

	std::string source;
	std::string delim = " \t\n";

	if(!extractParameters(parameters, "ltrim", source, delim))
		return 0;

	std::string::size_type begIdx = source.find_first_not_of(delim);
	if(begIdx == std::string::npos)
		return new TS::String;
	
	return new TS::String(source.substr(begIdx));
}

// rtrim()
//
TS::Object *rtrim(TS::Interpreter *interpreter, TS::List *parameters)
{

	std::string source;
	std::string delim = " \t\n";

	if(!extractParameters(parameters, "ltrim", source, delim))
		return 0;

	std::string::size_type endIdx = source.find_last_not_of(delim);
	if(endIdx == std::string::npos)
		return new TS::String(source);
	
	return new TS::String(source.substr(0, endIdx + 1));
}

extern "C" bool tsInitialize(TS::Frame *frame)
{

	frame->setSymbol("split", new TS::AddInFunction(split));
	frame->setSymbol("trim", new TS::AddInFunction(trim));
	frame->setSymbol("ltrim", new TS::AddInFunction(ltrim));
	frame->setSymbol("rtrim", new TS::AddInFunction(rtrim));

	return true;
}

