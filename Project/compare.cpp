#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void compare() {
	string a, b;
	ifstream file1("sequence.txt");
	getline(file1, a);
	file1.close();
	ifstream file2("result.txt");
	getline(file2, b);
	file2.close();
	int cnt = 0;
	for (int i = 0; i < b.length(); i++) {
		if (a[i] == b[i]) {
			cnt++;
		}
	}
	cout << (double)cnt * 100.0 / (double)a.length() << "%\n";
}