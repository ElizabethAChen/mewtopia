///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

// Convenient typedef for a vector of strings.
typedef vector<string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or false on I/O error.
bool load_words(string_vector& words, const string& path) {
	ifstream file;
	file.open(path);
	if (!file.is_open()) //if not open there was an error
	{
		return false;
	}

	else{
		words.clear(); //clear the string vector
		string word;
		while (file >> word) //while there are words to add to the vector
		{
			words.push_back(word); //add word to string vector
		}
	}
	file.close();
  
	return true;
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const string& string1, const string& string2) {
	if (string1 == string2) //strings cannot be equal
	{
		return false;
	}
	else 	
	{
		string::const_iterator fromFront = string1.begin();
		string::const_reverse_iterator fromBack = string2.rbegin(); 
		while  (fromFront != string1.end() || fromBack != string2.rend()){
			if (*fromFront != *fromBack)
			{
				return false;
			}
			else // string1 matches string2 at the opposite point in the index
			{
				fromFront++;
				fromBack++;
			}
		}	
	}
	return true;
}
	

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const string& alleged_substring, const string& alleged_superstring) {
	size_t found = alleged_superstring.find(alleged_substring);
	
	if (found != string::npos) // if the sub has a position within the super it will return true 
	{
		return true;
	}
	
	return false;
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
		if (!strings.empty())
	{
		vector<int>charCounter(256, 0);

		vector<string>::const_iterator i = strings.begin(); //iterator for vector of strings
		for (i; i != strings.end(); i++)
		{
			string word = *i;
			string::iterator j = word.begin(); //iterator for chars in words
			for (j; j != word.end(); j++)
			{	
				int index = int(unsigned char(*j));	//converts to ASCII value
				charCounter[index]++; // each time a letter is spotted add it as the index to the counter
				
			}
		}

		char c = 0;
		int max = charCounter[0];
		for (int i = 0; i < charCounter.size(); i++)
		{
			if (max < charCounter[i])
			{
				max = charCounter[i];
				c = char(i);
			}
		}
		return c;
	}
		return 0; //if empty does nothing
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
string longest_mirrored_string(const string_vector& strings) {
	string best = ""; //longest mirrored string in string_vectors
	string a = ""; //string a will be compared to
	string b = ""; //string b
	for (int i = 0; i < strings.size(); i++) //start at string a
	{
		a = strings[i];
		for (int j = i + 1; j < strings.size(); j++) //compare it to all the strings in
													 //string vector with string b
		{
			b = strings[j];
			if ((is_mirrored(a, b)) && (a.size() > best.size()))
				//Are a and b mirrored? does the string a have more characters than the
				//current longest string
			{
				best = a; //if so update the best string as a
			}
		}

	}
	
	return best;
}


// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	int best_length = 0; 
	int abc_length = 0;
	string a = ""; //string a will be compared to 
	string b = ""; // string b and then string b will be 
	string c = ""; // compared to string c.
	string_vector trio = { "", "", "" }; // here we have a vector containing strings a,b,c

	for (int i = 0; i < strings.size(); i++)
	{
		a = strings[i];
		for (int j = 0; j < strings.size(); j++)
		{
			b = strings[j];
			for (int k = 0; k < strings.size(); k++) //comaprisons 
			{
				c = strings[k];
				abc_length = a.size() + b.size() + c.size();
				if ((a != b) && (b != c) && is_substring(a, b) && is_substring(b, c) && (abc_length > best_length))
				{ //if the input contains a substring trio, return a vector containing three strings.
					best_length = abc_length;
					//cout << "Strings " << strings[i] << " " << strings[j] << " " << strings[k] << "\n";
					trio[0] = a;
					trio[1] = b;
					trio[2] = c;
					//cout << "Trios: " << trio[0] << " " << trio[1] << " " << trio[2] << "\n";
				}
			}
		}

	}
	return trio; //returning a vector of length exactly three.
}
