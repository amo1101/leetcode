#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
public:
	UnionFind(int size) {
		for (int i = 0; i < size; ++i) {
			root.push_back(i);
			rank.push_back(1);
		}
	}

	int find(int x) {
		if (x == root[x]) {
			return x;
		}

		return root[x] = find(root[x]);
	}

	void unionSet(int x, int y) {
		int rx = find(x);
		int ry = find(y);
		if (rx == ry) {
			return;
		}

		if (rank[rx] > rank[ry]) {
			root[ry] = rx;
		} else if (rank[rx] < rank[ry]) {
			root[rx] = ry;
		} else {
			root[ry] = rx;
			rank[rx]++;
		}
	}

	bool isConnected(int x, int y) {
		return find(x) == find(y);
	}

private:
	vector<int> root;
	vector<int> rank;
};

// DFS traverse all vertices
bool validPathDFS(int n, vector<vector<int>>& edges, int start, int end) {
	vector<vector<int>> adjacencyList;
	for (int i = 0; i < edges.size(); ++i) {
		adjacencyList[edges[i][0]].push_back(edges[i][1]);
		adjacencyList[edges[i][1]].push_back(edges[i][0]);
	}
	vector<bool> seen(n, false);

	stack<int> sk;
	sk.push(start);
	while (!sk.empty()) {
		int node = sk.top();
		sk.pop();
		if (node == end) {
			return true;
		}
		if (seen[node]) {
			continue;
		}
		seen[node] = true;

		for (auto nextNode : adjacencyList[node]) {
			sk.push(nextNode);
		}
	}

	return false;
}

// BFS traverse all vertices
bool validPathBFS(int n, vector<vector<int>>& edges, int start, int end) {
	vector<vector<int>> adjacencyList;
	for (int i = 0; i < edges.size(); ++i) {
		adjacencyList[edges[i][0]].push_back(edges[i][1]);
		adjacencyList[edges[i][1]].push_back(edges[i][0]);
	}
	vector<bool> seen(n, false);
	queue<int> q;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (node == end) {
			return true;
		}
		if (seen[node]) {
			continue;
		}
		for (auto nextNode : adjacencyList[node]) {
			q.push(nextNode);
		}
	}
	return false;
}

// DFS find all paths
void allPathsDFS(vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& paths) {
	path.push_back(node);
	if (node == graph.size() - 1) {
		paths.emplace_back(path);
		return;
	}

	for (auto nextNode : graph[node]) {
		allPathsDFS(graph, nextNode, path, paths);
		path.pop_back();
	}
}

vector<vector<int>> allPaths(vector<vector<int>>& graph) {
	vector<vector<int>> paths;
	if (graph.size() == 0) {
		return paths;
	}

	vector<int> path;
	allPathsDFS(graph, 0, path, paths);
	return paths;
}

// BFS find all paths
vector<vector<int>> allPathsBFS(vector<vector<int>>& graph) {
	vector<vector<int>> paths;
	if (graph.size() == 0) {
		return paths;
	}

	vector<int> path;
	queue<vector<int>> q;
	path.push_back(0);
	q.push(path);
	while (!q.empty()) {
		vector<int> curr = q.front();
		q.pop();
		int node = curr.back();
		for (auto nextNode : graph[node]) {
			vector<int> tempPath(curr.begin(), curr.end());
			tempPath.push_back(nextNode);
			if (nextNode == graph.size() - 1) {
				paths.push_back(tempPath);
			} else {
				q.push(tempPath);
			}
		}
	}

	return paths;
}

class Edge {
public:
	int point1;
	int point2;
	int cost;
	Edge(int point1, int point2, int cost)
		: point1(point1), point2(point2), cost(cost) {}
};

// Overload the < operator.
bool operator<(const Edge& edge1, const Edge& edge2) {
	return edge1.cost > edge2.cost;
}

// Minimum spanning tree - kruskal's algorithm
// premise: weighted undirected graph, V - 1 edges needed
 // Kruskal's algorithm
// Minimum costs
int minCostConnectPointsKruskal(vector<vector<int>>& points) {
	if (points.size() == 0) {
		return 0;
	}
	int sz = points.size();
	priority_queue<Edge> pq;
	UnionFind uf(sz);

	for (int i = 0; i < sz; i++) {
		vector<int>& coordinate1 = points[i];
		for (int j = i + 1; j < sz; j++) {
			vector<int>& coordinate2 = points[j];
			// Calculate the distance between two coordinates.
			int cost = abs(coordinate1[0] - coordinate2[0]) +
				abs(coordinate1[1] - coordinate2[1]);
			Edge edge(i, j, cost);
			pq.push(edge);
		}
	}

	int result = 0;
	int count = sz - 1;
	while (!pq.empty() && count > 0) {
		Edge edge = pq.top();
		pq.pop();
		if (!uf.isConnected(edge.point1, edge.point2)) {
			uf.unionSet(edge.point1, edge.point2);
			result += edge.cost;
			count--;
		}
	}
	return result;
}

