#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> left;
        vector<int> right;
        int dp[1000][1000] = {};
    public:
        void prepData() {
            ifstream fin ("nocross.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                left.push_back(a);
            }
            for (int i = 0; i < N; i++) {
                fin >> a;
                right.push_back(a);
            }   
            memset(dp, -1, sizeof(dp));         
        }

        int getNearest(int lP, int rP) {
            while (rP != right.size() && abs(left[lP]-right[rP]) > 4) rP++;
            return (rP+1);
        }

        int dfs(int lP, int rP) {
            if (rP > right.size()) return -1;
            if (lP == left.size() || rP == right.size()) return 0;
            if (dp[lP][rP] != -1) return dp[lP][rP];
            int total = 0;
            dp[lP][rP] = total + max(dfs(lP+1, getNearest(lP, rP)) + 1, dfs(lP+1, rP));
            return dp[lP][rP];
        }


        void main() {
            prepData();
            ofstream fout ("nocross.out");
            fout << dfs(0, 0);
        }
};

int main() {
    Solution s;
    s.main();
}