#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include "utils.h"               // ��ƿ��Ƽ �Լ��� (������ �ε�, ��Ȯ�� ��� ��)
#include "sequenceGenerator.h"

using namespace std;
using namespace chrono; 

vector<string> reads_temp;
unordered_map<string, vector<int>> prefix_suffix_map;

void initialize_prefix_suffix_map(const vector<string>& reads) {
	prefix_suffix_map = unordered_map<string, vector<int>>(); // ���� ��ü�� ���ο� ��ü�� �����

	// ������� ��ȸ�ϸ� �׷�ȭ
	for (size_t i = 0; i < reads.size(); ++i) {
		char start_char = reads[i][0];                    // ���� ����
		char end_char = reads[i][reads[i].size() - 1];    // �� ����
		string group = { start_char, end_char };            // �׷� Ű ����
		bool found = false;
		for (const auto& idx : prefix_suffix_map[group]) {
			if (reads[idx] == reads[i]) { // ���尡 �����ϸ� found�� true�� ����
				found = true;
				break;
			}
		}
		if (!found)
			prefix_suffix_map[group].push_back(i); // �ش� �׷쿡 ���� �ε����� �߰�
	}
}

int find_read_in_group(const string& reference, const string& window, const vector<string>& reads) {
	// �������� ���� ���ڿ� �� ���ڸ� ���� �׷� Ű ����
	string group_key = { window[0], window[window.size() - 1] };

	// �ش� �׷쿡 ���尡 �ִ��� Ȯ��
	auto it = prefix_suffix_map.find(group_key);
	if (it == prefix_suffix_map.end() || it->second.empty()) {
		return -1; // �׷��� ���ų�, ��� �ִ� ���
	}

	for (auto it_idx = it->second.begin(); it_idx != it->second.end(); ++it_idx) {
		int idx = *it_idx;
		if (reads[idx] == window) {
			// �ش� ���带 ã������, �ε����� ������ �� ��ȯ
			it->second.erase(it_idx);  // �׷쿡�� �ش� ���� ����
			return idx; // ������ �ε����� ��ȯ
		}
	}
	return -1; // ���尡 ������ -1 ��ȯ
}

string restore_sequence(const string& reference, const vector<string>& reads) {
	string restored_sequence(reference.size(), '-');  // '-'�� �ʱ�ȭ�� ������ ������
	size_t read_length = reads[0].size();  // ��� ����� ������ ���̷� ����

	for (size_t i = 0; i <= reference.size() - read_length; ++i) {
		string window = reference.substr(i, read_length);  // ���۷������� ���� �����̵� ������

		int match_idx = find_read_in_group(reference, window, reads); // �ش� �����쿡 �´� ���带 ã��
		if (match_idx != -1) {
			for (int j = 0; j < read_length; ++j) {
				if (restored_sequence[i + j] == '-') {
					restored_sequence[i + j] = reads[match_idx][j]; // ������ ���������� �ش� ��ġ�� �̹� ������ �κ��� �ƴ� ��쿡�� ����
				}
			}
		}
	}

	return restored_sequence; // ������ �������� ��ȯ
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
	// �迭(unordered map) �ʱ�ȭ
	initialize_prefix_suffix_map(reads);
	// ���� ������ ����
	string restored_sequence = restore_sequence(reference_genome, reads);
	auto end_time = high_resolution_clock::now();

	cout << "Enhanced_bruteforce:\n";
	// �ð� ���
	double elapsed_time = duration<double, milli>(end_time - start_time).count();
	cout << "Execution Time: " << elapsed_time / 1000.0 << " seconds\n";
	// ��Ȯ�� ���
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