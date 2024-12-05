#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

extern std::string d_result;
extern std::vector<std::string> reads_all;
bool d_bruteforce_forward(int curlen, std::vector<std::string> reads);
bool d_bruteforce_backward(int curlen, std::vector<std::string> reads);
void d_createReadArray();
void d_execute_Bruteforce(int P);

#endif
