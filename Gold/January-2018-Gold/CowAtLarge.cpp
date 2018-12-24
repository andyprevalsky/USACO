#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#define INF 2000000000

class Solution {
    private:
        int N, K;
        vector<int> edges[100000];
        vector<pair<int, int>> exits;
        queue<pair<int, int>> mq;
        int res = 0;
    public:
        void prepData() {
            ifstream fin ("atlarge.in");
            fin >> N >> K; int a, b;
            for (int i = 0; i < N-1; i++) {
                fin >> a >> b; a--; b--;
                edges[a].push_back(b);
                edges[b].push_back(a);
            }
        }

        void main() {
            prepData();
            ofstream fout ("atlarge.out");
            
            for (int i = 0; i < N; i++) {
                if (edges[i].size() == 1) { mq.push(make_pair(i, 0)); }
            }
            mq.push(make_pair(K-1, 1));

            int memo[100000] = {};
            while(!mq.empty()) {
                pair<int, int> node = mq.front(); mq.pop();
                if (memo[node.first] == 1 && node.second == 1) res++;
                if (memo[node.first] != 0) continue;
                if (node.second == 1) {
                    memo[node.first] = 2;
                    for (auto& e: edges[node.first]) mq.push(make_pair(e, 1));
                } else {
                    memo[node.first] = 1;
                    for (auto& e: edges[node.first]) mq.push(make_pair(e, 0));
                }

            }
            fout << res;
        }
};

int main() {
    Solution s; s.main();
    return 0;
}