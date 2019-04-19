#include  <iostream>
#include "ReadWriter.h"
#include "FordFulkerson.h"
#include "EdmondsKarp.h"
#include "Dinic.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <intrin.h>

#pragma intrinsic(__rdtsc)

using namespace std;

int main()
{
    vector<pair<string, int>> files = {{"input_10_0.0.txt",     10},
                                       {"input_10_0.5.txt",     10},
                                       {"input_10_1.0.txt",     10},
                                       {"input_10_disco.txt",   10},
                                       {"input_310_0.0.txt",    310},
                                       {"input_310_0.5.txt",    310},
                                       {"input_310_1.0.txt",    310},
                                       {"input_310_disco.txt",  310},
                                       {"input_610_0.0.txt",    610},
                                       {"input_610_0.5.txt",    610},
                                       {"input_610_1.0.txt",    610},
                                       {"input_610_disco.txt",  610},
                                       {"input_910_0.0.txt",    910},
                                       {"input_910_0.5.txt",    910},
                                       {"input_910_1.0.txt",    910},
                                       {"input_910_disco.txt",  910},
                                       {"input_1210_0.0.txt",   1210},
                                       {"input_1210_0.5.txt",   1210},
                                       {"input_1210_1.0.txt",   1210},
                                       {"input_1210_disco.txt", 1210},
                                       {"input_1510_0.0.txt",   1510},
                                       {"input_1510_0.5.txt",   1510},
                                       {"input_1510_1.0.txt",   1510},
                                       {"input_1510_disco.txt", 1510},
                                       {"input_1810_0.0.txt",   1810},
                                       {"input_1810_0.5.txt",   1810},
                                       {"input_1810_1.0.txt",   1810},
                                       {"input_1810_disco.txt", 1810},
                                       {"input_2110_0.0.txt",   2110},
                                       {"input_2110_0.5.txt",   2110},
                                       {"input_2110_1.0.txt",   2110},
                                       {"input_2110_disco.txt", 2110},
                                       {"input_2410_0.0.txt",   2410},
                                       {"input_2410_0.5.txt",   2410},
                                       {"input_2410_1.0.txt",   2410},
                                       {"input_2410_disco.txt", 2410},
                                       {"input_2710_0.0.txt",   2710},
                                       {"input_2710_0.5.txt",   2710},
                                       {"input_2710_1.0.txt",   2710},
                                       {"input_2710_disco.txt", 2710}};

    FordFulkerson ff;
    EdmondsKarp ek;
    Dinics dk;

    //для записи продолждительности работы алгоритмоы
    std::fstream fout;
    fout.open("output.txt", std::ios::out);

    //для записи результатов
    std::fstream ffout;
    ffout.open("Results.txt", std::ios::out);

    for (int k = 0; k < 40; ++k)
    {
        vector<vector<int>> graph;  //граф
        vector<Edge> edges;
        int s = 0, t = 0;

        ReadWriter rw(files[k].first);
        int N = files[k].second;
        int f = 0;
        int e = 0;
        int d = 0;

        rw.readGraph(N, graph, edges, s, t);


        //Создает rdtsc инструкция, которая возвращает метку времени процессора. Метка времени процессора регистрирует число тактов с момента последнего сброса.
        // unsigned long long start, finish;
        // start = __rdtsc(); /// start timer

        auto timeFord1 = chrono::steady_clock::now();
        f = ff.fordFulkerson(graph, N, s, t);
        auto timeFord2 = chrono::steady_clock::now();
        double ford = (chrono::duration_cast<chrono::duration<double >>(timeFord2 - timeFord1).count() * 1000000000);


        auto timeEdmond1 = chrono::steady_clock::now();
        e = ek.edmondsKarp(graph, N, s, t, files[k].first);
        auto timeEdmond2 = chrono::steady_clock::now();
        double edmond = (chrono::duration_cast<chrono::duration<double >>(timeEdmond2 - timeEdmond1).count() *
                         1000000000);

        auto timeDinic1 = chrono::steady_clock::now();
        d = dk.Dinic(graph, N, s, t);
        auto timeDinic2 = chrono::steady_clock::now();
        double dinic = (chrono::duration_cast<chrono::duration<double >>(timeDinic2 - timeDinic1).count() * 1000000000);

        fout << files[k].first << ";" << fixed << ford << ";" << edmond << ";" << dinic << "\n";

        ffout << k << " " << f << " " << e << " " << d << "\n";

        // finish = __rdtsc();
        //unsigned long long res = finish - start;

    }

    fout.close();

    ffout.close();

    return 0;
}