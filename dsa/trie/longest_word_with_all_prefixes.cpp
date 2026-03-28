/*
Find the longest string

    Given an array of strings words[]. Find the longest string in words[] such that every prefix of it is also present in the array words[]. 
    Note: If multiple strings have the same maximum length, return the lexicographically smallest one.

    Examples:

        Input: words[] = ["p", "pr", "pro", "probl", "problem", "pros", "process", "processor"]
        Output: pros
        Explanation: "pros" is the longest word with all prefixes ("p", "pr", "pro", "pros") present in the array words[].

        Input: words[] = ["ab", "a", "abc", "abd"]
        Output: abc
        Explanation: Both "abc" and "abd" has all the prefixes in words[]. Since, "abc" is lexicographically smaller than "abd", so the output is "abc".

    Constraints:
        1 ≤ words.length() ≤ 10^3
        1 ≤ words[i].length ≤ 10^3

    Expected Time Complexity: O(n * max(words[i].size()))
    Expected Auxiliary Space: O(n * max(words[i].size()))
*/


struct Node {
    Node* links[26] = {nullptr};
    bool endCharacter = false;
    
    bool hasCharacter(char ch) {
        return links[ch - 'a'] != nullptr;
    } 
    
    void put(char ch) {
        links[ch - 'a'] = new Node();
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
};

class Trie {
  private:
    Node *root;  
    
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
            if(!node->hasCharacter(ch)) {
                node->put(ch);
            }
            node = node->get(ch);
        }
        node->setEnd();
    }
    
    bool areAllPrefixPresent(string word) {
        Node *node = root;
        for(char ch: word) {
            if(!node->hasCharacter(ch)) {
                return false;
            }
            node = node->get(ch);
            if(!node->isEnd()) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
  public:
    string longestString(vector<string> &words) {
        Trie trie = Trie();
        for(string word: words) {
            trie.insert(word);
        }
        
        sort(words.begin(), words.end());
        string longestStr = "";
        for(string word: words) {
            if(word.length() > longestStr.length() && trie.areAllPrefixPresent(word)) {
                longestStr = word;
            }
        }
        
        return longestStr;
    }
};