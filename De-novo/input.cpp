#include <iostream>
using namespace std;

struct Info {
	int N, L, P;
	int toggle;
};

Info input() {
	Info info = { 0,0,0,0 };
	cout << "sequence�� ���̸� �Է��ϼ��� : "; cin >> info.N;
	cout << "read�� ���̸� �Է��ϼ��� : "; cin >> info.L;
	cout << "read�� ��ġ�� ���̸� �Է��ϼ��� : "; cin >> info.P;
	cout << "\n����� �˰����� �����ϼ��� \n";
	cout << "1. bruteforce (0)\n";
	cout << "2. enhanced bruteforce (1)\n";
	cout << "3. kmp (2)\n";
	cout << "4. kmp_lps_reuse (3)\n";
	cout << "5. rabin karp (4)\n";
	cout << "toggle : "; cin >> info.toggle;
	return info;
}