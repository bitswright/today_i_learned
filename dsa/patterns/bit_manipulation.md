# Bit Manipulation

## Important concepts
- **One's Complement**: Fliping all bits.
- **Two's Complement**: One's Complement + 1

## Problems
- Check if `k`th bit is set
    ```cpp
    bool checkKthBit(int n, int k) {
        return n >> k & 1;
    }
    ```
    ```cpp
    bool checkKthBit(int n, int k) {
        return (1 << k & n) != 0;
    }
    ```
- Check if a number is even/odd or not.
    ```cpp
    bool isEven(int n) {
        return (n & 1) == 0;
    }
    ```
- Check if a number is power of two
    ```cpp
    bool isPowerofTwo(int n) {
        if(n == 0) {
            return false;
        }
        while((n & 1) == 0) {
            n >>= 1;
        }
        return (n >> 1) == 0;
    }
    ```
    ```cpp
    bool isPowerofTwo(int n) {
        return (n != 0 && ((n & (n-1)) == 0));
    }
    ```
- Count set bits in a number
    - Brute Force
        ```cpp
        int countSetBits(int n) {
            int count = 0;
            while(n) {
                if(n & 1)
                    count++;
                n >>= 1;
            }
            return count;
        }
        ```
    - Brian Kernighan’s Algorithm
        ```cpp
        int countSetBits(int n) {
            int count = 0;
            while(n) {
                n &= (n-1);
                count++;
            }
            return count;
        }
        ```
    - Built-in
        ```cpp
        int countSetBits(int n) {
            return __buitin_popcount(n);
        }
        ```
- Count set bits in numbers from 1 to n

- Set rightmost unset bit
    ```cpp
    int setBit(int n) {
        return n | (n+1);
    }
    ```
- Unset rightmost set bit
    ```cpp
    int unsetBit(int n) {
        return n & (n-1);
    }
    ```
- Swapping two numbers without third number:
    ```cpp
    void swap(int &a, int &b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }   
    ``` 
- [Minimum Bit Flips to Convert Number](/dsa/problems/bit_manipulation/lc_2220.md)
