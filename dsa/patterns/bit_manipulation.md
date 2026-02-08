# Bit Manipulation

## Important concepts
- **One's Complement**: Fliping all bits.
- **Two's Complement**: One's Complement + 1

## Tricks
- **Swapping two numbers without third numbera**:

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