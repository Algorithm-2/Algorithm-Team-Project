#ifndef READS_ASSEMBLER_H
#define READS_ASSEMBLER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

bool d_bruteforce_forward(int curlen, vector<string> reads);
bool d_bruteforce_backward(int curlen, vector<string> reads);
void d_createReadArray();
void execute_Bruteforce(int P);

#endif
