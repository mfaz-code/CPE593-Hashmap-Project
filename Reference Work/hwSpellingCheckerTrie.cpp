/* Applied Data Structures and Algorithms
 * Author - Parveen 
 * Cite - stackoverflow on how to read a file */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Trie {
private:
	class Node {
	public:
		Node* next[26];
		bool isComplete;
		Node() {
			for(int i=0; i < 26; i++)
                                next[i] = nullptr;
                        isComplete = false;
		}
	};
	Node* root;
public:
	Trie() { 
		root = new Node;
	}
	// loading the trie from the dictionary file
	void load(string dictionary) {
		ifstream dfile(dictionary);
		string word;
		int i=0;
		while(dfile >> word) {
			insert(word);
			i++;
		}
		cout << i << '\n';
	}
	
	void insert(string word) {
		Node* p = root;
		for(char c: word) {
			if(p->next[c - 'a'] == nullptr)
				p->next[c - 'a'] = new Node;
			p = p->next[c - 'a'];
		}
		p->isComplete = true;
	}

	bool is_word(string word) {
		Node* p = root;
		for(char c: word) {
			if(p->next[c - 'a'] == nullptr)
				return false;
			p = p->next[c - 'a'];
		}
		return p->isComplete;
	}

	bool is_prefix(string word) {
		Node* p = root;
		for(char c: word) {
			if(p->next[c - 'a'] == nullptr)
				return false;
			p = p->next[c - 'a'];	
		}
		return true;
	}
};

int main() {
	Trie objtrie;
	objtrie.load("dict.txt");

	objtrie.insert("apple");

	ifstream wfile("words.txt");
	string word;
	while(wfile >> word) {
		objtrie.is_word(word) ? 
			cout << word << " is present in the dictionary\n" : 
			cout << word << " is not present in the dictionary\n";
	}
	//for(string word : wfile) {
	//	objtrie.insert(word);}
	
	
	/*string word = "buttons";
	objtrie.is_word(word) ? cout << word <<  " is present in the dictionary\n" : cout << word << " is not present in the dictionary\n";
	*/

	wfile.close();
	
	return 0;
}
