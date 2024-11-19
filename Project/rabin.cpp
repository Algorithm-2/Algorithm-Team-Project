#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int d = 4;          // 진수
int pattern = 10;   // 고정 겹치는 부분 길이
int q = 101;        // 소수(모듈러)

// 문자를 숫자로 변환
int charToValue(char c) {
	switch (c) {
	case 'A': return 0;
	case 'C': return 1;
	case 'G': return 2;
	case 'T': return 3;
	default: return -1; // 잘못된 입력 처리
	}
}

// 해시값 계산
int gethash(const string& read) {
	int hash = 0;
	for (char c : read) {
		hash = (d * hash + charToValue(c)) % q;
	}
	return hash;
}

// 일치율 계산
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

// 모든 visited가 true인지 확인하는 함수
bool allVisited(vector<bool>& visited) {
	for (bool v : visited) {
		if (!v) return false;
	}
	return true;
}

void execute_Rabin() {
	ifstream inputFile("read.txt");
	if (!inputFile) {
		cerr << "파일을 열 수 없습니다." << endl;
		exit(1);
	}

	vector<string> lines; // read 저장 배열
	string line;

	while (getline(inputFile, line)) {
		lines.push_back(line);
	}
	inputFile.close();

	if (lines.empty()) {
		cerr << "입력 데이터가 비어 있습니다." << endl;
		exit(1);
	}

	string result = lines[0]; // 첫 번째 read를 result로 초기화
	vector<bool> visited(lines.size(), false); // 각 read들의 사용 여부
	visited[0] = true; // 첫 번째 read 사용
	int j = 1;
	while (!allVisited(visited)) { // 모든 read들을 사용할 때까지 반복
		if (!visited[j]) {
			string nread_pre = lines[j].substr(0, pattern);
			string nread_suf = lines[j].substr(lines[j].size() - pattern, pattern);

			// 해시값 계산
			int nread_pre_hash = gethash(nread_pre);
			int nread_suf_hash = gethash(nread_suf);

			// result의 앞부분과 read의 뒷부분 겹침
			if (gethash(result.substr(0, pattern)) == nread_suf_hash && result.substr(0, pattern) == nread_suf) {
				result = lines[j].substr(0, lines[j].size() - pattern) + result;
				visited[j] = true;
			}
			// result의 뒷부분과 read의 앞부분 겹침
			else if (gethash(result.substr(result.size() - pattern, pattern)) == nread_pre_hash && result.substr(result.size() - pattern, pattern) == nread_pre) {
				result += lines[j].substr(pattern);
				visited[j] = true;
			}
		}
		j = (j + 1) % lines.size(); // read 배열 계속 돌면서 찾기
	}

	// 복원된 문자열을 result.txt에 저장
	ofstream resultFile("result.txt");
	resultFile << result;
	resultFile.close();

	// 원본과 일치율 계산
	ifstream originalFile("sequence.txt");
	if (!originalFile) {
		cerr << "원본 파일을 열 수 없습니다." << endl;
		exit(1);
	}

	string original;
	getline(originalFile, original);
	originalFile.close();

	double matchRate = calculateMatchRate(original, result);
	cout << "복원된 DNA 서열이 원본과 " << matchRate << "% 일치합니다." << endl;
}