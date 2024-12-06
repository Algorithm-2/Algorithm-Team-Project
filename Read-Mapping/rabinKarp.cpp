// rabinKarp.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "rabinKarp.h"

int execute_rabinkarp(const std::string& reference, const std::string& read) {
	const int prime = 101;       // �ؽø� ����ϱ� ���� �Ҽ�
	const int d = 256;           // ���� ���� �� (ASCII)
	int m = read.size();
	int n = reference.size();
	int h = 1;                   // �ؽð� ����� ���� h ��
	int read_hash = 0;           // ������ �ؽð�
	int ref_hash = 0;            // ���� â�� �ؽð�

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
				return i; // ��Ī ���� ��ġ ��ȯ
			}
		}
		if (i < n - m) {
			ref_hash = (d * (ref_hash - reference[i] * h) + reference[i + m]) % prime;
			if (ref_hash < 0) ref_hash += prime;
		}
	}
	return -1; // ��Ī ���� ��
}
