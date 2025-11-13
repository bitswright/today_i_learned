# Graphs

## Bipartite Graph
- An undirected graph in which vertices can be divided into two groups such that no vertices belonging to the same group share an edge. Or in other words, all the edges of the graph have vertices belonging to the different groups.
- If we are able to colour a graph with two colors such that no adjacent nodes have the same colour, it is called a bipartite graph.
- To find if the graph is bipartite or not, we can make the nodes with different colors (in visited array) while traversing the graph using BFS/DFS. And while traversing if any of the neighbouring node is found to have colored the same color as current node, we can say that graph is not bipartite, else the graph is bipartite.
- A graph with odd cycle is always a non-bipartite graph.
- Example:
    ```cpp
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n, 0);
        queue<pair<int, int>> q;
        for(int i = 0; i < n; ++i) {
            if(!vis[i]) {
                q.push({i, 1});
                vis[i] = 1;
                while(!q.empty()) {
                    auto front = q.front();
                    int node = front.first;
                    int color = front.second;
                    q.pop();
                    int otherColor = color == 1 ? 2 : 1;
                    for(int neigh: graph[node]) {
                        if(!vis[neigh]) {
                            vis[neigh] = otherColor;
                            q.push({neigh, otherColor});
                        }
                        else if(vis[neigh] == color) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    ```

### Sample Questions
- [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/description/)

## Directed Acyclic Graph
- A directed graph without a cycle.
- A DAG can be determined using DFS and BFS (Kahn's Algorithm).

### Detecting Cycle in a Directed Graph using DFS
- A cycle in a directed graph can be detected using DFS by storing all the nodes visited in the current path.
- If a node is found to be present in the current path and is neighbour of the current node, then graph contains a cycle.
- For this, we need to store a new array `pathVis` along with `vis` array and update it according to traversal.
- Example:
    ```cpp
    bool dfs(int i, vector<int>& vis, vector<int>& pathVis, vector<vector<int>>& adjList) {
        vis[i] = 1;
        pathVis[i] = 1;
        for(int neigh: adjList[i]) {
            if(!vis[neigh]) {
                if(dfs(neigh, vis, pathVis, adjList) == false) {
                    return false;
                }
            }
            else if(pathVis[neigh]) {
                return false;
            }
        }
        pathVis[i] = 0;
        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> vis(numCourses, 0);
        vector<int> pathVis(numCourses, 0);
        vector<vector<int>> adjList(numCourses);
        for(auto prerequisite: prerequisites) {
            adjList[prerequisite[1]].push_back(prerequisite[0]);
        }
        for(int i = 0; i < numCourses; ++i) {
            if(!vis[i]) {
                if(dfs(i, vis, pathVis, adjList) == false) {
                    return false;
                }
            }   
        }
        return true;
    }
    ```

### Detecting Cycle in a Directed Graph using BFS (Kahn's Algorithm)
- Kahn's Algorithm
    - Find indegree of all the vertices
    - Store all the vertices with indegree = 0 in the queue
    - Start traversing using BFS, and decrement indegree of all the neighbouring nodes.
    - Insert new nodes in the queue, if their indegree becomes 0.
    - If all the nodes are traversed, then there is no cycle in graph, i.e. it is a DAG.
- If we store the nodes in a list as we visited them using Kahn's Algorithm, we get Topological Sorted List of vertices.
    - In Topological Sort, if there is an edge from `u` to `v`, then node `u` appears before node `v`.
- Example:
    ```cpp
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adjList(numCourses);
        vector<int> indegree(numCourses, 0);
        for(auto prerequisite: prerequisites) {
            adjList[prerequisite[1]].push_back(prerequisite[0]);
            indegree[prerequisite[0]]++;
        }
        queue<int> q;
        vector<int> topoSort;
        for(int i = 0; i < numCourses; ++i)
            if(indegree[i] == 0) {
                q.push(i);
                topoSort.push_back(i);
            }
        while(!q.empty()) {
            int front = q.front();
            q.pop();
            for(int neigh: adjList[front]) {
                indegree[neigh]--;
                if(indegree[neigh] == 0) {
                    q.push(neigh);
                    topoSort.push_back(neigh);
                }
            }
        }
        return topoSort.size() == numCourses ? topoSort : vector<int>{};
    }
    ```

### Topological Sorting using DFS
- We want to store all the nodes of the graph topologically sorted in a stack, such that as we pop elements from the stack, we get the topo sort of the graph.
- Code:
    ```cpp
    void topoSort(int node, vector<int> adjList[], int vis[], stack<int> st) {
        vis[node] = 1;
        for(int neigh: adjList[node]) {
            if(!vis[neigh]) {
                topoSort(neigh, adjList, vis, st);
            }
        }
        st.push(node);
    }

    void main() {
        ...
        stack<int> st;
        for(int i = 0; i < N; ++i)
            if(!vis[i])
                topoSort(i, adjList, vis, st);
        ...
    }
    ```


### Sample Questions
- [207. Course Schedule](https://leetcode.com/problems/course-schedule/description/)
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/description/)
    - Reverse the graph, and then perform Kahn's Algorithm.
- [Alien Dictionary](https://www.geeksforgeeks.org/problems/alien-dictionary/1)
    - Construct graph using the words given. (Create an edge for non-matching characters while comparing all the words).
    - If characters in the alien language is not given, store the characters found in an array and only push the characters in queue if their indegree is 0 and they are present in the alien language.
    - Then, perform the topological sort.


## Shortest Path in Graphs

### Graph with unit distance
- Store an array `dist` which represents shortest distance from source node to respective nodes.
- Initialize `dist[source] = 0`
- Peform BFS, and for each neighbouring node, `dist[neigh] = dist[parentNode] + 1`
- Return `dist` array.

### DAG
- While standing on a node in topo sort, we know the short distance from source node to that node. Now, we just need to relax the out-going nodes from this node and repeat this process for all the nodes.
- Code:
    ```cpp
    
    ```