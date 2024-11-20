#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#define MAXLEN 25	// �ִ� ��ġ�� read ����
using namespace std;

string result = "";
vector<string> reads_all; // ���� 
vector<string> reads_A[4];	// A�� �����ϴ� read���� �����, ������ ���ĺ��� ���� ����Ǵ� vector�� �ε����� �޶���
vector<string> reads_C[4];	// C�� �����ϴ� read���� �����, ������ ���ĺ��� ���� ����Ǵ� vector�� �ε����� �޶���
vector<string> reads_T[4];	// T�� �����ϴ� read���� �����, ������ ���ĺ��� ���� ����Ǵ� vector�� �ε����� �޶���
vector<string> reads_G[4];	// G�� �����ϴ� read���� �����, ������ ���ĺ��� ���� ����Ǵ� vector�� �ε����� �޶���

// ������ ���Ʈ���� (read�� result�� ���ʿ� �ٴ� ���)
bool bruteforce_forward(int curlen, vector<string>(&reads)[4]) {
	int res_pre_idx = result.length() - curlen; // result ���ڿ����� ������ ���� ù��° �ε���
	int j;
	for (int k = 0; k < 4; k++) { // Ư�� ���ĺ����� �����ϴ� 4���� vector�� ����
		if (reads[k].size() == 0) continue;  // vector�� ��������� �ǳʶ�

		for (int i = 0; i < reads[k].size(); i++) {
			for (j = 0; j < curlen; j++) { // ���� ��
				if (result[res_pre_idx + j] != reads[k][i][j]) break; // ������ ��ġ���� ������ break
			}
			if (j == curlen) { // ���� ��ħ
				result += reads[k][i].substr(curlen); // result ���ʿ� �̾���
				reads[k].erase(reads[k].begin() + i); // �̾��� read vector���� ����
				return true;
			}
		}
	}
	return false;
}

// ������ ���Ʈ���� (read�� result�� ���ʿ� �ٴ� ���)
bool bruteforce_backward(int curlen, vector<string>& reads_A, vector<string>& reads_C, vector<string>& reads_T, vector<string>& reads_G) {
	vector<vector<string>*> reads = { &reads_A, &reads_C, &reads_T, &reads_G }; // 4���� ���͸� �迭�� ����
	int read_pre_idx; // read ���� ������ ���� ù��° �ε���
	int j;
	for (auto& read : reads) { // �� ���Ϳ� ���� �ݺ�
		if (read->empty()) continue; // vector�� ��������� �ǳʶ�

		for (int i = 0; i < read->size(); i++) { // ���� ��
			read_pre_idx = (*read)[i].length() - curlen;
			for (j = 0; j < curlen; j++) {
				if ((*read)[i][read_pre_idx + j] != result[j]) break; // ������ ��ġ���� ������ break
			}
			if (j == curlen) { // ���� ��ħ
				result = (*read)[i] + result.substr(curlen); // result ���ʿ� �̾���
				read->erase(read->begin() + i); // �̾��� read vector���� ����
				return true;
			}
		}
	}
	return false;
}

void createReadArray() { // �������⵵ O(read�� ����) / �ð����⵵ O(read�� ����)
	ifstream file("reads.txt");
	string line;
	int cnt = 1;
	bool isinit = false;
	while (getline(file, line)) {
		if (line[0] == 'A') {
			if (line[line.length() - 1] == 'A') reads_A[0].push_back(line);			// A�� ������ A�� ������ read
			else if (line[line.length() - 1] == 'C') reads_A[1].push_back(line);	// A�� ������ C�� ������ read
			else if (line[line.length() - 1] == 'T') reads_A[2].push_back(line);	// A�� ������ T�� ������ read
			else if (line[line.length() - 1] == 'G') reads_A[3].push_back(line);	// A�� ������ G�� ������ read
		}
		else if (line[0] == 'C') {
			if (line[line.length() - 1] == 'A') reads_C[0].push_back(line);			// C�� ������ A�� ������ read
			else if (line[line.length() - 1] == 'C') reads_C[1].push_back(line);	// C�� ������ C�� ������ read
			else if (line[line.length() - 1] == 'T') reads_C[2].push_back(line);	// C�� ������ T�� ������ read
			else if (line[line.length() - 1] == 'G') reads_C[3].push_back(line);	// C�� ������ G�� ������ read
		}
		else if (line[0] == 'T') {
			if (line[line.length() - 1] == 'A') reads_T[0].push_back(line);			// T�� ������ A�� ������ read
			else if (line[line.length() - 1] == 'C') reads_T[1].push_back(line);	// T�� ������ C�� ������ read
			else if (line[line.length() - 1] == 'T') reads_T[2].push_back(line);	// T�� ������ T�� ������ read
			else if (line[line.length() - 1] == 'G') reads_T[3].push_back(line);	// T�� ������ G�� ������ read
		}
		else if (line[0] == 'G') {
			if (line[line.length() - 1] == 'A') reads_G[0].push_back(line);			// G�� ������ A�� ������ read
			else if (line[line.length() - 1] == 'C') reads_G[1].push_back(line);	// G�� ������ C�� ������ read
			else if (line[line.length() - 1] == 'T') reads_G[2].push_back(line);	// G�� ������ T�� ������ read
			else if (line[line.length() - 1] == 'G') reads_G[3].push_back(line);	// G�� ������ G�� ������ read
		}
		if (cnt == 500) result = line; // ������ ���� read�� ���ϴ� �κ�, ���� ��� �ӽ÷� ����
		cnt++;
	}
}

