#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> E1;
        vector<int> E2;
        vector<int> B;
        int memo[100001] = {};
    public:
        void readIn() {
            ifstream fin ("cardgame.in");
            fin >> N;
            int a;
            for (int i = 0; i < N/2; i++) {
                fin >> a;
                memo[a] = 1;
                E1.push_back(a);
            }
            for (int i = 0; i < N/2; i++) {
                fin >> a;
                memo[a] = 1;
                E2.push_back(a);
            }
            for (int i = 1; i < 100001; i++) {
                if (i > 2*N) break;
                if (memo[i] == 0) B.push_back(i);
            }
            sort(E1.begin(), E1.end(), greater<int>());
            sort(E2.begin(), E2.end());
            sort(B.begin(), B.end());
        }

        void main() {
            readIn();
            ofstream fout ("cardgame.out");
            int points = 0;
            int j = 0;
            for (int i = 0; i < N/2; i++) {
                if (j == E1.size()) break;
                while (B[i] > E2[j]) {
                    j++;
                    if (j == E2.size()) break;
                }
                if (j == E2.size()) break;
                points++;
                j++;
            }
            reverse(B.begin(), B.end());

            j = 0;
            for (int i = 0; i < N/2; i++) {
                if (j == E1.size()) break;
                while (B[i] < E1[j]) {
                    j++;
                    if (j == E1.size()) break;
                }
                if (j == E1.size()) break;
                points++;
                j++;
            }
            fout << points << endl;
        }
        
};

int main() {
    Solution s;
    s.main();
}