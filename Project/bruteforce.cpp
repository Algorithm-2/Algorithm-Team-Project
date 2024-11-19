#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#define MAXLEN 29	// 최대 겹치는 read 길이, 이는 read 생성 당시 (read의 길이 - 1)와 동일해야함. -> why? 완전 겹치면 이어붙이는게 아님
using namespace std;


string result = "";
vector<string> reads_A;
vector<string> reads_C;
vector<string> reads_T;
vector<string> reads_G;

bool bruteforce(int curlen, vector<string> &reads) {
	if (reads.size() == 0) return false; // 해당 알파벳으로 시작하는 벡터가 비어있음
	int res_pre_idx = result.length() - curlen;
	for (int i = 0; i < reads.size(); i++) {
		if (result[result.length() - 1] != reads[i][curlen - 1]) continue; // 겹치는 부분의 끝이 다르면 패스
		int j;
		for (j = 0; j < curlen; j++) {
			if (result[res_pre_idx + j] != reads[i][j]) break;
		}
		if (j == curlen) { // 문자열 겹침
			result += reads[i].substr(curlen);
			reads.erase(reads.begin() + i);
			return true;
		}
	}
	return false;
}

/* 변경사항
	1) 함수 내에서 첫번째 line값을 초기 result 값으로 설정
	2) 처음 알파벳에 따라 다른 벡터로 저장 (효율성 증가 목적)
	3) sort 과정 삭제 (4개의 벡터에 나누어 저장해 정렬 의미 사라짐)
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
	while (curlen) { // 겹치는 길이가 0까지 내려가면 더이상 일치하는 패턴이 존재하지 않음
		char res_pre_c = result[result.length() - curlen];
		bool flag = false;
		if (res_pre_c == 'A') flag = bruteforce(curlen, reads_A);
		else if (res_pre_c == 'C') flag = bruteforce(curlen, reads_C);
		else if (res_pre_c == 'T') flag = bruteforce(curlen, reads_T);
		else if (res_pre_c == 'G') flag = bruteforce(curlen, reads_G);
		if (flag) curlen = MAXLEN; // 문자열이 늘어났다면 최대 겹침 길이부터 다시 탐색
		else curlen--; // 문자열이 늘어나지 않았다면 겹침 길이를 줄여 다시 탐색
		cout << result << "\n\n";
	}
}

/*
cout << "for\n";
for (int i = 0; i < reads.size(); i++) {
	string tmp = bruteforce(reads[i]);
	if (result != tmp) { // 결과 스트링이 늘어남
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