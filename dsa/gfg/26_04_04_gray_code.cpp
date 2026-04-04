/*
Given a number n, generate bit patterns from 0 to 2n-1 such that successive patterns differ by one bit. 
A Gray code sequence must begin with 0.

Examples:
    Input: n = 2
    Output: ["00", "01", "11", "10"]
    Explanation: 
        00 and 01 differ by one bit.
        01 and 11 differ by one bit.
        11 and 10 also differ by one bit.

    Input: n = 3
    Output: ["000", "001", "011", "010", "110", "111", "101", "100"]
    Explanation:
        000 and 001 differ by one bit.
        001 and 011 differ by one bit.
        011 and 010 differ by one bit.
        Similarly, every successive pattern differs by one bit.

Constraints :
1 ≤ n ≤ 16

Time Complexity: O(2^n)
Auxiliary Space: O(2^n)
*/

class Solution {
    string getBinaryString(int num, int n) {
        string binary(n, '0');
        for(int i = 0; i < n; ++i) {
            binary[n-1-i] = num >> i & 1 ? '1' : '0';
        }
        return binary;
    }
  public:
    vector<string> graycode(int n) {
        vector<string> greyCodes(pow(2, n));
        for(int i = 0; i < pow(2, n); ++i) {
            greyCodes[i] = getBinaryString(i ^ (i >> 1), n);
        }
        return greyCodes;
    }
};
