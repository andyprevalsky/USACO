#include <fstream>
using namespace std;

class Solution {
    private:
        int T, A, B;
        int memo[5000000] = {};
        int closest = 0;
    public:
        void readIn() {
            ifstream fin ("feast.in");
            fin >> T >> A >> B;
        }

        void dfs(int v, bool halved) {
            if (memo[v] == 1) return;
            if (v > closest) closest = v;
            memo[v] = 1;
            if (v + A <= T) dfs(v+A, halved);
            if (v + B <= T) dfs(v+B, halved);
            if (!halved) dfs(v/2, true);
            return;
        }

        void main() {
            readIn();
            ofstream fout ("feast.out");
            dfs(0, false);
            fout << closest;
        }
};

int main() {
    Solution s;
    s.main();
}