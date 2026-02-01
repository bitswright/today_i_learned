# Priority Queue

- A special type of queue in which elements are processed based on a priority assigned to each element instead of the order in which they arrive. 
- If two elements have same priority, then they are processed in the order they arrive.

## Binary Heap
- Binary tree that:
    - is a complete binary tree (all levels completely filled, and last filled from left to right)
    - satisfies heap property (parent node is greater/smaller than child nodes based on max/min heap)
- Represented as an array. (Left Child: `2*i+1`, Right Child: `2*i+2`, Parent: `(i-1)/2`).
- Operations:
    - Insert: $O(logn)$
    - Heapify: $O(logn)$
    - GetMin/GetMax: $O(1)$
    - ExtractMin/ExtractMax: $O(logn)$ -> using Heapify
    - DecreaseKey/IncreaseKey: $O(logn)$ -> using insertion
    - Delete: $O(logn)$ -> decrease key to INT_MIN or increase key to INT_MAX, ExtractMin/ExtractMax.

## Classic problems
- Directly using min-heap
  - [Kth Largest Element in an Array](/dsa/problems/priority_queue_and_heap/lc_215.md)
  - [Merge k Sorted Lists](/dsa/problems/priority_queue_and_heap/lc_23.md)
  - [Rank Transform of an Array](/dsa/problems/priority_queue_and_heap/lc_1331.md)
  - [Connect n ropes with minimal cost](/dsa/problems/priority_queue_and_heap/connect_n_ropes.md)
  - [Kth Largest Element in a Stream](/dsa/problems/priority_queue_and_heap/lc_703.md)
- Directly using max-heap
  - [Kth Smallest Element in an Array](/dsa/problems/priority_queue_and_heap/kth_smallest.md)