#include "aho_corasick.h"
 
AhoCorasick::AhoCorasick() {
	trie.push_back(Node()); // Root node
}

void AhoCorasick::build_trie(const vector<string>& patterns) {
	this->patterns = patterns;
	for (size_t i = 0; i < patterns.size(); i++) {
		int current = 0; // Start from root
		for (char c : patterns[i]) {
			if (trie[current].children.find(c) == trie[current].children.end()) {
				trie[current].children[c] = trie.size();
				trie.push_back(Node());
			}
			current = trie[current].children[c];
		}
		trie[current].output_link = i; // Mark the end of a pattern
	}
}

void AhoCorasick::build_failure_links() {
	queue<int> q;

	// Initialize fail links for direct children of root
	for (const auto& entry : trie[0].children) { // `entry`´Â key-value ½Ö
		char c = entry.first;
		int child = entry.second;

		trie[child].fail_link = 0;
		q.push(child);
	}

	// Process the rest of the trie
	while (!q.empty()) {
		int current = q.front();
		q.pop();

		for (const auto& entry : trie[current].children) {
			char c = entry.first;
			int child = entry.second;

			int fail = trie[current].fail_link;

			while (fail != 0 && trie[fail].children.find(c) == trie[fail].children.end()) {
				fail = trie[fail].fail_link;
			}

			if (trie[fail].children.find(c) != trie[fail].children.end()) {
				fail = trie[fail].children[c];
			}

			trie[child].fail_link = fail;

			if (trie[fail].output_link != -1) {
				trie[child].output_link = trie[fail].output_link;
			}

			q.push(child);
		}
	}
}

vector<int> AhoCorasick::search(const string& text, const string& pattern) {
	vector<int> match_positions;
	int current = 0;

	for (size_t i = 0; i < text.size(); i++) {
		char c = text[i];

		while (current != 0 && trie[current].children.find(c) == trie[current].children.end()) {
			current = trie[current].fail_link;
		}

		if (trie[current].children.find(c) != trie[current].children.end()) {
			current = trie[current].children[c];
		}

		if (trie[current].output_link != -1) {
			match_positions.push_back(i - pattern.size() + 1);
		}
	}

	return match_positions;
}

int execute_aho_corasick(const string& reference, const string& read) {
	AhoCorasick ac;
	ac.build_trie({ read });
	ac.build_failure_links();
	auto matches = ac.search(reference, read);

	return matches.empty() ? -1 : matches[0];
}
