#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <string> 
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class AhoCorasick {
public:
	AhoCorasick();
	void build_trie(const vector<string>& patterns);
	void build_failure_links();
	vector<int> search(const string& text, const string& pattern);

private:
	struct Node {
		unordered_map<char, int> children;
		int fail_link = 0;
		int output_link = -1; // Index of pattern matched at this node
	};

	vector<Node> trie;
	vector<string> patterns;
};

int execute_aho_corasick(const string& reference, const string& read);

#endif
