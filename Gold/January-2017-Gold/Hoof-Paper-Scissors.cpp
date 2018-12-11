#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution {
    private:
        int res = 0;
        int N, K;
        int memo[21][100001][3] = {};
        vector<int> moves;
        vector<vector<int>> leftPrefixes;
    public:
        void prepData() {
            ifstream fin ("hps.in");
            fin >> N >> K;
            char ch;
            for (int i = 0; i < N; i++) {
                fin >> ch;               
                if (ch == 'P') moves.push_back(0);
                else if (ch == 'H') moves.push_back(1);
                else if (ch == 'S') moves.push_back(2);
            }
        }

        void main() {
            prepData();
            ofstream fout ("hps.out");
            for (int k = 0; k <= K; k++) {
                for (int i = N-1; i >= 0; i--) {
                    for (int s = 0; s < 3; s++) {
                        if (k == 0) { memo[k][i][s] = memo[k][i+1][s] + (moves[i] == s ? 1: 0); continue; }
                        int s2 = (s+1)%3;
                        int s3 = (s+2)%3;
                        memo[k][i][s] = max(memo[k][i+1][s], max(memo[k-1][i+1][s2], memo[k-1][i+1][s3])) + (moves[i] == s ? 1 : 0); 
                    }
                }
            }
            fout << max(memo[K][0][0], max(memo[K][0][1], memo[K][0][2])) << endl;
        }
};

int main() {
    Solution s;
    s.main();
}