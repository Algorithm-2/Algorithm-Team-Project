// rabinKarp.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "rabinKarp.h"

int execute_rabinkarp(const std::string& reference, const std::string& read) {
	const int prime = 101;       // 해시를 계산하기 위한 소수
	const int d = 256;           // 고유 문자 수 (ASCII)
	int m = read.size();
	int n = reference.size();
	int h = 1;                   // 해시값 계산을 위한 h 값
	int read_hash = 0;           // 리드의 해시값
	int ref_hash = 0;            // 현재 창의 해시값

	for (int i = 0; i < m - 1; i++) {
		h = (h * d) % prime;
	}

	for (int i = 0; i < m; i++) {
		read_hash = (d * read_hash + read[i]) % prime;
		ref_hash = (d * ref_hash + reference[i]) % prime;
	}

	for (int i = 0; i <= n - m; i++) {
		if (read_hash == ref_hash) {
			if (reference.substr(i, m) == read) {
				return i; // 매칭 시작 위치 반환
			}
		}
		if (i < n - m) {
			ref_hash = (d * (ref_hash - reference[i] * h) + reference[i + m]) % prime;
			if (ref_hash < 0) ref_hash += prime;
		}
	}
	return -1; // 매칭 실패 시
}
