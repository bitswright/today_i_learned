/* 
# Trie
- Named from the work reTRIEval.
- Aka **prefix tree**.
- A tree structed data-structure for effieciently store and retrieve strings or ordered sequences.

TC: 
    - Insertion: O(N) 
    - Search: O(N)
    - Prefix Search: O(N)
    (where N is length of word)
SC: O(N) where N is total number of characters across all unique words
*/

#include<iostream>
#include<vector>
using namespace std;

struct Node {
    Node *links[26] = {nullptr};
    bool endCharacter = false;

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node *node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        endCharacter = true;
    }

    bool isEnd() {
        return endCharacter;
    }

    ~Node() {
        for(int i = 0; i < 26; ++i) {
            if(links[i] != nullptr) {
                delete links[i];
                links[i] = nullptr;
            }
        }
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        delete root;
    }

    void insert(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->setEnd();
    }

    bool search(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return node->isEnd();
    }

    bool startsWith(string prefix) {
        Node *node = root;
        for(char ch: prefix) {
            if(!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return true;
    }
};

enum Operation { INSERT, SEARCH, STARTS_WITH };

int main() {
    Trie *trie = new Trie();
    vector<pair<Operation, string>> operations = {
        {INSERT, "apple"}, 
        {SEARCH, "apple"},
        {SEARCH, "app"},
        {STARTS_WITH, "app"},
        {INSERT, "app"},
        {SEARCH, "app"}
    };
    for(auto op: operations) {
        switch (op.first) {
        case INSERT:
            trie->insert(op.second);
            cout << "OK" << endl;
            break;
        case SEARCH:
            cout << (trie->search(op.second) ? "FOUND" : "NOT_FOUND") << endl;
            break;
        case STARTS_WITH:
            cout << (trie->startsWith(op.second) ? "STARTS" : "DOES_NOT_START") << endl;
            break;
        default:
            cout << "ERROR" << endl;
            break;
        }
    }
    return 0;
}
