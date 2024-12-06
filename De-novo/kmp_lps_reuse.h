#ifndef KMP_LPS_REUSE_H
#define KMP_LPS_REUSE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

void r_computeLPSArray(const std::string& pattern, int M, std::vector<int>& lps);
int r_findOverlap(const std::string& text, const std::string& pattern, int max_length, const std::vector<int>& lps);
void r_kmpMerge(int pattern_length);
void r_execute_KMP(int pattern_length);

#endif