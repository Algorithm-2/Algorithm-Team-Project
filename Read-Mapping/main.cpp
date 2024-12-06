#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include "bruteforce.h"       // Bruteforce �˰��� ���� ���
#include "kmp.h"              // KMP �˰��� ���� ���
#include "rabinKarp.h"       // Rabin-Karp �˰��� ���� ���
#include "aho_corasick.h"     // Aho-Corasick �˰��� ���� ��� (�ּ� ó��)
#include "boyer_moore.h"      // Boyer-Moore �˰��� ���� ��� (�ּ� ó��)
#include "utils.h"            // ��ƿ��Ƽ �Լ��� (������ �ε�, ��Ȯ�� ��� ��)
#include "sequenceGenerator.h"
#include "enhanced_bruteforce.h"
#define N_GRID_SIZE 1
#define L_GRID_SIZE 5 
#define P_GRID_SIZE L_GRID_SIZE

int main() {
	int N_grid[N_GRID_SIZE] = { 1000 };
	int L_grid[L_GRID_SIZE] = { 3, 5, 7, 9, 10 };
	int P_grid[P_GRID_SIZE] = { 1, 2, 3, 3, 3 };

	// ��� ��� ����
	const string output_filepath = "result_temp.txt";
	
	// N_grid�� L_grid�� ��� ���� ����Ͽ� �ݺ�
	for (int n_idx = 0; n_idx < N_GRID_SIZE; ++n_idx) {
		const int N_value = N_grid[n_idx];
		create_dna(N_value);

		for (int l_idx = 0; l_idx < L_GRID_SIZE; ++l_idx) {

			int L_value = L_grid[l_idx];
			int P_value = P_grid[l_idx];

			create_read(L_value, P_value);
			ofstream file_output(output_filepath, ios::app);

			// reference_genome �ε�
			string reference_genome;
			if (!load_sequences("sequence.txt", reference_genome)) {
				return 1;
			}
			
			// reads �ε�
			vector<string> reads;
			if (!load_reads("reads.txt", reads)) {
				return 1;
			}

			// ���� ���� �Ķ���� ���
			cout << "Parameters N=" << N_value << ", L=" << L_value << ", P=" << P_value << endl;
			file_output << "Parameters N=" << N_value << ", L=" << L_value << ", P=" << P_value << endl;

			cout << "Number of Reads : " << reads.size() << "\n";
			file_output << "Number of Reads : " << reads.size() << "\n";

			// ���� ����
			run_and_measure(reads, reference_genome, "Bruteforce", execute_bruteforce, output_filepath);
			run_and_measure(reads, reference_genome, "KMP", execute_KMP, output_filepath);
			run_and_measure(reads, reference_genome, "Rabin-Karp", execute_rabinkarp, output_filepath);
			
			// ������ ������ �ּ�ó��
			//run_and_measure(reads, reference_genome, "Aho_corasick", execute_aho_corasick, output_filepath);
			//run_and_measure(reads, reference_genome, "Boyer_moore", execute_boyer_moore, output_filepath);

			// ������ ������ ������ ���Ʈ������ ���� �� ���
			execute_enhanced_bruteforce(reads, reference_genome, output_filepath);
			
		}
	}

	return 0;
}