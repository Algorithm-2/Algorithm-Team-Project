// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// �������� �����ϴ� �Լ�
string reconstruct_sequence(const vector<string>& reads, const string& reference,
	int(*execute_function)(const string&, const string&));

// ��Ȯ�� ��� �Լ�
double calculate_accuracy(const string& reconstructed, const string& reference);

// �˰��� ���� �� �ð� ���� �Լ�
void run_and_measure(const vector<string>& reads, const string& reference,
	const string& function_name,
	int(*execute_function)(const string&, const string&),
	const string& output_filepath);


// ������ ���� �б� �Լ�
bool load_sequences(const string& sequence_file_path, string& reference_sequence);

// ���� ���� �б� �Լ�
bool load_reads(const string& reads_file_path, vector<string>& reads);

#endif // UTILS_H
