#include <cstring>
#include <limits.h>
#include <vector>

using namespace std;

class Dinics
{

public:
    int s, t;
    vector<vector<int>> graph;
    vector<vector<int>> rGraph;


    bool bfs(int N, vector<int> &d)
    {
        queue<int> q;
        q.push(s);
        for (int i = 0; i < N; ++i)
        {
            d[i] = -1;
        }
        d[s] = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int to = 0; to < N; ++to)
                if (d[to] == -1 && rGraph[v][to] < graph[v][to])
                {
                    q.push(to);
                    d[to] = d[v] + 1;
                }
        }
        return d[t] != -1;
    }

    int dfs(int N, int v, int flow, vector<int> &d, vector<int> &ptr)
    {
        if (!flow) return 0;
        if (v == t) return flow;
        for (int to = ptr[v]; to < N; ++to)
        {

            //это условие эквивалентно поиску во вспомогательной слоистой сети
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(N, to, min(flow, graph[v][to] - rGraph[v][to]), d, ptr);
            if (pushed)
            {
                rGraph[v][to] += pushed;
                rGraph[to][v] -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int Dinic(vector<vector<int>> g, int N, int source, int stock)
    {
        vector<int> d(N);   //длины из истока до i-той вершины
        vector<int>pt(N);   // номер первого неудалённого ребра, идущего из i
        s = source;
        t = stock;

        graph.resize(N);
        rGraph.resize(N);
        for (int i = 0; i < N; ++i)
        {
            graph[i].resize(N);
            rGraph[i].resize(N);
            for (int j = 0; j < N; ++j)
            {
                graph[i][j] = g[i][j];
                rGraph[i][j] = 0;
            }
        }

        int flow = 0;
        while (bfs(N, d))
        {
            for (int i = 0; i < N; ++i)
            {
                pt[N] = 0;
            }

            while (int pushed = dfs(N, s, INT_MAX, d, pt))
                flow += pushed;
        }

        return flow;
    }
};