// kmp.h

#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

// 패턴의 LPS (Longest Prefix Suffix) 배열을 계산
std::vector<int> compute_lps(const std::string& pattern);

// KMP 알고리즘 실행: 매칭 시작 위치 반환, 실패 시 -1 반환
int execute_KMP(const std::string& reference, const std::string& read);

#endif // KMP_H
 