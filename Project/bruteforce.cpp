#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

string d_result = "";
vector<string> reads_all; // 기본 브루트포스

// 정방향 기본 브루트포스 (read가 result의 뒤쪽에 붙는 경우)
bool d_bruteforce_forward(int curlen, vector<string> reads) {
	int res_pre_idx = d_result.length() - curlen; // result 문자열에서 패턴을 비교할 첫번째 인덱스
	int j;
	if (!reads.empty()) {
		for (int i = 0; i < reads.size(); i++) {
			for (j = 0; j < curlen; j++) { // 패턴 비교
				if (d_result[res_pre_idx + j] != reads[i][j]) break; // 패턴이 일치하지 않으면 break
			}
			if (j == curlen) { // 패턴 겹침
				d_result += reads[i].substr(curlen); // result 뒤쪽에 이어줌
				reads.erase(reads.begin() + i); // 이어준 read vector에서 삭제
				return true;
			}
		}
	}
	return false;
}

// 역방향 기본 브루트포스 (read가 result의 앞쪽에 붙는 경우)
bool d_bruteforce_backward(int curlen, vector<string> reads) {
	int read_pre_idx; // read 에서 패턴을 비교할 첫번째 인덱스
	int j;
	if (!reads.empty()) {
		for (int i = 0; i < reads.size(); i++) { // 패턴 비교
			read_pre_idx = reads[i].length() - curlen;
			for (j = 0; j < curlen; j++) {
				if (reads[i][read_pre_idx + j] != d_result[j]) break; // 패턴이 일치하지 않으면 break
			}
			if (j == curlen) { // 패턴 겹침
				d_result = reads[i] + d_result.substr(curlen); // result 앞쪽에 이어줌
				reads.erase(reads.begin() + i); // 이어준 read vector에서 삭제
				return true;
			}
		}
	}
	return false;
}

void d_createReadArray() { // 공간복잡도 O(read의 개수) / 시간복잡도 O(read의 개수)
	ifstream file("reads.txt");
	string line;
	bool isinit = false;
	while (getline(file, line)) {
		if (!isinit) {
			d_result = line; isinit = true;
		}
		reads_all.push_back(line);
	}
}

void d_execute_Bruteforce(int P) {
	d_createReadArray();
	int curlen = P;
	clock_t start = clock();
	while (true) { // 겹치는 길이가 하한점 까지 내려가면 더이상 일치하는 패턴이 존재하지 않음으로 종료
		bool flag = false; // 겹침 유무를 판단하는 변수
		// 순방향
		flag = d_bruteforce_forward(curlen, reads_all);
		// 역방향
		if (!flag) flag = d_bruteforce_backward(curlen, reads_all);
		// 매칭되는 read가 존재하지 않으면 종료
		if(!flag) break; 
	}
	clock_t end = clock();

	double duration = double(end - start) / CLOCKS_PER_SEC;
	cout << "Execution Time: " << duration << " seconds" << endl;
	ofstream file("result.txt");
	file << d_result << "\n";
	file.close();
}