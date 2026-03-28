/*
Advance Trie supports following functions
    - Insert
    - CountWordsEqualTo
    - CountPrefixEqualTo/CountWordsStartingWith
    - Erase
*/

#include <iostream>
using namespace std;

struct Node {
    Node* links[26] = {nullptr};
    int endWordCount = 0;
    int startsWithWordCount = 0;

    bool hasCharater(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch) {
        links[ch - 'a'] = new Node();
    }

    void increamentPrefixCount() {
        startsWithWordCount++;
    }

    void decrementPrefixCount() {
        startsWithWordCount--;
    }

    void increamentWordCount() {
        endWordCount++;
    }

    void decrementWordCount() {
        endWordCount--;
    }
};

class Trie {
private:
    Node *root;
public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->hasCharater(ch)) {
                node->put(ch);
            }
            node = node->get(ch);
            node->increamentPrefixCount();
        }
        node->increamentWordCount();
    }

    int countWordsEqualTo(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->hasCharater(ch)) {
                return 0;
            }
            node = node->get(ch);
        }
        return node->endWordCount;
    }

    int countPrefixEqualTo(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->hasCharater(ch)) {
                return 0;
            }
            node = node->get(ch);
        }
        return node->startsWithWordCount;
    }

    void erase(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->hasCharater(ch)) {
                return;
            }
            node = node->get(ch);
            node->decrementPrefixCount();
        }
        node->decrementWordCount();
    }
};

enum Operation { INSERT, COUNT_WORDS_EQUAL_TO, COUNT_WORDS_STARTING_WITH, ERASE };

int main() {
    vector<pair<Operation, string>> operations = {
        {INSERT, "apple"},
        {INSERT, "apple"},
        {INSERT, "ball"},
        {COUNT_WORDS_STARTING_WITH, "a"},
        {COUNT_WORDS_EQUAL_TO, "apple"},
        {COUNT_WORDS_STARTING_WITH, "app"},
        {ERASE, "apple"},
        {COUNT_WORDS_EQUAL_TO, "apple"},
        {COUNT_WORDS_STARTING_WITH, "app"},
        {ERASE, "apple"},
        {COUNT_WORDS_STARTING_WITH, "app"}
    };

    Trie trie = Trie();
    for(auto op: operations) {
        switch(op.first) {
            case INSERT:
                trie.insert(op.second);
                cout << "OK" << endl;
                break;
            case COUNT_WORDS_EQUAL_TO:
                cout << trie.countWordsEqualTo(op.second) << endl;
                break;
            case COUNT_WORDS_STARTING_WITH:
                cout << trie.countPrefixEqualTo(op.second) << endl;
                break;
            case ERASE:
                trie.erase(op.second);
                cout << "OK" << endl;
                break;
            default:
                cout << "INVALID OPERATION" << endl;
        }
    }
    return 0;
}