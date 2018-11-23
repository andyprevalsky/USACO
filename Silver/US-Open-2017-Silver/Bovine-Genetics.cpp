#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    private:
        int memo[64];
        int total = 0;
    public:
        void BovineGenomics() {
            ifstream fin ("cownomics.in");
            ofstream fout ("cownomics.out");
            int N, M;
            fin >> N >> M;
            vector<vector<int> > cows;
            char c;
            int a;
            for (int i = 0; i < 2*N; i++) {
                vector<int> row;
                for (int j = 0; j < M; j++) {
                    fin >> c;
                    if (c == 'A') a = 0;
                    else if (c == 'C') a = 1;
                    else if (c == 'G') a = 2;
                    else a = 3;
                    row.push_back(a);
                }
                cows.push_back(row);
            }

            for (int i = 0; i < M-2; i++) {
                for (int j = i + 1; j < M-1; j++) {
                    for (int k = j+1; k < M; k++) {
                        for (int i = 0; i < 64; i++) {
                            memo[i] = 0;
                        }
                        for (int x = 0; x < N; x++) {
                            memo[cows[x][i]*16 + cows[x][j]*4 + cows[x][k]] = 1;
                        }
                        for (int x = N; x < 2*N; x++) {
                            if (memo[cows[x][i]*16 + cows[x][j]*4 + cows[x][k]]) break;
                            if (x == 2*N - 1) total++;
                        }
                    }
                }
            }
            fout << total;
        }
};

int main() {
    Solution s;
    s.BovineGenomics();
    return 0;
}