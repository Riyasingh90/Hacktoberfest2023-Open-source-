#include <iostream>
#include <unordered_map>

using namespace std;

// Define a TrieNode class
class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // Map to store child nodes
    bool is_end_of_word; // Indicates if a word ends at this node

    TrieNode() {
        is_end_of_word = false;
    }
};

// Define the Trie class
class Trie {
private:
    TrieNode* root; // The root node of the Trie

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                // If the character doesn't exist in the children, create a new node
                node->children[c] = new TrieNode();
            }
            node = node->children[c]; // Move to the child node
        }
        node->is_end_of_word = true; // Mark the end of the word
    }

    // Search for a word in the Trie
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                // If the character doesn't exist in the children, the word is not in the Trie
                return false;
            }
            node = node->children[c]; // Move to the child node
        }
        return node->is_end_of_word; // Check if the last node marks the end of a word
    }

    // Check if the Trie contains a word with the given prefix
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                // If the character doesn't exist in the children, the prefix is not in the Trie
                return false;
            }
            node = node->children[c]; // Move to the child node
        }
        return true; // The prefix is found in the Trie
    }
};

int main() {
    Trie trie;

    // Insert words into the Trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    // Search for words in the Trie
    cout << trie.search("apple") << endl;  // Output: 1 (true)
    cout << trie.search("app") << endl;    // Output: 1 (true)
    cout << trie.search("banana") << endl; // Output: 1 (true)
    cout << trie.search("ban") << endl;    // Output: 0 (false)

    // Check if the Trie contains words with given prefixes
    cout << trie.startsWith("app") << endl; // Output: 1 (true)

    return 0;
}
