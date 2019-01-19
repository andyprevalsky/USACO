#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
    private:
        long long N, M, T;  
        vector<int> numCows;
        vector<pair<int, int>> edges[10001];
        vector<int> reEdges[10001]; // pair(nextField, currTravel)
        long long res = 0;            
        long long weights[10001];
        
        long long cp[10001] = {};
        int memo[10001] = {};
        vector<int> leaves;
    public:
        void prepData() {
            ifstream fin ("shortcut.in");
            fin >> N >> M >> T;
            for (int i = 0; i < N; i++) {
                int a; fin >> a;
                numCows.push_back(a);
            }
            int a, b, c;
            for (int i = 0; i < M; i++) {
                fin >> a >> b >> c;
                edges[a].push_back(make_pair(b, c));
                edges[b].push_back(make_pair(a, c));
            }

        }      

        void dijkstra() {
            set<vector<vector<int>>> dists; // vector 1 is the weight, vector 2 is the list of nodes, vector 3 is the next node
            set<int> seen;
            for (int i = 0; i < 10001; i++) weights[i] = 2000000000;
            weights[1] = 0;
            dists.insert(vector<vector<int>>({{0}, {0}, {1}}));
            while (!dists.empty()) {
                vector<vector<int>> ne = *dists.begin(); int n = ne[2][0];
                dists.erase(dists.begin());
                if (seen.find(n) != seen.end()) continue;
                seen.insert(n);
                int cameFrom = ne[1].front();
                reEdges[cameFrom].push_back(n);
                vector<int> sub; sub.push_back(n);
                for (auto& i: ne[1]) sub.push_back(i);
                for (auto& e: edges[n]) {
                    if (weights[e.first] >= weights[n] + e.second) {
                        weights[e.first] = weights[n] + e.second;
                        dists.insert(vector<vector<int>>({{(int)weights[e.first]}, sub, {e.first}}));
                    }
                }
            }
        }

        int dfs(int curr) {
            if (memo[curr] == 1) return 0;
            memo[curr] = 1;
            int total = numCows[curr-1];
            for (auto& i: reEdges[curr]) {
                total += dfs(i);
            }
            cp[curr] = total;
            return total;
        }

        void main() {
            prepData();
            ofstream fout ("shortcut.out");

            dijkstra();
            for (int i = 1; i <= N; i++) {
                dfs(i);
            }

            for (int i = 1; i<= N; i++) {
                res = max(res, weights[i]*cp[i] - cp[i]*T);
            }
            cout << res << endl;
            fout << res << endl;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}
