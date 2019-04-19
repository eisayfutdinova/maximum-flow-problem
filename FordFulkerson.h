#include <vector>
#include <queue>
#include <memory.h>
#include <stack>

using namespace std;

class FordFulkerson
{

    bool dfs(vector<vector<int>>& rGraph, int N, int s, int t, vector<int>& parent, vector<bool>& visited)
    {
        if (s == t) return true;
        visited[s] = true;

        for (int i = 0; i < N; ++i)
        {
            if (rGraph[s][i] != 0 && !visited[i])
            {
                parent[i] = s;
                if (dfs(rGraph, N, i, t, parent, visited))
                    return true;
            }
        }
        return false;
    }

public:
    int fordFulkerson(vector<vector<int>> graph, int N, int s, int t)
    {

        int u, v;

        //остаточный граф, изначально равен данному graph
        vector<vector<int>> rGraph(N, vector<int>(N));
        vector<bool> visited(N, false);

        for (u = 0; u < N; u++)
            for (v = 0; v < N; v++)
                rGraph[u][v] = graph[u][v];

        vector<int> parent(N);  // путь найденного потока

        int max_flow = 0;

        // пока можем найти путь
        while (dfs(rGraph, N, s, t, parent, visited))
        {
            for (int i = 0; i < N; ++i)
            {
                visited[i] = false;
            }

            int path = INT_MAX;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                path = min(path, rGraph[u][v]);
            }

            // update residual capacities of the edges and reverse edges
            // along the path
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                rGraph[u][v] -= path;
                rGraph[v][u] += path;
            }

            // Add path flow to overall flow
            max_flow += path;
        }

        // Return the overall flow

        return max_flow;
    }
};
