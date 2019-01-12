#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    private:
        pair<int, int> input[100001];
        int BIT[100001] = {};
        int N;
    public:
        int sum(int x) {
            int res = 0;
            while (x > 0) {
                res += BIT[x];
                x -= x&-x;
            }
            return res;
        }

        void update(int x) {
            while (x <= N) {
                BIT[x] += 1;
                x += x&-x;
            }
        }

        void prepData() {
            ifstream fin ("sort.in");
            fin >> N;
            for (int i = 1; i <= N; i++) {
                input[i].second = i;
                fin >> input[i].first;
            }
            sort(input+1, input+N+1);
        }
        void main() {
            ofstream fout ("sort.out");
            prepData();

            int res = 1;
            for (int i = 1; i < N; i++) {
                update(input[i].second);
                res = max(res, i-sum(i));
            }
            fout << res << endl;
            return;
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}