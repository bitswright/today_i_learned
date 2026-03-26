# Sorting Techniques - The Unforgettable Guide

### Selection Sort
- **Find the Minimum** Strategy
- Algorithm:
    ```
    For each index 0 to n-1:
        1. Find the minimum element
        2. Replace with current element
    ```
- Code:
    ```cpp
    void sortArray(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n-1; ++i) {
            int minIdx = i;
            for(int j = i+1; j < n; ++j) {
                if(nums[j] < nums[minIdx])
                    minIdx = j;
            }
            if(minIdx != i)
            swap(nums[i], nums[minIdx]);
        }
    }
    ```
- TC: $O(n^2)$ always
- SC: $O(1)$

### Bubble Sort 
- **Bubbling Up** Strategy
- Algorithm:
    ```
    Repeat until no swaps needed:
        For each adjacent pair:
            if arr[j] > arr[j+1] then swap
    ```
- Code:
    - Iterative:
        ```cpp
        void sortArray(vector<int>& nums) {
            int n = nums.size();
            for(int i = n-1; i >= 0; --i) {
                bool swapped = false;
                for(int j = 0; j < i; ++j) {
                    if(nums[j] > nums[j+1]) {
                        swap(nums[j], nums[j+1]);
                        swapped = true;
                    }
                }
                if(!swapped)
                    break;
            }
        }
        ```
    - Recursive
        ```cpp
        void sortArray(vector<int>& nums, int n) {
            if(n == 0)
                return;
            bool swapped = false;
            for(int j = 0; j < n; ++j) {
                if(nums[j] > nums[j+1]) {
                    swap(nums[j], nums[j+1]);
                    swapped = true;
                }
            }
            if(swapped)
                sortArray(nums, n-1);
        }
        vector<int> sortArray(vector<int>& nums) {
            int n = nums.size();
            sortArray(nums, n-1);
            return nums;
        }
        ```
- TC: $O(n^2)$ worst, $O(n)$ best(already sorted)
- SC: $O(1)$

### Insertion Sort
- **Card Player** strategy
- Algorithm:
    ```
    For each element:
        Shift all selected larger elements to the right
        Insert the current element in its correct position
    ```
- Code:
    - Iterative:
        ```cpp
        void sortArray(vector<int>& nums) {
            int n = nums.size();
            for(int i = 1; i < n; ++i) {
                int key = nums[i];
                int j = i - 1;
                for(;j >= 0 && nums[j] > key; --j) {
                    nums[j+1] = nums[j];
                }
                nums[j+1] = key;
            }
        }
        ```
    - Recursive:
        ```cpp
        void sortArray(vector<int>& nums, int n) {
            if(n == 0)
                return;
            sortArray(nums, n-1);
            int key = nums[n];
            int j = n-1;
            while(j >= 0 && nums[j] > key) {
                nums[j+1] = nums[j];
                j--;
            }
            nums[j+1] = key;
        }
        vector<int> sortArray(vector<int>& nums) {
            int n = nums.size();
            sortArray(nums, n-1);
            return nums;
        }
        ```
- TC: $O(n^2)$ (worst), $O(n)$ (best, already sorted)
- SC: $O(1)$

### Merge Sort
- **Divide and Conquer** strategy
- Algorithm:
    ```
    Divide: Split array into halves
    Conquer: Recursively sort each half
    Merge: Combine two sorted halves into one sorted array
    ```
- Code:
    ```cpp
    void sortArray(vector<int>& nums, int s, int e) {
        if(s >= e)
            return;
        int m = (s + e) >> 1;
        sortArray(nums, s, m);
        sortArray(nums, m+1, e);
        merge(nums, s, m, e);
    }

    void merge(vector<int>& nums, int s, int m, int e) {
        int i = s, j = m + 1;
        vector<int> temp = vector<int>(e - s + 1);
        int k = 0;
        while(i <= m && j <= e) {
            if(nums[i] <= nums[j]) {
                temp[k] = nums[i];
                i++;
            } else {
                temp[k] = nums[j];
                j++;
            }
            k++;
        }
        while(i <= m) {
            temp[k] = nums[i];
            i++;
            k++;
        }
        while(j <= e) {
            temp[k] = nums[j];
            j++;
            k++;
        }
        for(int i = s; i <= e; ++i) 
            nums[i] = temp[i-s];
    }
    
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        sortArray(nums, 0, n-1);
        return nums;
    }
    ```
- TC: $O(nlogn)$ (always)
- SC: $O(n)$

### Quick Sort
- **Pivot Partitioning** strategy
- Algorithm:
    ```
    Pick a pivot element
    Move smaller elements to the left and larger to the right
    Recursively sort left and right partitions
    ```
- Code:
    ```cpp
    void sortArray(vector<int>& nums, int s, int e) {
        if(s >= e)
            return;
        int pivot = partition(nums, s, e);
        sortArray(nums, s, pivot-1);
        sortArray(nums, pivot+1, e);
    }

    int partition(vector<int>& nums, int s, int e) {
        int i = s;
        for(int j = s; j < e; ++j) {
            if(nums[j] < nums[e]) {
                swap(nums[i], nums[j]);
                i++;
            }
        } 
        swap(nums[e], nums[i]);
        return i;
    }
    
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        sortArray(nums, 0, n-1);
        return nums;
    }
    ```
- TC: $O(nlogn)$ (average), $O(n^2)$ (worst)
- SC: $O(logn)$ (average), $O(n)$ (worst)
