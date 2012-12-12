#ifndef _DICE_TEST_H_
#define _DICE_TEST_H_

#include <cppunit/TestFixture.h>

class DiceTest : public CppUnit::TestFixture
{
	
	CPPUNIT_TEST_SUITE( DiceTest );
	CPPUNIT_TEST( testRollDie );
	CPPUNIT_TEST_SUITE_END();
	
public:
	
	void testRollDie();
};

#endif
