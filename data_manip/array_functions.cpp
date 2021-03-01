#include "../includes/array_functions.h"
#include "../includes/utilities.h"
#include "../includes/constants.h"
#define ARRAY_FUNCTIONS_H_
#include <vector>
#include <algorithm>

using namespace std;
using namespace constants;
namespace KP{

	bool compareWord(const constants::entry& x, const constants::entry& y){
		return x.word_uppercase > y.word_uppercase;
	}

	bool compareWord2(const constants::entry& x, const constants::entry& y){
			return x.word_uppercase < y.word_uppercase;
	}

	bool compareNum(const constants::entry& x, const constants::entry& y){
				return x.number_occurences > y.number_occurences;
	}
	//zero out vector that tracks words and their occurrences
	void clear(std::vector<constants::entry>  &entries){
		entries.clear();
	}

		//how many unique words are in the vector
	int getSize(std::vector<constants::entry>  &entries){
		return entries.size();
	}

		//get data at a particular location, if i>size() then get the last value in the vector
		//(this is lazy, should throw an exception instead)
	std::string getWordAt(std::vector<constants::entry>  &entries, int i){
		return entries.at(i).word;
	}

	int getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
		return entries.at(i).number_occurences;
	}

		/*loop through whole file, one line at a time
		 * call processLine on each line from the file
		 * returns false: myfstream is not open
		 *         true: otherwise*/
	bool processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
		if (!myfstream.is_open()){
			return false;
		}
		std::string line;
		while(!myfstream.eof()){
			getline(myfstream, line);
			processLine(entries,line);
		}
		return true;
	}


		/*take 1 line and extract all the tokens from it
		feed each token to processToken for recording*/
	void processLine(std::vector<constants::entry>  &entries,std::string &myString){
		std::stringstream ss(myString);
		std::string p;
		while (getline(ss,p, constants::CHAR_TO_SEARCH_FOR)){
			processToken(entries,p);

		}

	}

		/*Keep track of how many times each token seen*/
	void processToken(std::vector<constants::entry>  &entries,std::string &token){
		if (!strip_unwanted_chars(token)){
			return;
		}
		std::string p = token;
		toUpper(p);
		for (int i =0; i < entries.size();i++){
			if (entries.at(i).word_uppercase.compare(p)==0){
				entries.at(i).number_occurences += 1;
				return;
			}
		}
		constants::entry n;
		n.number_occurences = 1;
		n.word = token;
		n.word_uppercase = p;
		entries.push_back(n);
	}

		/*
		 * Sort myEntryArray based on so enum value.
		 * Please provide a solution that sorts according to the enum
		 * The presence of the enum implies a switch statement based on its value
		 * See the course lectures and demo project for how to sort a vector of structs
		 */
	void sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
		switch(so){
			case(constants::sortOrder::NUMBER_OCCURRENCES):
				sort(entries.begin(), entries.end(), compareNum);
				break;
			case(constants::sortOrder::DESCENDING):
				sort(entries.begin(), entries.end(), compareWord);
				break;
			case(constants::sortOrder::ASCENDING):
				sort(entries.begin(), entries.end(), compareWord2);
				break;
			case(constants::sortOrder::NONE):
				break;
		}
	}
}
