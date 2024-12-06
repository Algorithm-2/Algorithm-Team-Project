#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include "bruteforce.h"       // Bruteforce 알고리즘 관련 헤더
#include "kmp.h"              // KMP 알고리즘 관련 헤더
#include "rabinKarp.h"       // Rabin-Karp 알고리즘 관련 헤더
#include "aho_corasick.h"     // Aho-Corasick 알고리즘 관련 헤더 (주석 처리)
#include "boyer_moore.h"      // Boyer-Moore 알고리즘 관련 헤더 (주석 처리)
#include "utils.h"            // 유틸리티 함수들 (시퀀스 로드, 정확도 계산 등)
#include "sequenceGenerator.h"
#include "enhanced_bruteforce.h"
#define N_GRID_SIZE 1
#define L_GRID_SIZE 5 
#define P_GRID_SIZE L_GRID_SIZE

int main() {
	int N_grid[N_GRID_SIZE] = { 1000 };
	int L_grid[L_GRID_SIZE] = { 3, 5, 7, 9, 10 };
	int P_grid[P_GRID_SIZE] = { 1, 2, 3, 3, 3 };

	// 결과 출력 파일
	const string output_filepath = "result_temp.txt";
	
	// N_grid와 L_grid의 모든 값을 사용하여 반복
	for (int n_idx = 0; n_idx < N_GRID_SIZE; ++n_idx) {
		const int N_value = N_grid[n_idx];
		create_dna(N_value);

		for (int l_idx = 0; l_idx < L_GRID_SIZE; ++l_idx) {

			int L_value = L_grid[l_idx];
			int P_value = P_grid[l_idx];

			create_read(L_value, P_value);
			ofstream file_output(output_filepath, ios::app);

			// reference_genome 로딩
			string reference_genome;
			if (!load_sequences("sequence.txt", reference_genome)) {
				return 1;
			}
			
			// reads 로딩
			vector<string> reads;
			if (!load_reads("reads.txt", reads)) {
				return 1;
			}

			// 현재 실험 파라미터 출력
			cout << "\n\nParameters N=" << N_value << ", L=" << L_value << ", P=" << P_value << endl;
			file_output << "Parameters N=" << N_value << ", L=" << L_value << ", P=" << P_value << endl;

			cout << "Number of Reads : " << reads.size() << "\n";
			file_output << "Number of Reads : " << reads.size() << "\n";

			// 실험 수행
			run_and_measure(reads, reference_genome, "Bruteforce", execute_bruteforce, output_filepath);
			run_and_measure(reads, reference_genome, "KMP", execute_KMP, output_filepath);
			run_and_measure(reads, reference_genome, "Rabin-Karp", execute_rabinkarp, output_filepath);
			
			// 구현상 문제로 주석처리
			//run_and_measure(reads, reference_genome, "Aho_corasick", execute_aho_corasick, output_filepath);
			//run_and_measure(reads, reference_genome, "Boyer_moore", execute_boyer_moore, output_filepath);

			// 팀에서 개발한 개선된 브루트포스의 실행 및 결과
			execute_enhanced_bruteforce(reads, reference_genome, output_filepath);
			
		}
	}

	return 0;
}
