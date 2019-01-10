#include <fstream>
#include <iostream>
using namespace std;

#define MOD 1000000007

class Solution {
    private:
        long long N, M, K;
        long long res = 0;
        long long maxCombo = 1;
        int dp[1000001];
    public:
        void prepData() {
            ifstream fin ("spainting.in");
            fin >> N >> M >> K;
            for (int i = 0; i < N; i++) {
                maxCombo *= M;
                maxCombo %= MOD;
            }
        }

        void main() {
            prepData();
            ofstream fout ("spainting.out");
            dp[0] = M;
            long long numCombinations = 1;
            for (int k = 1; k < K; k++) {
                numCombinations *= M;
                numCombinations %= MOD;
                dp[k] = numCombinations;
            }
            numCombinations *= M;
            numCombinations %= MOD;
            numCombinations -= M;
            numCombinations += MOD;
            numCombinations %= MOD;
            dp[K] = numCombinations;
            for (int i = K+1; i <= N; i++) {
                numCombinations *= M;
                numCombinations %= MOD;
                numCombinations -= (dp[i-K]*(M-1))%MOD;
                numCombinations += MOD;
                numCombinations %= MOD;
                dp[i] = numCombinations;
            }
            fout << (maxCombo - dp[N] + MOD)%MOD;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}