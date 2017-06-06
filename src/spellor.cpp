#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

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

	static bool sort_by_second(const pair<std::string, int>& left, const pair<std::string, int>& right){
		return left.second < right.second;
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

	string correct(const string& word){
		vector<string> result;
		Dictionary candidates;

		if (dictionary.find(word) != dictionary.end()) { return word; }

		edits(word, result);
		known(result, candidates);

		if (candidates.size() > 0) { return max_element(candidates.begin(), candidates.end(), sort_by_second)->first; }

		for (unsigned int i = 0;i < result.size();i++){
			vector<string> subResult;

			edits(result[i], subResult);
			known(subResult, candidates);
		}

		if (candidates.size() > 0) { return max_element(candidates.begin(), candidates.end(), sort_by_second)->first; }

		return "";
	}

	void known(vector<string>& results, Dictionary& candidates){
		Dictionary::iterator end = dictionary.end();
		for(unsigned int i = 0; i < results.size(); i++){
			Dictionary::iterator value = dictionary.find(results[i]);
			if(value != end) candidates[value->first] = value->second;
		}
	}

	void edits(const string& word, vector<string>& result){
		for (string::size_type i = 0;i < word.size(); i++)    result.push_back(word.substr(0, i) + word.substr(i + 1)); //deletions
		for (string::size_type i = 0;i < word.size() - 1;i++) result.push_back(word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2)); //transposition

		for (char j = 'a';j <= 'z';++j){
			for (string::size_type i = 0;i < word.size(); i++)    result.push_back(word.substr(0, i) + j + word.substr(i + 1)); //alterations
			for (string::size_type i = 0;i < word.size() + 1;i++) result.push_back(word.substr(0, i) + j + word.substr(i)); //insertion
		}
  	}

	void output(){
		cout << dictionary.size() << endl;
		int i = 0;
		for (std::map<string, int>::iterator it=dictionary.begin(); it!=dictionary.end() ; ++it){
		    std::cout << it->first << " => " << it->second << '\n';
		    if(i == 10) break;
		}
	}
};