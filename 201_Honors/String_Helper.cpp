#include "String_Helper.h"
#include <iostream>
#include <fstream>
#include <sstream>

vector<string> String_Helper::Words_From_ISS_By_Comma(istringstream& iss) {
	// If no commas return string
    string word;
	vector<string> words;

    while (getline(iss, word, ',')) {

        // add all the column data 
        // of a row to a vector 
        words.push_back(word);
    }

	return words;
}