#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

#define MLONG 9223372036854775807

class Solution {
    private:
        int N, M;
        vector<pair<int, int>> jPos;
        vector<pair<int, int>> bPos;
        long long memo[1001][1001] = {};

    public:
        long long dist(pair<int, int> p1, pair<int, int> p2) {
            long long y1 = p1.first;
            long long y2 = p2.first;
            long long x1 = p1.second;
            long long x2 = p2.second;
            return ((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
        }

        void prepData() {
            ifstream fin ("radio.in");
            fin >> N >> M;

            int a, b;
            fin >> a >> b;
            jPos.push_back(make_pair(a, b));
            fin >> a >> b;
            bPos.push_back(make_pair(a, b));
            
            char c;
            pair<int, int>tPos = jPos[0];
            for (int i = 0; i < N; i++) {
                fin >> c;
                if (c == 'N') {
                    tPos.second++;
                }
                else if (c == 'E') {
                    tPos.first++;
                }
                else if (c == 'W') {
                    tPos.first--;
                }
                else if (c == 'S') {
                    tPos.second--;
                }
                jPos.push_back(make_pair(tPos.first, tPos.second));
            }

            tPos = bPos[0];
            for (int i = 0; i < M; i++) {
                fin >> c;
                if (c == 'N') {
                    tPos.second++;
                }
                else if (c == 'E') {
                    tPos.first++;
                }
                else if (c == 'W') {
                    tPos.first--;
                }
                else if (c == 'S') {
                    tPos.second--;
                }
                bPos.push_back(make_pair(tPos.first, tPos.second));
            }

            for (int i = 0; i <= N; i++) {
                for (int j = 0; j <= M; j++) {
                    memo[i][j] = MLONG;
                }
            }

            memo[0][0] = 0;
        }  

        long long DTW(int bess, int john) {
            if (bess < 0 || john < 0) return MLONG;
            if (memo[john][bess] != MLONG) return memo[john][bess];
            memo[john][bess] = dist(bPos[bess], jPos[john]) + min(DTW(bess-1, john), min(DTW(bess, john-1), DTW(bess-1, john-1)));
            return memo[john][bess];
        }

        void main() {
            prepData();
            ofstream fout ("radio.out");
            fout << DTW(bPos.size()-1, jPos.size()-1) << endl;
        }
};

int main() {
    Solution s;
    s.main();
}