#include "gtest/gtest.h"
#include "spellor.cpp"
#include <iostream>

using namespace std;

TEST(spellor, all_tests){
	spellor *s = new spellor("test");
	ASSERT_EQ(s->original_spelling(), "test");	
	s->take_input();
	s->output();
}
