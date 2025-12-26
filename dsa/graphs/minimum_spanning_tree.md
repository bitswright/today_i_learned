# Minimum Spanning Tree
- **Spanning Tree**: A tree formed from a graph with all `N` nodes but only `N-1` edges such that all nodes are connected.
    - A graph can have more than 1 spanning tree.
- **Minimum Spanning Tree**: A spanning tree such that the weight of the selected edges is the minimum among all spanning trees.
    - A graph can have more than 1 minimum spanning tree.

## Prim's Algorithm
- Use a visited array and a priority_queue for finding the next minimum edge from the list of already visited nodes.
- Store any one of the node (say `0`) in the prority queue (Min-heap) as `{0, 0}` (`{edgeWt, currNode, parentNode}` in case we want the MST too). 
- Now, keep poping elements from the priority queue, and if current node is not visited, then add `edgeWt` to `mstWt` and for each neighbouring node, store `{edgeWt, neighNode}` in priority_queue.
- TC: $O(E.logE)$
- SC: $O(V+E)$

## Krushkal's Algorithm
