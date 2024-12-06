#pragma once
// boyer_moore.h
#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H
 
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class BoyerMoore {
public:
	BoyerMoore();
	void build_bad_char_table(const string& pattern);
	vector<int> search(const string& text, const string& pattern);

private:
	unordered_map<char, int> bad_char_table;
};
int execute_boyer_moore(const string& reference, const string& read);
#endif // BOYER_MOORE_H
