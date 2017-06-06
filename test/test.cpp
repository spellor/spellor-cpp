#include "gtest/gtest.h"
#include "spellor.cpp"
#include <iostream>

using namespace std;

bool checker(const std::string& input_string, const std::string& expected){
	const bool is_correct = input_string == expected;
	std::cout << "(" << input_string << ") == (" << expected << ") = (" << std::boolalpha << is_correct << ")" << std::endl;
	return is_correct;
}

TEST(spellor, all_tests){
	spellor *s = new spellor("test");
	s->take_input();
	//s->output();
	EXPECT_TRUE(checker(s->correct("speling"), "spelling")); // insert
	EXPECT_TRUE(checker(s->correct("korrectud"), "corrected")); // replace 2
	EXPECT_TRUE(checker(s->correct("bycycle"), "bicycle")); // replace
	EXPECT_TRUE(checker(s->correct("inconvient"), "inconvenient")); // insert 2
	EXPECT_TRUE(checker(s->correct("arrainged"), "arranged")); // delete
	EXPECT_TRUE(checker(s->correct("peotry"), "poetry")); // transpose
	EXPECT_TRUE(checker(s->correct("peotryy"), "poetry")); // transpose + delete
	EXPECT_TRUE(checker(s->correct("word"), "word")); // known
	EXPECT_TRUE(checker(s->correct("quintessential"), "")); // unknown
}
