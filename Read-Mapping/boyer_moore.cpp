// boyer_moore.cpp
#include "boyer_moore.h"
#include <algorithm>
BoyerMoore::BoyerMoore() {}
 
void BoyerMoore::build_bad_char_table(const string& pattern) {
	for (int i = 0; i < pattern.size(); i++) {
		// 패턴 내에서 각 문자에 대해 가장 오른쪽 위치를 기록
		bad_char_table[pattern[i]] = i;
	}
}

vector<int> BoyerMoore::search(const string& text, const string& pattern) {
	vector<int> match_positions;
	int m = pattern.size();
	int n = text.size();

	if (m > n) return match_positions;

	build_bad_char_table(pattern);

	int s = 0;  // 패턴을 텍스트에서 비교할 시작 위치

	while (s <= n - m) {
		int j = m - 1;

		// 패턴의 끝에서부터 텍스트를 비교
		while (j >= 0 && pattern[j] == text[s + j]) {
			j--;
		}

		// 패턴이 완전히 일치했을 때
		if (j < 0) {
			match_positions.push_back(s);
			// 이동을 위해 bad character rule을 적용
			s += (s + m < n) ? m - bad_char_table[text[s + m]] : 1;
		}
		else {
			// 일치하지 않는 경우 bad character rule 적용
			s += max(1, j - bad_char_table[text[s + j]]);
		}
	}

	return match_positions;
}

int execute_boyer_moore(const string& reference, const string& read) {
	BoyerMoore bm;
	auto matches = bm.search(reference, read);
	return matches.empty() ? -1 : matches[0];
}
