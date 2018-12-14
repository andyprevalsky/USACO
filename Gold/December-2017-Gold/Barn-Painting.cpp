#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

#define MMOD 1000000007

class Solution {
    private:
        int N, K;
        long long res = 1;
        vector<int> edges[100000];
        int memo[100000] = {};
        int colored[100000] = {};
    public:
        void prepData() {
            ifstream fin ("barnpainting.in");
            fin >> N >> K;
            int a, b;
            for (int i = 0; i < N-1; i++) {
                fin >> a >> b; a--; b--;
                edges[a].push_back(b);
                edges[b].push_back(a);
            }

            for (int i = 0; i < K; i++) {
                fin >> a >> b;
                colored[a-1] = b;
            }
        }

        vector<long long> dfs(int root) {
            if (memo[root] == 1) return {-1, -1, -1};
            memo[root] = 1;

            vector<long long> variations = {1, 1, 1};
            if (colored[root] != 0) variations = {colored[root] == 1 ? 1:0, colored[root] == 2 ? 1:0, colored[root] == 3 ? 1:0};
            
            for (auto i: edges[root]) {
                vector<long long> res = dfs(i); if (res == vector<long long>{-1, -1, -1}) continue; 
                long long validA = res[1] + res[2];
                long long validB = res[0] + res[2];
                long long validC = res[0] + res[1];
                variations[0] *= validA; variations[1] *= validB; variations[2] *= validC;
                for (int i = 0; i < 3; i++) variations[i] = variations[i]%MMOD;
            }

            return variations;
        }

        void main() {
            prepData();
            ofstream fout ("barnpainting.out");
            for (int i = 0; i < N; i++) {
                vector<long long> v = dfs(i); if (v == vector<long long>{-1, -1, -1}) continue; 
                res *= (v[0]+v[1]+v[2]);
            }
            fout << (res%MMOD) << endl;
        }

};

int main() {
    Solution s;
    s.main();
}