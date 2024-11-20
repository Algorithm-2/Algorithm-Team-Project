#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#define MAXLEN 25	// 최대 겹치는 read 길이
using namespace std;

string result = "";
vector<string> reads_all; // 완전 
vector<string> reads_A[4];	// A로 시작하는 read들이 저장됨, 끝나는 알파벳에 따라 저장되는 vector의 인덱스가 달라짐
vector<string> reads_C[4];	// C로 시작하는 read들이 저장됨, 끝나는 알파벳에 따라 저장되는 vector의 인덱스가 달라짐
vector<string> reads_T[4];	// T로 시작하는 read들이 저장됨, 끝나는 알파벳에 따라 저장되는 vector의 인덱스가 달라짐
vector<string> reads_G[4];	// G로 시작하는 read들이 저장됨, 끝나는 알파벳에 따라 저장되는 vector의 인덱스가 달라짐

// 정방향 브루트포스 (read가 result의 뒤쪽에 붙는 경우)
bool bruteforce_forward(int curlen, vector<string>(&reads)[4]) {
	int res_pre_idx = result.length() - curlen; // result 문자열에서 패턴을 비교할 첫번째 인덱스
	int j;
	for (int k = 0; k < 4; k++) { // 특정 알파벳으로 시작하는 4개의 vector에 대해
		if (reads[k].size() == 0) continue;  // vector가 비어있으면 건너뜀

		for (int i = 0; i < reads[k].size(); i++) {
			for (j = 0; j < curlen; j++) { // 패턴 비교
				if (result[res_pre_idx + j] != reads[k][i][j]) break; // 패턴이 일치하지 않으면 break
			}
			if (j == curlen) { // 패턴 겹침
				result += reads[k][i].substr(curlen); // result 뒤쪽에 이어줌
				reads[k].erase(reads[k].begin() + i); // 이어준 read vector에서 삭제
				return true;
			}
		}
	}
	return false;
}

// 역방향 브루트포스 (read가 result의 앞쪽에 붙는 경우)
bool bruteforce_backward(int curlen, vector<string>& reads_A, vector<string>& reads_C, vector<string>& reads_T, vector<string>& reads_G) {
	vector<vector<string>*> reads = { &reads_A, &reads_C, &reads_T, &reads_G }; // 4개의 벡터를 배열로 묶기
	int read_pre_idx; // read 에서 패턴을 비교할 첫번째 인덱스
	int j;
	for (auto& read : reads) { // 각 벡터에 대해 반복
		if (read->empty()) continue; // vector가 비어있으면 건너뜀

		for (int i = 0; i < read->size(); i++) { // 패턴 비교
			read_pre_idx = (*read)[i].length() - curlen;
			for (j = 0; j < curlen; j++) {
				if ((*read)[i][read_pre_idx + j] != result[j]) break; // 패턴이 일치하지 않으면 break
			}
			if (j == curlen) { // 패턴 겹침
				result = (*read)[i] + result.substr(curlen); // result 앞쪽에 이어줌
				read->erase(read->begin() + i); // 이어준 read vector에서 삭제
				return true;
			}
		}
	}
	return false;
}

