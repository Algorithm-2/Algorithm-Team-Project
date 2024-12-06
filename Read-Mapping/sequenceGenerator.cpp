#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

char dna[4] = { 'A', 'C', 'T', 'G' };

void create_dna(const int N) {
	// 0~3 사이의 난수 생성
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 3);

	ofstream file(DNA_SEQUENCE);

	for (int i = 0; i < N; i++) {
		file << dna[dis(gen)];
	}
	file.close();
}

void create_read(const int L, const int P) {
	ifstream dnafile(DNA_SEQUENCE);
	ofstream readfile(READS);
	string read;
	string sequence;
	vector<string> v;

	getline(dnafile, sequence); // Read the DNA sequence

	while (sequence.length()) {
		if (sequence.length() <= L) { // If the remaining sequence is shorter than L
			read = sequence.substr(0);
			v.push_back(read);
			break;
		}
		else {
			read = sequence.substr(0, L); // Take a substring of length L
			v.push_back(read);
			sequence.erase(0, L - P); // Overlap by P characters
		}
	}

	// Shuffle the reads
	random_device rd;
	default_random_engine rng(rd());
	shuffle(v.begin(), v.end(), rng);

	// Write the reads to the output file
	for (const auto& r : v) {
		readfile << r << "\n";
	}

	dnafile.close();
	readfile.close();
}

void create_seqeunce(const int N, const int L, const int P) {
	create_dna(N);  // Generate the DNA sequence
	create_read(L, P); // Generate the reads from the DNA sequence
}