/*
Given a 2D array houses[][], consisting of n 2D coordinates {x, y} where each coordinate represents the location of each house, the task is to find the minimum cost to connect all the houses of the city.

The cost of connecting two houses is the Manhattan Distance between the two points (xi, yi) and (xj, yj) i.e., |xi – xj| + |yi – yj|, where |p| denotes the absolute value of p.

Examples :
    Input: n = 5 houses[][] = [[0, 7], [0, 9], [20, 7], [30, 7], [40, 70]]
    Output: 105
    Explanation:
    Connect house 1 (0, 7) and house 2 (0, 9) with cost = 2
    Connect house 1 (0, 7) and house 3 (20, 7) with cost = 20
    Connect house 3 (20, 7) with house 4 (30, 7) with cost = 10 
    At last, connect house 4 (30, 7) with house 5 (40, 70) with cost 73.
    All the houses are connected now.
    The overall minimum cost is 2 + 10 + 20 + 73 = 105.

    Input: n = 4 houses[][] = [[0, 0], [1, 1], [1, 3], [3, 0]]
    Output: 7
    Explanation: 
    Connect house 1 (0, 0) with house 2 (1, 1) with cost = 2
    Connect house 2 (1, 1) with house 3 (1, 3) with cost = 2 
    Connect house 1 (0, 0) with house 4 (3, 0) with cost = 3 
    The overall minimum cost is 3 + 2 + 2 = 7.

Constraint:
    1 ≤ n ≤ 10^3
    0 ≤ houses[i][j] ≤ 10^3
*/

// Approach 1: By building graph: TC: O(n^2logn), SC: O(n^2)
class Solution {
  public:
    int minCost(vector<vector<int>>& houses) {
        // in this question we are supposed to find MST of a graph, 
        // but that graph is not directly given to us
        // so we need to evaluate the graph first
        // the graph will contain an edge from every vertex to every other vertex
        // where the cost of each edge will be manhattan distance between those two vertices
        int n = houses.size();
        int dist;
        vector<vector<pair<int, int>>> adjList(n);
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                dist = abs(houses[i][0] - houses[j][0]) + abs(houses[i][1] - houses[j][1]);
                adjList[i].push_back({dist, j});
                adjList[j].push_back({dist, i});
            }
        // TC: O(n^2)
        
        // using prim's algorithm to find MST cost
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});
        vector<int> vis(n, 0);
        int verticesVisited = 0;
        int mstCost = 0;
        while(!pq.empty()) {
            pair<int, int> top = pq.top();
            int dist = top.first;
            int i = top.second;
            pq.pop();
            if(!vis[i]) {
                mstCost += dist;
                vis[i] = 1;
                verticesVisited++;
                if(verticesVisited == n)
                    break;
                for(auto edge: adjList[i]) {
                    if(!vis[edge.second])
                        pq.push(edge);
                }
            }
        }
        // TC: O(n^2logn)
        
        return mstCost;
    }
};

// Approach 2: Without building graph: TC: O(n^2), SC: O(n)
class Solution {
  public:
    int minCost(vector<vector<int>>& houses) {
        // in this question we are supposed to find MST of a graph, 
        // but instead of building a graph, we can directly solve the problem
        // choose a non-visited vertex, with minimum cost to reach from so far visited nodes
        // mark it as visited and update it's cost in totalCost
        // then find dist to all the non-visited vertices from this vertex 
        // and repeat the process V times
        int n = houses.size();
        vector<int> minDist(n, INT_MAX);
        vector<int> vis(n, 0);
        int cost = 0;
        
        minDist[0] = 0;
        for(int i = 0; i < n; ++i) {
            // find non-visited minimum distance vertex
            int u = -1;
            for(int j = 0; j < n; ++j)
                if(!vis[j] && (u == -1 || minDist[j] < minDist[u]))
                    u = j;
                
            cost += minDist[u];
            vis[u] = 1;
            
            // update distance to non-visited vertices from u
            for(int j = 0; j < n; ++j)
                if(!vis[j]) {
                    minDist[j] = min(minDist[j], abs(houses[u][0] - houses[j][0]) + abs(houses[u][1] - houses[j][1]));
                }
        }
        
        return cost;
    }
};