void createReadArray() { // 공간복잡도 O(read의 개수) / 시간복잡도 O(read의 개수)
	ifstream file("reads.txt");
	string line;
	int cnt = 1;
	bool isinit = false;
	while (getline(file, line)) {
		if (line[0] == 'A') {
			if (line[line.length() - 1] == 'A') reads_A[0].push_back(line);			// A로 시작해 A로 끝나는 read
			else if (line[line.length() - 1] == 'C') reads_A[1].push_back(line);	// A로 시작해 C로 끝나는 read
			else if (line[line.length() - 1] == 'T') reads_A[2].push_back(line);	// A로 시작해 T로 끝나는 read
			else if (line[line.length() - 1] == 'G') reads_A[3].push_back(line);	// A로 시작해 G로 끝나는 read
		}
		else if (line[0] == 'C') {
			if (line[line.length() - 1] == 'A') reads_C[0].push_back(line);			// C로 시작해 A로 끝나는 read
			else if (line[line.length() - 1] == 'C') reads_C[1].push_back(line);	// C로 시작해 C로 끝나는 read
			else if (line[line.length() - 1] == 'T') reads_C[2].push_back(line);	// C로 시작해 T로 끝나는 read
			else if (line[line.length() - 1] == 'G') reads_C[3].push_back(line);	// C로 시작해 G로 끝나는 read
		}
		else if (line[0] == 'T') {
			if (line[line.length() - 1] == 'A') reads_T[0].push_back(line);			// T로 시작해 A로 끝나는 read
			else if (line[line.length() - 1] == 'C') reads_T[1].push_back(line);	// T로 시작해 C로 끝나는 read
			else if (line[line.length() - 1] == 'T') reads_T[2].push_back(line);	// T로 시작해 T로 끝나는 read
			else if (line[line.length() - 1] == 'G') reads_T[3].push_back(line);	// T로 시작해 G로 끝나는 read
		}
		else if (line[0] == 'G') {
			if (line[line.length() - 1] == 'A') reads_G[0].push_back(line);			// G로 시작해 A로 끝나는 read
			else if (line[line.length() - 1] == 'C') reads_G[1].push_back(line);	// G로 시작해 C로 끝나는 read
			else if (line[line.length() - 1] == 'T') reads_G[2].push_back(line);	// G로 시작해 T로 끝나는 read
			else if (line[line.length() - 1] == 'G') reads_G[3].push_back(line);	// G로 시작해 G로 끝나는 read
		}
		if (cnt == 500) result = line; // 임의의 시작 read를 정하는 부분, 구현 대신 임시로 설정
		cnt++;
	}
}

void execute_Bruteforce() {
	createReadArray();
	int curlen = MAXLEN;
	clock_t start = clock();
	while (curlen >= 15) { // 겹치는 길이가 하한점 까지 내려가면 더이상 일치하는 패턴이 존재하지 않음으로 종료
		bool flag = false; // 겹침 유무를 판단하는 변수
		// bruteforce(curlen,reads_all);
		char res_pre_c = result[result.length() - curlen]; // read가 result의 뒤에 붙는 경우에 
		char res_sur_c = result[curlen - 1];
		// 순방향
		if (res_pre_c == 'A')  flag = bruteforce_forward(curlen, reads_A);			// A_ 형식인 경우
		else if (res_pre_c == 'C')  flag = bruteforce_forward(curlen, reads_C);		// C_ 형식인 경우
		else if (res_pre_c == 'T')  flag = bruteforce_forward(curlen, reads_T);		// T_ 형식인 경우
		else if (res_pre_c == 'G')  flag = bruteforce_forward(curlen, reads_G);		// G_ 형식인 경우
		// 역방향
		if (!flag) {
			if (res_sur_c == 'A') flag = bruteforce_backward(curlen, reads_A[0], reads_C[0], reads_T[0], reads_G[0]);			// _A 형식인 경우
			else if (res_sur_c == 'C') flag = bruteforce_backward(curlen, reads_A[1], reads_C[1], reads_T[1], reads_G[1]);		// _C 형식인 경우
			else if (res_sur_c == 'T') flag = bruteforce_backward(curlen, reads_A[2], reads_C[2], reads_T[2], reads_G[2]);		// _T 형식인 경우
			else if (res_sur_c == 'G') flag = bruteforce_backward(curlen, reads_A[3], reads_C[3], reads_T[3], reads_G[3]);		// _G 형식인 경우
		}
		if (flag) {
			curlen = MAXLEN; // 문자열이 늘어났다면 최대 겹침 길이부터 다시 탐색

			// 어떤 유형의 read가 소모되는지 시각적 표시
			cout << reads_A[0].size() << ' ' << reads_A[1].size() << ' ' << reads_A[2].size() << ' ' << reads_A[3].size() << "\n";
			cout << reads_C[0].size() << ' ' << reads_C[1].size() << ' ' << reads_C[2].size() << ' ' << reads_C[3].size() << "\n";
			cout << reads_T[0].size() << ' ' << reads_T[1].size() << ' ' << reads_T[2].size() << ' ' << reads_T[3].size() << "\n";
			cout << reads_G[0].size() << ' ' << reads_G[1].size() << ' ' << reads_G[2].size() << ' ' << reads_G[3].size() << "\n\n";
		}
		else curlen--; // 문자열이 늘어나지 않았다면 겹침 길이를 줄여 다시 탐색
	}
	clock_t end = clock();
	double duration = double(end - start) / CLOCKS_PER_SEC;
	cout << "Execution Time: " << duration << " seconds" << endl;
	cout << result << "\n"; // 최종 구성된 문자열 출력
	ofstream file("result.txt");
	file << result << "\n";
	file.close();
}