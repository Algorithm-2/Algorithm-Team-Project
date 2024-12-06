#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include "utils.h"               // 유틸리티 함수들 (시퀀스 로드, 정확도 계산 등)
#include "sequenceGenerator.h"

using namespace std;
using namespace chrono; 

vector<string> reads_temp;
unordered_map<string, vector<int>> prefix_suffix_map;

void initialize_prefix_suffix_map(const vector<string>& reads) {
	prefix_suffix_map = unordered_map<string, vector<int>>(); // 기존 객체를 새로운 객체로 덮어씌움

	// 리드들을 순회하며 그룹화
	for (size_t i = 0; i < reads.size(); ++i) {
		char start_char = reads[i][0];                    // 시작 문자
		char end_char = reads[i][reads[i].size() - 1];    // 끝 문자
		string group = { start_char, end_char };            // 그룹 키 생성
		bool found = false;
		for (const auto& idx : prefix_suffix_map[group]) {
			if (reads[idx] == reads[i]) { // 리드가 동일하면 found를 true로 설정
				found = true;
				break;
			}
		}
		if (!found)
			prefix_suffix_map[group].push_back(i); // 해당 그룹에 리드 인덱스를 추가
	}
}

int find_read_in_group(const string& reference, const string& window, const vector<string>& reads) {
	// 윈도우의 시작 문자와 끝 문자를 통해 그룹 키 생성
	string group_key = { window[0], window[window.size() - 1] };

	// 해당 그룹에 리드가 있는지 확인
	auto it = prefix_suffix_map.find(group_key);
	if (it == prefix_suffix_map.end() || it->second.empty()) {
		return -1; // 그룹이 없거나, 비어 있는 경우
	}

	for (auto it_idx = it->second.begin(); it_idx != it->second.end(); ++it_idx) {
		int idx = *it_idx;
		if (reads[idx] == window) {
			// 해당 리드를 찾았으면, 인덱스를 제거한 후 반환
			it->second.erase(it_idx);  // 그룹에서 해당 리드 제거
			return idx; // 리드의 인덱스를 반환
		}
	}
	return -1; // 리드가 없으면 -1 반환
}

string restore_sequence(const string& reference, const vector<string>& reads) {
	string restored_sequence(reference.size(), '-');  // '-'로 초기화된 복원된 시퀀스
	size_t read_length = reads[0].size();  // 모든 리드는 동일한 길이로 가정

	for (size_t i = 0; i <= reference.size() - read_length; ++i) {
		string window = reference.substr(i, read_length);  // 레퍼런스에서 현재 슬라이딩 윈도우

		int match_idx = find_read_in_group(reference, window, reads); // 해당 윈도우에 맞는 리드를 찾기
		if (match_idx != -1) {
			for (int j = 0; j < read_length; ++j) {
				if (restored_sequence[i + j] == '-') {
					restored_sequence[i + j] = reads[match_idx][j]; // 복원된 시퀀스에서 해당 위치가 이미 복원된 부분이 아닌 경우에만 변경
				}
			}
		}
	}

	return restored_sequence; // 복원된 시퀀스를 반환
}

void print_prefix_suffix_map(const unordered_map<string, vector<int>>& map) {
	for (const auto& pair : map) {
		cout << "Group: " << pair.first << " -> Indices: ";
		for (const auto& index : pair.second) {
			cout << index << " ";
		}
		cout << endl;
	}
}

void execute_enhanced_bruteforce(const vector<string>& reads, const string& reference_genome, const string& output_filepath) {
	auto start_time = high_resolution_clock::now();
	// 배열(unordered map) 초기화
	initialize_prefix_suffix_map(reads);
	// 원래 시퀀스 복원
	string restored_sequence = restore_sequence(reference_genome, reads);
	auto end_time = high_resolution_clock::now();

	cout << "Enhanced_bruteforce:\n";
	// 시간 계산
	double elapsed_time = duration<double, milli>(end_time - start_time).count();
	cout << "Execution Time: " << elapsed_time / 1000.0 << " seconds\n";
	// 정확도 계산
	double accuracy = calculate_accuracy(reference_genome, restored_sequence);
	cout << "Accuracy:"<< accuracy << "%\n";

	ofstream file_output(output_filepath, ios::app);
	if (file_output.is_open()) {
		file_output << "Enhanced_bruteforce" << " Results:\n";
		file_output << "Execution Time: " << elapsed_time / 1000.0 << " seconds\n";
		file_output << "Accuracy: " << accuracy << "%\n\n";
		file_output.close();
	}
	else {
		cerr << "Error: Unable to open the file " << output_filepath << endl;
	}
}