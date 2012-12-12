// main.cpp
//
//
//

#include <iostream>
#include "interpreter/None.h"
#include "interpreter/Interpreter.h"
#include "interpreter/Error.h"

int main( int argc, char *argv[] )
{

	if( argc == 1 )
	{

		std::cout << "Usage: ts filename" << std::endl;
		return -1;
	}

    TS::None::initialize();

	TS::Interpreter interpreter( argc, argv );
	if( !interpreter.import( std::string( argv[1] ) ) )
	{

		std::cout << "Error: " << TS::errorMessage << " (Line " << TS::errorLineNumber << ")." << std::endl;
		return -1;
	}
	
	std::cout << "Done." << std::endl;
	return 0;
}
