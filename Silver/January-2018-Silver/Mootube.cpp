#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define _INT_MAX 2000000000

class Solution {
    private:
        int N, Q;
        vector<vector<int> > questions;
        list<vector<int> > tree[5001];
        int total = 0;
        int memo[5001] = {};
        queue<int> erase;
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
            if (memo[key] == 1) return;
            total ++;
            memo[key] = 1;
            for (auto i = tree[key].begin(); i != tree[key].end(); i++) {
                if ((*i)[1] >= k) dfs((*i)[0], k);
            }
            erase.push(key);
        }

        void main() {
            ofstream fout ("mootube.out");
            readIn();
            for (int i = 0; i < questions.size(); i++) {
                while (!erase.empty()) {
                    memo[erase.front()] = 0;
                    erase.pop();
                }
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