// boyer_moore.cpp
#include "boyer_moore.h"
#include <algorithm>
BoyerMoore::BoyerMoore() {}
 
void BoyerMoore::build_bad_char_table(const string& pattern) {
	for (int i = 0; i < pattern.size(); i++) {
		// ���� ������ �� ���ڿ� ���� ���� ������ ��ġ�� ���
		bad_char_table[pattern[i]] = i;
	}
}

vector<int> BoyerMoore::search(const string& text, const string& pattern) {
	vector<int> match_positions;
	int m = pattern.size();
	int n = text.size();

	if (m > n) return match_positions;

	build_bad_char_table(pattern);

	int s = 0;  // ������ �ؽ�Ʈ���� ���� ���� ��ġ

	while (s <= n - m) {
		int j = m - 1;

		// ������ ���������� �ؽ�Ʈ�� ��
		while (j >= 0 && pattern[j] == text[s + j]) {
			j--;
		}

		// ������ ������ ��ġ���� ��
		if (j < 0) {
			match_positions.push_back(s);
			// �̵��� ���� bad character rule�� ����
			s += (s + m < n) ? m - bad_char_table[text[s + m]] : 1;
		}
		else {
			// ��ġ���� �ʴ� ��� bad character rule ����
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
