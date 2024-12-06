#ifndef ENHANCED_BRUTEFORCE_H
#define ENHANCED_BRUTEFORCE_H

#include <vector>
#include <string>
#include <unordered_map>

void initialize_prefix_suffix_map(const std::vector<std::string>& reads);
int find_read_in_group(const std::string& reference, const std::string& window, const std::vector<std::string>& reads);
std::string restore_sequence(const std::string& reference, const std::vector<std::string>& reads);
void print_prefix_suffix_map(const std::unordered_map<std::string, std::vector<int>>& map);
void execute_enhanced_bruteforce(const vector<string>& reads, const string& reference_genome, const string& output_filepath);

#endif 
 