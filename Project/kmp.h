#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

void computeLPSArray(const std::string& pattern, int M, std::vector<int>& lps);
int findOverlap(const std::string& text, const std::string& pattern, int max_length, const std::vector<int>& lps);
void kmpMerge(int pattern_length);
void execute_KMP(int pattern_length);

#endif