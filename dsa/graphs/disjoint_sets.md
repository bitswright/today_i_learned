# Disjoint Sets

- Given a graph with multiple components, disjoint sets help us evaluate whether two vertices belong to the same component or not.
- Generally, used for dynamic graphs.
- **Brute Force Approach**: Perform BFS/DFS on the graph starting from any of one of the given vertices, and if the other point doesn't gets traversed, then both points belong to different components, else they belong to the same component. 
    - Time Complexity: $O(V + E)$
    - But Disjoint Set data structure can solve this problem in $O(1)$ TC.

## Disjoint Set Data Structure
- Disjoint set DS provides 2 functionalities:
    - `findPar(Node)`: Returns parent of given node
    - `union(Node1, Node2)`: Adds an edge between given two nodes.
        - It can be implemented using **union by rank** or **union by size**.
    
- **Union By Rank**: 
    - **Rank**: #nodes between the node and the leaf nodes (including leaf nodes).
    - **Ultimate Parent**: Topmost node or the root node.
    - Code:
        ```cpp
        class DisjointSet {
            vector<int> rank, parent;
            public:
            DisjointSet(int n) {
                rank.resize(n + 1, 0);
                parent.resize(n + 1);
                for (int i = 0; i <= n; i++) {
                    parent[i] = i;
                }
            }

            int findUPar(int node) {
                if (node == parent[node])
                    return node;
                // updating parent of each parsed node for path compression
                return parent[node] = findUPar(parent[node]);
            }

            void unionByRank(int u, int v) {
                int ulp_u = findUPar(u);
                int ulp_v = findUPar(v);
                if (ulp_u == ulp_v) return;
                if (rank[ulp_u] < rank[ulp_v]) {
                    parent[ulp_u] = ulp_v;
                }
                else if (rank[ulp_v] < rank[ulp_u]) {
                    parent[ulp_v] = ulp_u;
                }
                else {
                    parent[ulp_v] = ulp_u;
                    rank[ulp_u]++;
                }
            }
        };
        ```
    - Notes:
        - Node with lower rank is made child of node with higher rank in `unionByRank` because 
            - it will increase the time for path compression for lesser number of nodes and,
            - height of the new tree will be smaller as compared to other way around.
        - Rank of the nodes gets distored on path compression. But we cannot update the rank of a node on path compression as we are not sure what the new rank of a node will be in $O(1)$.
            - Hence, we can consider the rank of a node as upper bound on the rank (#nodes between ultimate parent and itself).
            - Not updating rank during path compression operation doesn't effect union operation as both of them are independent operations.
            - Purpose of keeping track of rank of node is only to keep the tree balanced (minimize height of the tree) during union operation.
            - If we compute rank of a node during union operation then amortized TC would worsen.
        - Time complexity for this algorithm is $O(4)$ (calculated using long mathematical derivation). Which can be considered as $O(1)$.
- **Union By Size**:
    - Since, rank of nodes get distored during union operation, we can use size as the deciding factor which component is larger than the other.
    - It is much more intutive than union by rank.
    - Same as union by rank, but uses `size` array to store size of the component starting at node `i`.
    - Code:
        ```cpp
        class DisjointSet {
            vector<int> rank, parent, size;
        public:
            DisjointSet(int n) {
                rank.resize(n + 1, 0);
                parent.resize(n + 1);
                size.resize(n + 1);
                for (int i = 0; i <= n; i++) {
                    parent[i] = i;
                    size[i] = 1;
                }
            }

            int findUPar(int node) {
                if (node == parent[node])
                    return node;
                return parent[node] = findUPar(parent[node]);
            }

            void unionBySize(int u, int v) {
                int ulp_u = findUPar(u);
                int ulp_v = findUPar(v);
                if (ulp_u == ulp_v) return;
                if (size[ulp_u] < size[ulp_v]) {
                    parent[ulp_u] = ulp_v;
                    size[ulp_v] += size[ulp_u];
                }
                else {
                    parent[ulp_v] = ulp_u;
                    size[ulp_u] += size[ulp_v];
                }
            }
        };
        ```
    - TC: $O(4)$ ~ $O(1)$

## Questions
- [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/)
    - In this question, we need to find the number of components in the graph.
    - If the number of edges in the graph is less than `n-1` then we can simply return `-1` as we cannot connect all the nodes of the graph using less than `n-1` edges.
    - Then we can find the #components in the graph using BFS/DFS or disjoint set. And then just return `components-1`. As only those number of edges can be moved to make all the nodes connected.
- [947. Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/)
    - We are given a list of coordinates where stones are present. Now, we need to find the number of stones that can be removed. If two stones share same row or column, then one of them can be removed.
    - In other words, we need to group all the stones that share a row/column and then just return (total #stones) - (#groups).
    - Now, we can solve this question by BFS/DFS or Disjoint Set. 
    - Important Note: First find the `max_row` and `max_col`. Then create a Disjoint set of size `max_row + max_col`. Then for each stone, just pair by the rows and cols in which stone is present. 
        - This solution seems less intutive but it is easy to implement and best solution.
        - TC: $O(N)$ and SC: $O(R*C)$
    - Another approach (more space complexity and time complexity, but more intutive): Create a disjoint set of size of #stones. Now, for each stone, store the stones in maps (row -> stones and col -> stones).
        - TC: $O(N^2)$ and SC: $O(4N)$
- [827. Making A Large Island](https://leetcode.com/problems/making-a-large-island/description/)
    - In this question there is binary grid given of size `n`x`n`, where 1 is land and 0 is sea. We can change one 0 to 1 and then return the maximum island.
    - We can solve this question using Disjoint Set (union by size) of size `n*n`. Tranverse all nodes, and for each neighbouring node, if it is a land, then we union it with current node. After this, we tranverse all nodes again, and if it is a sea, then we keep track of all the neighbouring land and store their ultimate parents in a set. Then just check if adding the size of each nighbouring land island size would make up the largest island or not.
    - TC: $O(N*N)$