void execute_Bruteforce() {
	createReadArray();
	int curlen = MAXLEN;
	clock_t start = clock();
	while (curlen >= 15) { // ��ġ�� ���̰� ������ ���� �������� ���̻� ��ġ�ϴ� ������ �������� �������� ����
		bool flag = false; // ��ħ ������ �Ǵ��ϴ� ����
		// bruteforce(curlen,reads_all);
		char res_pre_c = result[result.length() - curlen]; // read�� result�� �ڿ� �ٴ� ��쿡 
		char res_sur_c = result[curlen - 1];
		// ������
		if (res_pre_c == 'A')  flag = bruteforce_forward(curlen, reads_A);			// A_ ������ ���
		else if (res_pre_c == 'C')  flag = bruteforce_forward(curlen, reads_C);		// C_ ������ ���
		else if (res_pre_c == 'T')  flag = bruteforce_forward(curlen, reads_T);		// T_ ������ ���
		else if (res_pre_c == 'G')  flag = bruteforce_forward(curlen, reads_G);		// G_ ������ ���
		// ������
		if (!flag) {
			if (res_sur_c == 'A') flag = bruteforce_backward(curlen, reads_A[0], reads_C[0], reads_T[0], reads_G[0]);			// _A ������ ���
			else if (res_sur_c == 'C') flag = bruteforce_backward(curlen, reads_A[1], reads_C[1], reads_T[1], reads_G[1]);		// _C ������ ���
			else if (res_sur_c == 'T') flag = bruteforce_backward(curlen, reads_A[2], reads_C[2], reads_T[2], reads_G[2]);		// _T ������ ���
			else if (res_sur_c == 'G') flag = bruteforce_backward(curlen, reads_A[3], reads_C[3], reads_T[3], reads_G[3]);		// _G ������ ���
		}
		if (flag) {
			curlen = MAXLEN; // ���ڿ��� �þ�ٸ� �ִ� ��ħ ���̺��� �ٽ� Ž��

			// � ������ read�� �Ҹ�Ǵ��� �ð��� ǥ��
			cout << reads_A[0].size() << ' ' << reads_A[1].size() << ' ' << reads_A[2].size() << ' ' << reads_A[3].size() << "\n";
			cout << reads_C[0].size() << ' ' << reads_C[1].size() << ' ' << reads_C[2].size() << ' ' << reads_C[3].size() << "\n";
			cout << reads_T[0].size() << ' ' << reads_T[1].size() << ' ' << reads_T[2].size() << ' ' << reads_T[3].size() << "\n";
			cout << reads_G[0].size() << ' ' << reads_G[1].size() << ' ' << reads_G[2].size() << ' ' << reads_G[3].size() << "\n\n";
		}
		else curlen--; // ���ڿ��� �þ�� �ʾҴٸ� ��ħ ���̸� �ٿ� �ٽ� Ž��
	}
	clock_t end = clock();
	double duration = double(end - start) / CLOCKS_PER_SEC;
	cout << "Execution Time: " << duration << " seconds" << endl;
	cout << result << "\n"; // ���� ������ ���ڿ� ���
	ofstream file("result.txt");
	file << result << "\n";
	file.close();
}