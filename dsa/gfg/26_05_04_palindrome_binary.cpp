/*
Check if the binary representation of a number is palindrome or not.
 
Example 1:
    Input       : N = 17
    Output      : 1
    Explanation : (17)_10 = (10001)_2, Which is pallindrome hence output is 1.

Example 2:
    Input       : N = 16
    Output      : 0
    Explanation : (16)_10 = (10000)_2, Which is not pallindrome hence output is 0.

Expected Complexities:
    Time Complexity: O(log N)
    Space Complexity: O(logN)

Constraints:
    1 <= N <= 10^18
*/

int isPallindrome(long long int N) {
    long long int opN = 0, temp = N;
    while(temp > 0) {
        opN = (opN << 1 ) | (temp & 1);
        temp >>= 1;
    }
    return N == opN;
}