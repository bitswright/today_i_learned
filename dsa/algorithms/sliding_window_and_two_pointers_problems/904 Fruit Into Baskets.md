# [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/description/)

Given an array `fruits[]`. Pick at most 2 types of fruits, but pick them from a contiguous subarray. Return the maximum number of fruits that can be collected.

- This problem is translation of *Longest subarray with at most 2 distinct elements*.

## Solutions:
### Brute Force: 
- Idea:
    - Generate all subarrays of the given `fruits` array. $O(n^2)$
    - Check if the subarrays follows the rules. $O(n)$
    - Keep track of longest subarray.
- TC: $O(n^3)$
- SC: $O(1)$
### Brute Force with Early Stop
- Idea:
    - Fix `l` and keeping expanding `r` till distinct type of fruits does not exceed 2. $O(n^2)$
    - Keep track of longest subarray.
- TC: $O(n^2)$
- SC: $O(1)$
- Code:
    ```cpp
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxFruits = -1;
        for(int l = 0; l < n; ++l) {
            int fruit1 = -1, fruit2 = -1;
            for(int r = l; r < n; ++r) {
                if(fruit1 == -1) {
                    fruit1 = fruits[r];
                } else if(fruits[r] != fruit1 && fruit2 == -1) {
                    fruit2 = fruits[r];
                } else if(fruits[r] != fruit1 && fruits[r] != fruit2) {
                    break;
                }
                maxFruits = max(maxFruits, r - l + 1);
            }
        }
        return maxFruits;
    }
    ```
### Sliding Window with HashMap
- Idea
    - Instead of fixing `l`, keeping expanding `r` till distinct type of fruits does not exceed 2, but once it exceeds 2, keep moving the `l` to the right till distinct fruit doesn't again equal to 2. $O(n)$
    - Keep track of longest subarray.
- TC: $O(n)$
- SC: $O(1)$
- Code:
    ```cpp
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxFruits = -1;
        int l = 0, r = 0;
        map<int, int> fruitCount;
        while(r < n) {
            if(fruitCount.find(fruits[r]) == fruitCount.end()) {
                if(fruitCount.size() < 2) {
                    fruitCount[fruits[r]] = 1;
                    r++;
                } else {
                    while(fruitCount.size() == 2) {
                        fruitCount[fruits[l]]--;
                        if(fruitCount[fruits[l]] == 0) {
                            fruitCount.erase(fruits[l]);
                        }   
                        l++;
                    }
                }
            } else {
                fruitCount[fruits[r]]++;
                r++;
            }
            maxFruits = max(maxFruits, r - l);

        }
        return maxFruits;
    }
    ```
### Using Last Occurrence Trick
- Idea
    - Instead of sliding window from left one by one, we can slide the window directly to the desired position by keeping the length of streak of last fruit occurance.
- TC: $O(n)$
- SC: $O(1)$ 
- Code:
    ```cpp
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxFruits = -1;
        int l = 0, r = 0;
        int lastFruit = -1, otherFruit = -1;
        int streak = 0;
        for(;r < n; ++r) {
            if(lastFruit == -1) {
                lastFruit = fruits[r];
                streak = 1;
            } else if(lastFruit == fruits[r]) {
                streak++;
            } else if(otherFruit == -1 || otherFruit == fruits[r]) {
                otherFruit = lastFruit;
                lastFruit = fruits[r];
                streak = 1;
            } else {
                // fruits[r] != lastFruit andalso fruits[r] != otherFruit
                // jump l to r - streak position
                l = r - streak;
                otherFruit = lastFruit;
                lastFruit = fruits[r];
                streak = 1;
            }
            maxFruits = max(maxFruits, r - l + 1);
        }
        return maxFruits;
    }
    ```