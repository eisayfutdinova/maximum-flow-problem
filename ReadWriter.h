#include <iostream>
#include <fstream>
#include <vector>
#include "Edge.h"

using namespace std;

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter(string path)
    {
        fin.open(path, std::ios::in);
    }

    // read M edges, and fill vector
    void readGraph(int &N, vector<vector<int>> &graph, vector<Edge> &edges, int &sMain, int &tMain)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;

        vector<int> stok, t;

        for (int i = 0; i < N; i++)
        {
            vector<int> vec;
            for (int j = 0; j < N; ++j)
            {
                int p;
                fin >> p;
                vec.push_back(p);
            }

            graph.push_back(vec);
            std::getline(fin, s);
        }

        int k;
        for (int i = 0; i < N; ++i)
        {
            k = 0;
            for (int j = 0; j < N; ++j)
            {
                if (graph[i][j] != 0)
                {
                    Edge edge;
                    edge.A = i;
                    edge.B = j;
                    edge.W = graph[i][j];
                    edges.push_back(edge);
                }
                if (graph[i][j] == 0)
                    k++;
            }
            if (k == N)
                t.push_back(i);
        }

        vector<bool> arr(N, false);
        for (int i = 0; i < edges.size(); ++i)
        {
            arr[edges[i].B] = true;
        }

        for (int i = 0; i < N; ++i)
        {
            if (!arr[i])
                stok.push_back(i);
        }


        if (stok.size() == 1)
        {
            sMain = stok[0];
            tMain = t[0];
        } else
        {
            sMain = N;
            tMain = sMain + 1;

            for (int l = 0; l < N; ++l)
            {
                graph[l].push_back(0);
                graph[l].push_back(0);
            }

            N += 2;
            vector<int> vecS(N, 0);
            vector<int> vecT(N, 0);

            graph.push_back(vecS);
            graph.push_back(vecT);


            for (int n = 0; n < t.size(); ++n)
            {
                graph[sMain][stok[n]] = INT_MAX;
                graph[t[n]][tMain] = INT_MAX;
            }
        }
    }
};