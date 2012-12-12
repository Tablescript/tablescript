#include <cppunit/extensions/HelperMacros.h>
#include "DiceTest.h"
#include "interpreter/Dice.h"

CPPUNIT_TEST_SUITE_REGISTRATION( DiceTest );

void DiceTest::testRollDie()
{
	
	TS::rollDie( 6 );
}
