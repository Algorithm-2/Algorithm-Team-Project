#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int d = 4;          // ����
int pattern = 10;   // ���� ��ġ�� �κ� ����
int q = 101;        // �Ҽ�(��ⷯ)

// ���ڸ� ���ڷ� ��ȯ
int charToValue(char c) {
	switch (c) {
	case 'A': return 0;
	case 'C': return 1;
	case 'G': return 2;
	case 'T': return 3;
	default: return -1; // �߸��� �Է� ó��
	}
}

// �ؽð� ���
int gethash(const string& read) {
	int hash = 0;
	for (char c : read) {
		hash = (d * hash + charToValue(c)) % q;
	}
	return hash;
}

// ��ġ�� ���
double calculateMatchRate(const string& original, const string& reconstructed) {
	int matchCount = 0;
	int minLength = min(original.size(), reconstructed.size());

	for (int i = 0; i < minLength; ++i) {
		if (original[i] == reconstructed[i]) {
			matchCount++;
		}
	}

	return (static_cast<double>(matchCount) / original.size()) * 100;
}

// ��� visited�� true���� Ȯ���ϴ� �Լ�
bool allVisited(vector<bool>& visited) {
	for (bool v : visited) {
		if (!v) return false;
	}
	return true;
}

void execute_Rabin() {
	ifstream inputFile("read.txt");
	if (!inputFile) {
		cerr << "������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	vector<string> lines; // read ���� �迭
	string line;

	while (getline(inputFile, line)) {
		lines.push_back(line);
	}
	inputFile.close();

	if (lines.empty()) {
		cerr << "�Է� �����Ͱ� ��� �ֽ��ϴ�." << endl;
		exit(1);
	}

	string result = lines[0]; // ù ��° read�� result�� �ʱ�ȭ
	vector<bool> visited(lines.size(), false); // �� read���� ��� ����
	visited[0] = true; // ù ��° read ���
	int j = 1;
	while (!allVisited(visited)) { // ��� read���� ����� ������ �ݺ�
		if (!visited[j]) {
			string nread_pre = lines[j].substr(0, pattern);
			string nread_suf = lines[j].substr(lines[j].size() - pattern, pattern);

			// �ؽð� ���
			int nread_pre_hash = gethash(nread_pre);
			int nread_suf_hash = gethash(nread_suf);

			// result�� �պκа� read�� �޺κ� ��ħ
			if (gethash(result.substr(0, pattern)) == nread_suf_hash && result.substr(0, pattern) == nread_suf) {
				result = lines[j].substr(0, lines[j].size() - pattern) + result;
				visited[j] = true;
			}
			// result�� �޺κа� read�� �պκ� ��ħ
			else if (gethash(result.substr(result.size() - pattern, pattern)) == nread_pre_hash && result.substr(result.size() - pattern, pattern) == nread_pre) {
				result += lines[j].substr(pattern);
				visited[j] = true;
			}
		}
		j = (j + 1) % lines.size(); // read �迭 ��� ���鼭 ã��
	}

	// ������ ���ڿ��� result.txt�� ����
	ofstream resultFile("result.txt");
	resultFile << result;
	resultFile.close();

	// ������ ��ġ�� ���
	ifstream originalFile("sequence.txt");
	if (!originalFile) {
		cerr << "���� ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	string original;
	getline(originalFile, original);
	originalFile.close();

	double matchRate = calculateMatchRate(original, result);
	cout << "������ DNA ������ ������ " << matchRate << "% ��ġ�մϴ�." << endl;
}