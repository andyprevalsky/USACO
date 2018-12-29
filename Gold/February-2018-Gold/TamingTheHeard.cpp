#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define INF 2000000000

class Solution {
    private:
        int N;
        vector<int> s;
        int dp[101][101] = {};
    public:
        void prepData() {
            ifstream fin ("taming.in");
            fin >> N; int a;
            for (int i = 0; i < N; i++) {
                fin >> a; s.push_back(a);
            }
            for (int i = 0; i < 101; i++) {
                for (int j = 0; j < 101; j++) {
                    dp[i][j] = INF;
                }
            }
        }
        
        int breakout(int lBound, int rBound) { // lBound is first 0, rBound is location of next breakout
            int res = 0;
            for (int i = lBound, c = 0; i < rBound; i++, c++) {
                if (s[i] != c) res++;
            }
            return res;
        }

        void main() {
            prepData();
            ofstream fout ("taming.out");
            vector<int> ans; ans.push_back(breakout(0, N));
            dp[0][0] = 0;
            for (int i = 1; i < N; i++) {
                int lMin = INF;
                for (int j = i; j < N; j++) {
                    for (int k = 0; k < j; k++) {
                        dp[i][j] = min(dp[i][j], dp[i-1][k]+breakout(k, j));
                        lMin = min(lMin, dp[i][j]+breakout(j, N));
                    }
                }
                ans.push_back(lMin);
            }
            for (auto i: ans) fout << i << endl;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}
