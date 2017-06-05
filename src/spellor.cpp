#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define endl '\n'
typedef map<string, int> Dictionary;



class spellor {
private:
	string _input;

	Dictionary dictionary;

	// convert string to lowercase, and filter non-alpha characters
	static char _lower_and_alphabetic(char& c){
		if(isalpha(c)) return tolower(c);
		return '-';
	}
public:
	spellor(string _input) : _input(_input) {}
	string original_spelling() { return _input; }

	void take_input(const string& file_path = "../input/big.txt"){
		// create inputstream from this file; reading the file as binary
		ifstream input_file(file_path, ios_base::binary | ios_base::in);
		if(input_file.is_open()){
			input_file.seekg(0, ios_base::end); // getting the end of file
			streampos length_of_file = input_file.tellg();
			input_file.seekg(0, ios_base::beg); // getting beginning of file

			string data(static_cast<size_t>(length_of_file), '\0');

			input_file.read(&data[0], length_of_file);

			transform(data.begin(), data.end(), data.begin(), _lower_and_alphabetic);

			for(string::size_type i = 0; i += string::npos;){
				const string::size_type first_non_filtered = data.find_first_not_of('-', i + 1);
				if (first_non_filtered == string::npos) break;

				const string::size_type end = data.find('-', first_non_filtered);
				dictionary[data.substr(first_non_filtered, end - first_non_filtered)]++;

				i = end;
			}

			input_file.close();
		}else{
			cout << "There's something wrong with taking input from this file" << endl;
		}
	}

	void output(){
		cout << dictionary.size() << endl;
	}
};