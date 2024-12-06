// bruteforce.cpp
#include "bruteforce.h"

int execute_bruteforce(const std::string& reference, const std::string& read) {
	for (int i = 0; i <= reference.size() - read.size(); i++) {
		if (reference.substr(i, read.size()) == read) {
			return i; // ��Ī ���� ��ġ ��ȯ
		}
	}
	return -1; // ��Ī ����
}
 