#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

// int N, L, P; // sequence 길이 / read 길이 / read간 겹치는 길이
void create_dna(int N) {
    char dna[4] = { 'A', 'C', 'T', 'G' };
    // 0~3 사이의 난수 생성
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3);

    ofstream file(DNA_SEQUENCE);
    for (int i = 0; i < N; i++) file << dna[dis(gen)];
    file.close();
}

void create_read(int L, int P) {
    ifstream dnafile(DNA_SEQUENCE);
    ofstream readfile(READS);
    string read;
    string sequence;
    vector<string> v;

    random_device rd;
    default_random_engine rng(rd());

    getline(dnafile, sequence);
    while (sequence.length()) {
        if (sequence.length() <= L) {
            read = sequence.substr(0);
            v.push_back(read);
            break;
        }
        else {
            read = sequence.substr(0, L);
            v.push_back(read);
            sequence.erase(0, L - P);
        }
    }
    shuffle(v.begin(), v.end(), rng);
    for (int i = 0; i < v.size(); i++) readfile << v[i] << "\n";
    dnafile.close();
    readfile.close();
}

void create_data(int N, int L, int P) {
    create_dna(N); 
    create_read(L, P); 
}