#include <iostream>
#include <string>
using namespace std;

class spellor {
private:
	string _input;
public:
	spellor(string _input) : _input(_input) {}
	string original_spelling() { return _input; }
};