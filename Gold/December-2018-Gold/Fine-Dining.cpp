#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

#define INF 2000000000

class Solution {
    private:
        int N, M, K;
        vector<pair<int, int>> edges[50001]; // each edge is haybale first then weight second
        vector<pair<int, int>> bales;
        set<pair<int, int>> dists;
        int weights[50001];
    public:

        void prepData() {
            ifstream fin ("dining.in");
            fin >> N >> M >> K; int a, b, c;
            for (int i = 0; i < M; i++) {
                fin >> a >> b >> c; a--; b--;
                edges[a].push_back(make_pair(b, c));
                edges[b].push_back(make_pair(a, c));
            }
            for (int i = 0; i < K; i++) {
                fin >> a >> b; a--;
                bales.push_back(make_pair(a, b));
            }

            for (int i = 0; i < 50001; i++) weights[i] = INF; 
        }

        void dijkstra(int source) {
            weights[source] = 0;
            dists.insert(make_pair(0, source));
            while (!dists.empty()) {
                int n = dists.begin()->second;
                dists.erase(dists.begin());
                for (auto& e: edges[n]) {
                    if (weights[e.first] > weights[n] + e.second) {
                        weights[e.first] = weights[n] + e.second;
                        dists.insert(make_pair(weights[e.first], e.first));
                    }
                }
            }
        }
        void main() {
            prepData();
            ofstream fout ("dining.out");
            int origDist[50000];
            dijkstra(N-1);
            for (int i = 0; i < 50000; i++) origDist[i] = weights[i];
            for (int i = 0; i < 50001; i++) weights[i] = INF; 
            for (auto i: bales) {
                edges[N].push_back(make_pair(i.first, origDist[i.first] - i.second));
            }
            dijkstra(N);
            for (int i = 0; i < N-1; i++) {
                fout << (origDist[i] >= weights[i] ? 1 : 0) << endl;
            }
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}