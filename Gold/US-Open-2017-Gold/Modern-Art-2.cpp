#include <fstream>
#include <vector>
#include <iostream>
#include <sys/resource.h>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> c;
        vector<int> edges[100001];
        int res = 0;
    public:
        void prepData() {
            ifstream fin ("art2.in");
            fin >> N;
            int a;
            int prev = -1;
            for (int i = 0; i < N; i++) {
                fin >> a;
                if (a != prev) c.push_back(a);
                prev = a;
            }

            for (int i = 0; i < c.size(); i++) {
                edges[c[i]].push_back(i);        
            }
        }
        int recurse (int start, int end) {
            int res = 0;
            for (int i = start; i < end; i++) {
                if (edges[c[i]].size() == 1 || c[i] == 0) continue;
                for (int j = 1; j < edges[c[i]].size(); j++) {
                    if (edges[c[i]][j] > end) { return 2000000000; }
                    res = max(res, recurse(edges[c[i]][j-1]+1, edges[c[i]][j]));
                }
                i = edges[c[i]].back()+1;
            }
            return res+1;
        }

        void main() {
            prepData();
            ofstream fout ("art2.out");
            int res = 0;
            for (int i = 0; i < c.size(); i++) {
                if (c[i] != 0) { res = recurse(0, c.size()); break; }
            }
            cout << (res >= 2000000000 ? -1 : res)  << endl;
        }
};

void setStackLimit() {
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
}

int main() {
    setStackLimit();
    Solution s;
    s.main();
}