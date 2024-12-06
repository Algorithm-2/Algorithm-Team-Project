// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// 시퀀스를 복원하는 함수
string reconstruct_sequence(const vector<string>& reads, const string& reference,
	int(*execute_function)(const string&, const string&));

// 정확도 계산 함수
double calculate_accuracy(const string& reconstructed, const string& reference);

// 알고리즘 실행 및 시간 측정 함수
void run_and_measure(const vector<string>& reads, const string& reference,
	const string& function_name,
	int(*execute_function)(const string&, const string&),
	const string& output_filepath);


// 시퀀스 파일 읽기 함수
bool load_sequences(const string& sequence_file_path, string& reference_sequence);

// 리드 파일 읽기 함수
bool load_reads(const string& reads_file_path, vector<string>& reads);

#endif // UTILS_H
