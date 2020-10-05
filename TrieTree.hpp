#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
#include "stack"
#include "algorithm"

using namespace std;
struct Trie
{
    // true when node is a leaf node
    bool isLeaf;
    vector<int> files{0,0,0,0,0};
    string code_word;
    int level;
    int score;

    // each node stores a map to its child nodes
    unordered_map<char, Trie*> map;
    Trie* parent;

};

bool isSubsting(const string &new_word, const vector<Trie> &vector_tries);
static void DestroyRecursive(Trie* node);
static int returnScore(const vector<int>& files, int level);
Trie* getNewTrieNode();
void insert(Trie*& head, char* str, const int& file_number);
bool haveChildren(Trie const* curr);
bool deletion(Trie*& curr, char* str);
vector<Trie> traverseTree(const Trie &node);
vector<Trie> getTopString();
