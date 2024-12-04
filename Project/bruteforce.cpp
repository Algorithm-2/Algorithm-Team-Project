#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#define MAXLEN 10	// �ִ� ��ġ�� read ����
using namespace std;

string result = "";
vector<string> reads_all; // �⺻ ���Ʈ����

// ������ �⺻ ���Ʈ���� (read�� result�� ���ʿ� �ٴ� ���)
bool d_bruteforce_forward(int curlen, vector<string> reads) {
	int res_pre_idx = result.length() - curlen; // result ���ڿ����� ������ ���� ù��° �ε���
	int j;
	if (!reads.empty()) {
		for (int i = 0; i < reads.size(); i++) {
			for (j = 0; j < curlen; j++) { // ���� ��
				if (result[res_pre_idx + j] != reads[i][j]) break; // ������ ��ġ���� ������ break
			}
			if (j == curlen) { // ���� ��ħ
				result += reads[i].substr(curlen); // result ���ʿ� �̾���
				reads.erase(reads.begin() + i); // �̾��� read vector���� ����
				return true;
			}
		}
	}
	return false;
}

// ������ �⺻ ���Ʈ���� (read�� result�� ���ʿ� �ٴ� ���)
bool d_bruteforce_backward(int curlen, vector<string> reads) {
	int read_pre_idx; // read ���� ������ ���� ù��° �ε���
	int j;
	if (!reads.empty()) {
		for (int i = 0; i < reads.size(); i++) { // ���� ��
			read_pre_idx = reads[i].length() - curlen;
			for (j = 0; j < curlen; j++) {
				if (reads[i][read_pre_idx + j] != result[j]) break; // ������ ��ġ���� ������ break
			}
			if (j == curlen) { // ���� ��ħ
				result = reads[i] + result.substr(curlen); // result ���ʿ� �̾���
				reads.erase(reads.begin() + i); // �̾��� read vector���� ����
				return true;
			}
		}
	}
	return false;
}

void d_createReadArray() { // �������⵵ O(read�� ����) / �ð����⵵ O(read�� ����)
	ifstream file("reads.txt");
	string line;
	bool isinit = false;
	while (getline(file, line)) {
		if (!isinit) {
			result = line; isinit = true;
		}
		reads_all.push_back(line);
	}
}

void execute_Bruteforce(int P) {
	d_createReadArray();
	int curlen = P;
	clock_t start = clock();
	while (true) { // ��ġ�� ���̰� ������ ���� �������� ���̻� ��ġ�ϴ� ������ �������� �������� ����
		bool flag = false; // ��ħ ������ �Ǵ��ϴ� ����
		// ������
		flag = d_bruteforce_forward(curlen, reads_all);
		// ������
		if (!flag) flag = d_bruteforce_backward(curlen, reads_all);
		// ��Ī�Ǵ� read�� �������� ������ ����
		if(!flag) break; 
	}
	clock_t end = clock();

	double duration = double(end - start) / CLOCKS_PER_SEC;
	cout << "Execution Time: " << duration << " seconds" << endl;
	ofstream file("result.txt");
	file << result << "\n";
	file.close();
}