// Prim's algorithm
int minCostConnectPointsPrim(vector<vector<int>>& points) {
	if (points.size() == 0) {
		return 0;
	}
	int sz = points.size();
	priority_queue<Edge> pq;
	vector<bool> visited(sz);
	int result = 0;
	int count = sz - 1;
	// Add all edges from points[0] vertex
	vector<int>& coordinate1 = points[0];
	for (int j = 1; j < sz; j++) {
		// Calculate the distance between two coordinates
		vector<int>& coordinate2 = points[j];
		int cost = abs(coordinate1[0] - coordinate2[0]) +
			abs(coordinate1[1] - coordinate2[1]);
		Edge edge(0, j, cost);
		pq.push(edge);
	}
	visited[0] = true;

	while (!pq.empty() && count > 0) {
		Edge edge = pq.top();
		pq.pop();
		int point1 = edge.point1;
		int point2 = edge.point2;
		int cost = edge.cost;
		if (!visited[point2]) {
			result += cost;
			visited[point2] = true;
			for (int j = 0; j < sz; j++) {
				if (!visited[j]) {
					int distance = abs(points[point2][0] - points[j][0]) +
						abs(points[point2][1] - points[j][1]);
					pq.push(Edge(point2, j, distance));
				}
			}
			count--;
		}
	}
	return result;
}

// Single source shortest path
// Dijkstra's algorithm
// premise: 1) Weighted directed graph, 2) weight of edges should be non-negative
// No.743. Network Delay Time
class Solution {
public:
	int networkDelayTime(vector<vector<int>>& times, int n, int k) {
		vector<vector<pair<int, int>>> adjacency_list(n + 1);
		priority_queue<pair<int, int>, vector<pair<int, int>>,
			greater<pair<int, int>>> minPQ;
		vector<int> costTime(n + 1, INT_MAX);

		for (int i = 0; i < times.size(); ++i) {
			int src = times[i][0];
			int dest = times[i][1];
			int time = times[i][2];
			adjacency_list[src].push_back({ time, dest });
		}

		// dijkstra's algorithm
		costTime[k] = 0;
		minPQ.push({ 0, k });
		while (!minPQ.empty()) {
			int currTime = minPQ.top().first;
			int currNode = minPQ.top().second;
			minPQ.pop();
			if (currTime > costTime[currNode]) {
				continue;
			}
			for (auto next : adjacency_list[currNode]) {
				int time = next.first;
				int nextNode = next.second;
				if (costTime[nextNode] > currTime + time) {
					costTime[nextNode] = currTime + time;
					minPQ.push({ costTime[nextNode], nextNode });
				}
			}
		}

		int answer = INT_MIN;
		for (int i = 1; i < n + 1; ++i) {
			answer = max(answer, costTime[i]);
		}
		return answer == INT_MAX ? -1 : answer;
	}
};

// No.787. Cheapest Flights Within K Stops
// Bellman-Ford algorithm
class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		vector<vector<int>> prices(2, vector<int>(n, INT_MAX));
		int curr = 0, next = 1;
		prices[curr][src] = 0;

		for (int i = 0; i <= k; ++i) {
			for (auto& f : flights) {
				int from = f[0];
				int to = f[1];
				int cost = f[2];
				if (prices[curr][from] != INT_MAX &&
					prices[curr][from] + cost < prices[next][to]) {
					prices[next][to] = prices[curr][from] + cost;
				}
			}
			swap(curr, next);
			prices[curr][src] = 0;
		}
		return prices[curr][dst] == INT_MAX ? -1 : prices[curr][dst];
	}
};

// No.1631. Path With Minimum Effort
// SPFA
class Solution {
public:
	int minimumEffortPath(vector<vector<int>>& heights) {
		int m = heights.size();
		int n = heights[0].size();

		vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
		cost[0][0] = 0;
		vector<vector<int>> seen(m, vector<int>(n, 0));
		seen[0][0] = 1;

		queue<pair<int, int>> q;
		q.push({ 0,0 });

		int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			int x = p.first, y = p.second;
			seen[x][y] = 0;
			for (auto d : dirs) {
				int i = x + d[0];
				int j = y + d[1];
				if (i < 0 || i >= m || j < 0 || j >= n || cost[i][j] <= max(cost[x][y], abs(heights[i][j] - heights[x][y])))
					continue;
				if (!seen[i][j]) {
					q.push({ i,j });
					seen[i][j] = 1;
				}

				cost[i][j] = max(cost[x][y], abs(heights[i][j] - heights[x][y]));
			}
		}

		return cost.back().back();
	}
};








