#include "test.h"
#include "restitutionTest.h"
#include "HierarchieTest.h"
#include "StressTest.h"
#include "myMath.h"

#undef main

int main()
{

	Test* test = new StressTest();
	test->init();

	test->run();


	return 0;
}