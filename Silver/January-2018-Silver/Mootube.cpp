#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

#define _INT_MAX 2000000000

class Solution {
    private:
        int N, Q;
        vector<vector<int> > questions;
        unordered_map<int, vector<vector<int> > > tree;
        unordered_map<int, int> memo;
        int total = 0;
    public:
        void readIn() {
            ifstream fin ("mootube.in");
            fin >> N >> Q;
            int a, b, c;
            for (int i = 1; i < N; i++) {
                fin >> a >> b >> c;
                tree[a].push_back({b, c});
                tree[b].push_back({a, c});
            }
            for (int i = 0; i < Q; i++) {
                fin >> a >> b;
                questions.push_back({a, b});
            }
        }

        void dfs(int key, int k) {
            if (memo[key]) return;
            total ++;
            memo[key] = 1;
            for (int i = 0; i < tree[key].size(); i++) {
                if (tree[key][i][1] >= k) dfs(tree[key][i][0], k);
            }
            memo.erase(key);
        }

        void main() {
            ofstream fout ("mootube.out");
            readIn();
            for (int i = 0; i < questions.size(); i++) {
                dfs(questions[i][1], questions[i][0]);
                fout << total-1 << endl;
                total = 0;
            }
        }
};

int main() {
    Solution s;
    s.main();
}