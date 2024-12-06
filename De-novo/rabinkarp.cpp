#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>
using namespace std;

#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

int d = 4;          // 진수
int q = 10007;      // 모듈러 계산을 위한 소수

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

vector<string> rb_createReadArray() {
    ifstream inputFile("reads.txt");
    vector<string> lines;
    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}

void execute_RabinKarp(int pattern) {
    
    vector<string> lines = rb_createReadArray();
    clock_t start = clock();

    // 해시 테이블 생성
    vector<tuple<int, string, int>> readNhash; // read, read의 접두사 해시값, read의 접미사 해시값 저장된 tuple 배열
    for (int i = 0; i < lines.size(); i++) {
        readNhash.push_back({
            gethash(lines[i].substr(0, pattern)), // read 접두사 해시값
            lines[i], // read
            gethash(lines[i].substr(lines[i].size() - pattern, pattern)) // read 접미사 해시값
            });
    }

    // 첫 번째 read를 result로 초기화
    string result = get<1>(readNhash[0]);
    int resultPreHash = get<0>(readNhash[0]);
    int resultSufHash = get<2>(readNhash[0]);

    bool endcheck; // 이전 실행에서 result가 변경되었는지 확인하는 변수
    while (true) {
        endcheck = false;
        for (auto it = readNhash.begin() + 1; it != readNhash.end();) { // 해시테이블에 남아있는 모든 read 탐색
            if (resultPreHash == get<2>(*it)) { // result의 접두사 해시값과 read의 접미사 해시값 같은지 확인 (result 앞에 read가 붙는 경우)
                if (result.substr(0, pattern) == get<1>(*it).substr(get<1>(*it).size() - pattern, pattern)) { // 실제로 같은지 확인
                    result = get<1>(*it).substr(0, get<1>(*it).size() - pattern) + result; // result 앞에 read 붙이기
                    resultPreHash = get<0>(*it); // result 해시값 업데이트
                    it = readNhash.erase(it); // 현재 요소 제거 후 반복자 갱신
                    endcheck = true;
                    continue; // 다음 반복자로 이동
                }
            }
            else if (resultSufHash == get<0>(*it)) { // result의 접미사 해시값과 read의 접두사 해시값 같은지 확인 (result 뒤에 read가 붙는 경우)
                if (result.substr(result.size() - pattern, pattern) == get<1>(*it).substr(0, pattern)) { // 실제로 같은지 확인
                    result = result + get<1>(*it).substr(pattern); // result 뒤에 read 붙이기
                    resultSufHash = get<2>(*it); // result 해시값 업데이트
                    it = readNhash.erase(it); // 현재 요소 제거 후 반복자 갱신
                    endcheck = true;
                    continue; // 다음 반복자로 이동
                }
            }
            ++it; // 조건을 만족하지 않으면 다음 요소로 이동
        }

        if (!endcheck) { // endcheck==false라면 이전 실행에서 result가 변경되지 않았으므로 더이상 추가할 read가 없다는 것을 의미
            break;
        }
    }

    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Execution Time: " << duration << " seconds" << endl;

    // 복원된 문자열을 result.txt에 저장
    ofstream resultFile("result.txt");
    resultFile << result;
    resultFile.close();
}