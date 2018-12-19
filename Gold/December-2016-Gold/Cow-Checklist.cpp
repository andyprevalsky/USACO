#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x3FFFFFFFFFFFFFFFLL

class Solution {
    private:
        vector<pair<long long, long long>> H;
        vector<pair<long long, long long>> G;
        int hSize;
        int gSize;
        long long memo[1001][1001][2];
    public:
        void prepData() {
            ifstream fin ("checklist.in");
            fin >> hSize >> gSize;
            long long a, b;
            H.push_back(make_pair(INF, INF));
            for (int i = 0; i < hSize; i++) {
                fin >> a >> b;
                H.push_back(make_pair(a, b));
            }
            G.push_back(make_pair(0, 0));
            for (int i = 0; i < gSize; i++) {
                fin >> a >> b;
                G.push_back(make_pair(a, b));
            }
            memset(memo, -1, sizeof(memo));
            memo[1][0][0] = 0;
        }

        long long dist(pair<long long, long long> a, pair<long long, long long> b) {
            long long ret = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
            if (ret < 0) return INF;
            else return ret;
        }


        long long DTW(int a, int b, int s) {
            if (a == 0 || b < 0) return INF;
            if (memo[a][b][s] != -1) return memo[a][b][s];
            if (s == 0) memo[a][b][s] = min((dist(H[a], H[a-1]) + DTW(a-1, b, 0)), (dist(H[a], G[b]) + DTW(a-1, b, 1)));
            else memo[a][b][s] = min((dist(G[b], H[a]) + DTW(a, b-1, 0)), (dist(G[b], G[b-1]) + DTW(a, b-1, 1)));
            return memo[a][b][s];
        }

        void main() {
            prepData();
            ofstream fout ("checklist.out");
            fout << DTW(hSize, gSize, 0) << endl;
        }
};

int main() {
    Solution s;
    s.main();
}