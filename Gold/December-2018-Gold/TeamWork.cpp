#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N, K;
        int cows[10000];
        int dp[10001] = {};
    public:
        void prepData() {
            ifstream fin ("teamwork.in");
            fin >> N >> K;
            for (int i = 0; i < N; i++) fin >> cows[i];
        }

        void main() {
            prepData();
            ofstream fout ("teamwork.out");
            for (int i = 0; i <= N; i++) {
                int m = 0;
                for (int k = i-1; i-k <= K && k >= 0; k--) {
                    m = max(m, cows[k]);
                    dp[i] = max(dp[i], m*(i-k)+dp[k]);
                }
            }
            fout << dp[N];
        }
};

int main() {
    Solution s; s.main();
    return 0;
}