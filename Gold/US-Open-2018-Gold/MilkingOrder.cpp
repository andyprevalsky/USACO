#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
    private:
        int N, M;
        unordered_set<int> edges[100000];
        vector<int> ans;
        int memo[100000] = {};
        int inDegree[100000] = {};
    public:

        void prepData() {
            ifstream fin ("milkorder.in");
            fin >> N >> M;
            for (int i = 0; i < M; i++) {
                int mi; fin >> mi;
                int prev = -1;
                vector<int> line;
                for (int j = 0; j < mi; j++) {
                    int a; fin >> a; a--;
                    line.push_back(a);
                    if (prev == -1) { prev = a; continue; }
                    edges[prev].insert(a); inDegree[a] += 1;
                    int tMemo[100000] = {};
                    if (hasCycle(a, prev, tMemo)) { 
                        int pz = -1;
                        for (auto z: line) {
                            if (pz == -1) { pz = z; continue; }
                            edges[pz].erase(z);
                            inDegree[z]--;
                            pz = z;
                        }    
                        return; 
                    }
                    prev = a;
                }
            }
        }
        bool hasCycle(int root, int cycleHead, int* memo) {
            if (root == cycleHead) return true;
            if (memo[root] == 1) return false;
            memo[root] = 1;
            bool ans = false;
            for (auto& i: edges[root]) {
                ans |= hasCycle(i, cycleHead, memo);
            }
            return ans;
        }

        void topSort() {
            priority_queue<int> q;
            for (int i = 0; i < N; i++) {
                if (inDegree[i] == 0) q.push(-i-1);
            }
            while (!q.empty()) {
                int n = q.top(); q.pop(); n = -n - 1;
                for (auto& i: edges[n]) {
                    inDegree[i] -= 1;
                    if (inDegree[i] == 0) q.push(-i-1);
                }
                ans.push_back(n+1);
            }
        }

        void main() {
            prepData();
            ofstream fout ("milkorder.out");
            topSort();
            for (auto i: ans) fout << i << (i != ans.back() ? " " : "");
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}