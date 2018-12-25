#include <fstream>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N, M, K;
    public:
        void prepData() {
            ifstream fin ("spainting.in");
            fin >> N >> M >> K;
        }

        void main() {
            prepData();
            ofstream fout ("spainting.out");
            int lStamp = N-K+1;
            int numLeft = N-K;
            int ans = lStamp*K*numLeft*K;

            cout << ans << endl;
            for (int i = 1; i <= N-K; i++) {
                ans -= K * (i*(i+1))/2;
            }

            fout << ans;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}