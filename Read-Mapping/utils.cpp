// utils.cpp
#include "utils.h"
#include <fstream>
#include <iostream>
#include <fstream>

string reconstruct_sequence(const vector<string>& reads, const string& reference,
	int(*execute_function)(const string&, const string&)) {
	vector<bool> matched(reference.size(), false);
	string reconstructed(reference.size(), '-');

	for (const string& read : reads) {
		int start = execute_function(reference, read);
		if (start != -1) {
			for (int i = 0; i < read.size(); i++) {
				reconstructed[start + i] = read[i];
				matched[start + i] = true;
			}
		}
	}
	return reconstructed;
}

double calculate_accuracy(const string& reconstructed, const string& reference) {
	int correct = 0;
	int total = reference.size();

	for (int i = 0; i < total; i++) {
		if (reconstructed[i] == reference[i]) {
			correct++;
		}
	}
	return (double)correct / total * 100.0;
}

void run_and_measure(const vector<string>& reads, const string& reference,
	const string& function_name,
	int(*execute_function)(const string&, const string&),
	const string& output_filepath) {
	// 시작 시간 측정
	auto start_time = high_resolution_clock::now();

	// 시퀀스 복원
	string reconstructed_sequence = reconstruct_sequence(reads, reference, execute_function);

	// 끝 시간 측정
	auto end_time = high_resolution_clock::now();

	// 정확도 및 소요 시간 계산
	double accuracy = calculate_accuracy(reconstructed_sequence, reference);
	double elapsed_time = duration<double, milli>(end_time - start_time).count();

	// 결과 출력 (콘솔)
	cout << function_name << " Results:\n";
	cout << "Execution Time: " << elapsed_time / 1000.0 << " seconds\n";
	cout << "Accuracy: " << accuracy << "%\n\n";

	// 결과 출력(파일)
	ofstream file_output(output_filepath, ios::app); 
	if (file_output.is_open()) {
		file_output << function_name << " Results:\n";
		file_output << "Execution Time: " << elapsed_time / 1000.0 << " seconds\n";
		file_output << "Accuracy: " << accuracy << "%\n\n";
		file_output.close();
	}
	else {
		cerr << "Error: Unable to open the file " << output_filepath << endl;
	}
}


// 시퀀스 파일 읽기 함수
bool load_sequences(const string& sequence_file_path, string& reference_sequence) {
	
	ifstream sequence_file(sequence_file_path);
	
	if (!sequence_file.is_open()) {
		cerr << "Failed to open sequence file: " << sequence_file_path << endl;
		return false;
	}

	getline(sequence_file, reference_sequence);
	sequence_file.close();


	return true;
}

// 리드 파일 읽기 함수
bool load_reads(const string& reads_file_path, vector<string>& reads) {
	
	ifstream reads_file(reads_file_path);
	
	if (!reads_file.is_open()) {
		cerr << "Failed to open reads file: " << reads_file_path << endl;
		return false;
	}
	
	string read;
	
	while (getline(reads_file, read)) {
		reads.push_back(read);
	}
	
	reads_file.close();


	return true;
}
