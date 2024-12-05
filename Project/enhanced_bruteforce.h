#ifndef E_BRUTEFORCE_H
#define E_BRUTEFORCE_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>


extern std::string result;
extern std::vector<std::string> reads_A[4];
extern std::vector<std::string> reads_C[4];
extern std::vector<std::string> reads_T[4];
extern std::vector<std::string> reads_G[4];
bool bruteforce_forward(int curlen, std::vector<std::string>(&reads)[4]);
bool bruteforce_backward(int curlen, std::vector<std::string>& reads_A, std::vector<std::string>& reads_C,
    std::vector<std::string>& reads_T, std::vector<std::string>& reads_G);
void createReadArray();
void execute_Bruteforce(int P);

#endif
