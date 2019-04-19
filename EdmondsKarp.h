#include <vector>
#include <queue>
#include <memory.h>
#include <limits.h>

using namespace std;

class EdmondsKarp
{
    bool bfs(vector<vector<int>> rGraph, int N, int s, int t, int parent[])
    {
        bool visited[N];
        for (int i = 0; i < N; ++i)
        {
            visited[i] = 0;
        }

        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < N; v++)
            {
                if (!visited[v] && rGraph[u][v] > 0)
                {
                    parent[v] = u;
                    visited[v] = true;

                    if (v == t)
                        return true;
                    q.push(v);
                }
            }
        }

        return false;
    }

public:
    int edmondsKarp(vector<vector<int>> graph, int N, int s, int t, string filename)
    {
        int u, v;

        vector<vector<int>> rGraph(N, vector<int>(N));

        for (u = 0; u < N; u++)
            for (v = 0; v < N; v++)
                rGraph[u][v] = graph[u][v];

        int parent[N];

        int max_flow = 0;

        while (bfs(rGraph, N, s, t, parent))
        {

            int path = INT_MAX;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                path = min(path, rGraph[u][v]);
            }


            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                rGraph[u][v] -= path;
                rGraph[v][u] += path;
            }

            // Add path flow to overall flow
            max_flow += path;
        }

        std::fstream fout;
        filename = filename + "MAXFLOW.txt";
        fout.open(filename, std::ios::out);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                fout << rGraph[i][j] << " ";
            }

            fout << "\n";
        }

        fout.close();

        // Return the overall flow
        return max_flow;
    }

};