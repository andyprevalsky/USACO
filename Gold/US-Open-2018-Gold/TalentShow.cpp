#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

#define INF 0x3FFFFFFFFFFFFFFFLL

class Solution {
    private:
        int N, W;
        vector<pair<int, int>> cows;
        long long dpw[1001];
    public:
        void prepData() {
            ifstream fin ("talent.in");
            fin >> N >> W; int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                cows.push_back(make_pair(a, b));
            }
        }

        bool viable(int y) {
            for (int i = 1; i <= W; i++) {
                dpw[i] = -INF;
            }
            dpw[0] = 0;
            for (auto i: cows) {
                long long val = (long long)1000*i.second - (long long)y*i.first;
                cout << val << endl;
                for (int j = W; j >= 0; j--) {
                    int nWeight = min(W, j+i.first);
                    if (dpw[j] != -INF) dpw[nWeight] = max(dpw[j]+val, dpw[nWeight]);
                }
            }
            return dpw[W] >= 0;
        }

        void main() {
            ofstream fout ("talent.out");
            prepData();
            int count = 0;
            int l = 0;
            int r = 250 * 1000;
            while (l < r-1) {
                int mid = l + (r-l)/2;
                if (viable(mid)) l = mid;
                else r = mid;
            }
            fout << l << endl;
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}