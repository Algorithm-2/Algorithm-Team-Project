#include <iostream>
using namespace std;

struct Info {
	int N, L, P;
	int toggle;
};

Info input() {
	Info info = { 0,0,0,0 };
	cout << "sequence의 길이를 입력하세요 : "; cin >> info.N;
	cout << "read의 길이를 입력하세요 : "; cin >> info.L;
	cout << "read간 겹치는 길이를 입력하세요 : "; cin >> info.P;
	cout << "\n사용할 알고리즘을 선택하세요 \n";
	cout << "1. bruteforce (0)\n";
	cout << "2. enhanced bruteforce (1)\n";
	cout << "3. kmp (2)\n";
	cout << "4. kmp_lps_reuse (3)\n";
	cout << "5. rabin karp (4)\n";
	cout << "toggle : "; cin >> info.toggle;
	return info;
}