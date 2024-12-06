#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	bool isWord;
	TrieNode() : isWord(false) {}
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	void insert(string word) {
		TrieNode* curr = root;
		for (auto c : word) {
			auto it = curr->children.find(c);
			if (it == curr->children.end()) {
				curr->children[c] = new TrieNode();
				curr = curr->children[c];
			} else {
				curr = it->second;
			}
		}
		curr->isWord = true;
	}

	bool search(string word) {
		TrieNode* curr = root;
		for (auto c : word) {
			auto it = curr->children.find(c);
			if (it == curr->children.end()) {
				return false;
			} else {
				curr = it->second;
			}
		}
		return curr->isWord;
	}

	bool startWith(string prefix) {
		TrieNode* curr = root;
		for (auto c : prefix) {
			auto it = curr->children.find(c);
			if (it == curr->children.end()) {
				return false;
			} else {
				curr = it->second;
			}
		}
		return true;
	}

private:
	TrieNode* root;
};