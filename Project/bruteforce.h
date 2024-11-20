#ifndef READS_ASSEMBLER_H
#define READS_ASSEMBLER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

bool bruteforce_forward(int curlen, vector<string>(&reads)[4]);
bool bruteforce_backward(int curlen, vector<string>& reads_A, vector<string>& reads_C, vector<string>& reads_T, vector<string>& reads_G);
void createReadArray();
void execute_Bruteforce();

#endif
