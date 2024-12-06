// kmp.cpp
#include "kmp.h"
#include <vector>

using namespace std;

vector<int> compute_lps(const string& pattern) {
	int m = pattern.size();
	vector<int> lps(m, 0);
	int length = 0;
	int i = 1;

	while (i < m) {
		if (pattern[i] == pattern[length]) {
			length++;
			lps[i] = length;
			i++; 
		}
		else {
			if (length != 0) {
				length = lps[length - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
	return lps;
}

int execute_KMP(const string& reference, const string& read) {
	vector<int> lps = compute_lps(read);
	int i = 0; // reference 포인터
	int j = 0; // read 포인터

	while (i < reference.size()) {
		if (reference[i] == read[j]) {
			i++;
			j++;
		}
		if (j == read.size()) {
			return i - j; // 매칭 시작 위치 반환
		}
		else if (i < reference.size() && reference[i] != read[j]) {
			if (j != 0) {
				j = lps[j - 1];
			}
			else {
				i++;
			}
		}
	}
	return -1; // 매칭 실패 시
}
