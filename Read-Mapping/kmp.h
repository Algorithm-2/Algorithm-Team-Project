// kmp.h

#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

// ������ LPS (Longest Prefix Suffix) �迭�� ���
std::vector<int> compute_lps(const std::string& pattern);

// KMP �˰��� ����: ��Ī ���� ��ġ ��ȯ, ���� �� -1 ��ȯ
int execute_KMP(const std::string& reference, const std::string& read);

#endif // KMP_H
 