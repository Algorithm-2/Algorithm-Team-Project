#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#define MAXLEN 29	// �ִ� ��ġ�� read ����, �̴� read ���� ��� (read�� ���� - 1)�� �����ؾ���. -> why? ���� ��ġ�� �̾���̴°� �ƴ�
using namespace std;


string result = "";
vector<string> reads_A;
vector<string> reads_C;
vector<string> reads_T;
vector<string> reads_G;

bool bruteforce(int curlen, vector<string> &reads) {
	if (reads.size() == 0) return false; // �ش� ���ĺ����� �����ϴ� ���Ͱ� �������
	int res_pre_idx = result.length() - curlen;
	for (int i = 0; i < reads.size(); i++) {
		if (result[result.length() - 1] != reads[i][curlen - 1]) continue; // ��ġ�� �κ��� ���� �ٸ��� �н�
		int j;
		for (j = 0; j < curlen; j++) {
			if (result[res_pre_idx + j] != reads[i][j]) break;
		}
		if (j == curlen) { // ���ڿ� ��ħ
			result += reads[i].substr(curlen);
			reads.erase(reads.begin() + i);
			return true;
		}
	}
	return false;
}

/* �������
	1) �Լ� ������ ù��° line���� �ʱ� result ������ ����
	2) ó�� ���ĺ��� ���� �ٸ� ���ͷ� ���� (ȿ���� ���� ����)
	3) sort ���� ���� (4���� ���Ϳ� ������ ������ ���� �ǹ� �����)
*/
void createReadArray() {
	ifstream file("read.txt");
	string line;
	bool isinit = false;
	while (getline(file, line)) {
		if (!isinit) {
			isinit = true;
			result = line;
		}
		else {
			if (line[0] == 'A') reads_A.push_back(line);
			else if (line[0] == 'C') reads_C.push_back(line);
			else if (line[0] == 'T') reads_T.push_back(line);
			else if (line[0] == 'G') reads_G.push_back(line);
		}
	}
}

void execute_Bruteforce() {
	createReadArray();
	int curlen = MAXLEN;
	while (curlen) { // ��ġ�� ���̰� 0���� �������� ���̻� ��ġ�ϴ� ������ �������� ����
		char res_pre_c = result[result.length() - curlen];
		bool flag = false;
		if (res_pre_c == 'A') flag = bruteforce(curlen, reads_A);
		else if (res_pre_c == 'C') flag = bruteforce(curlen, reads_C);
		else if (res_pre_c == 'T') flag = bruteforce(curlen, reads_T);
		else if (res_pre_c == 'G') flag = bruteforce(curlen, reads_G);
		if (flag) curlen = MAXLEN; // ���ڿ��� �þ�ٸ� �ִ� ��ħ ���̺��� �ٽ� Ž��
		else curlen--; // ���ڿ��� �þ�� �ʾҴٸ� ��ħ ���̸� �ٿ� �ٽ� Ž��
		cout << result << "\n\n";
	}
}

/*
cout << "for\n";
for (int i = 0; i < reads.size(); i++) {
	string tmp = bruteforce(reads[i]);
	if (result != tmp) { // ��� ��Ʈ���� �þ
		flag = true;
		result = tmp; reads.erase(reads.begin());
		break;
	}
}
cout << result << "\n";
*/

/*
	cout << result << ' ' << read << "\n";
	string res_pre = result.substr(0, PATTERNSIZE);
	cout << res_pre << ' ';
	string res_sur = result.substr(result.length() - PATTERNSIZE);
	cout << res_sur << ' ';
	string read_pre = read.substr(0, PATTERNSIZE);
	cout << read_pre << ' ';
	string read_sur = read.substr(read.length() - PATTERNSIZE);
	cout << read_sur << "\n";
	int i;
	for (i = 0; i < PATTERNSIZE; i++) {
		if (res_sur[i] != read_pre[i]) break;
	}
	if (i == PATTERNSIZE) {
		return result.substr(0, result.size() - PATTERNSIZE) + read;
	}
	for (i = 0; i < PATTERNSIZE; i++) {
		if (read_sur[i] != res_pre[i]) break;
	}
	if (i == PATTERNSIZE) {
		return read.substr(0, read.size() - PATTERNSIZE) + result;
	}
	return result;
*/